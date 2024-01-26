// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/AlchemicComposeWidget.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TileView.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/EditableTextBox.h"
#include "Acme/AcmeCharacter.h"
#include "Acme/Data/ItemData.h"
#include "Acme/Widget/ItemEntryWidget.h"
#include "Acme/Utils/Util.h"
#include "Acme/Widget/AlchemySlotWidget.h"
#include "Acme/AcmeGameInstance.h"


void UAlchemicComposeWidget::NativeConstruct()
{
	bIsFocusable = true;
	SetKeyboardFocus();

	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	}

	CurrentCategory = EItemCategory::E_Element;
	SetActiveCategory();
	SetItemList();

	BtnElement->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnElementClicked);
	BtnEquipment->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnEquipmentClicked);
	BtnTool->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnToolClicked);
	BtnPotion->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnPotionClicked);
	BtnFood->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnFoodClicked);
	BtnMaterial->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnMaterialClicked);

	BtnMinus->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnMinusClicked);
	BtnPlus->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnPlusClicked);
	BtnCompose->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnComposeClicked);

	EdtNum->OnTextChanged.AddDynamic(this, &UAlchemicComposeWidget::OnTextChanged);
}

FReply UAlchemicComposeWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	//TODO: Change Key
	if (InKeyEvent.GetKey() == EKeys::End)
	{
		AAcmeCharacter* Character = GetOwningPlayerPawn<AAcmeCharacter>();
		Character->CloseInteractWidget();
	}

	return Result;
}

void UAlchemicComposeWidget::OnElementClicked()
{
	CurrentCategory = EItemCategory::E_Element;
	SetItemList();
}

void UAlchemicComposeWidget::OnEquipmentClicked()
{
	CurrentCategory = EItemCategory::E_Equipment;
	SetItemList();
}

void UAlchemicComposeWidget::OnToolClicked()
{
	CurrentCategory = EItemCategory::E_Tool;
	SetItemList();
}

void UAlchemicComposeWidget::OnPotionClicked()
{
	CurrentCategory = EItemCategory::E_Potion;
	SetItemList();
}

void UAlchemicComposeWidget::OnFoodClicked()
{
	CurrentCategory = EItemCategory::E_Food;
	SetItemList();
}

void UAlchemicComposeWidget::OnMaterialClicked()
{
	CurrentCategory = EItemCategory::E_Material;
	SetItemList();
}

void UAlchemicComposeWidget::OnMinusClicked()
{
	int num = UKismetStringLibrary::Conv_StringToInt(EdtNum->GetText().ToString());
	num--;

	if (num < 1) num = 1;
	SetNumTxt(FText::AsNumber(num));
}

void UAlchemicComposeWidget::OnPlusClicked()
{
	int num = UKismetStringLibrary::Conv_StringToInt(EdtNum->GetText().ToString());
	num++;

	if (num > 99) num = 99;
	SetNumTxt(FText::AsNumber(num));
}

void UAlchemicComposeWidget::OnComposeClicked()
{
	//check
	if (LeftSlot->IsEmpty() || RightSlot->IsEmpty()) return;

	FItem LeftItem = LeftSlot->GetItemInfo();
	FItem RightItem = RightSlot->GetItemInfo();

	if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TArray<FItem> ComposeResults = GameInstance->GetComposeResult(LeftItem, RightItem);

	LeftSlot->UseItem();
	RightSlot->UseItem();

	//Add
	if (!OwnerCharacter) OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	for (FItem result : ComposeResults)
	{
		OwnerCharacter->AddItem(result);
		//TVItem Update
		SetItemList();
	}
}

void UAlchemicComposeWidget::OnTextChanged(const FText& newText)
{
	//숫자가 아니면 걸러야 함
	int num = UKismetStringLibrary::Conv_StringToInt(EdtNum->GetText().ToString());

	SetNumTxt(newText);
}

void UAlchemicComposeWidget::SetNumTxt(const FText& newText)
{
	EdtNum->SetText(newText);
}

void UAlchemicComposeWidget::SetItemList()
{
	TVItem->ClearListItems();

	if (!OwnerCharacter) OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	TArray<FItem>& Items = OwnerCharacter->GetItems(CurrentCategory).Get();
	for (int i = 0; i < Items.Num(); i++)
	{
		FItem& item = Items[i];

		UItemData* Data = NewObject<UItemData>();
		Data->SetItem(item);
		Data->SetIndex(i);

		TVItem->AddItem(Data);
	}

	SetActiveCategory();
}

void UAlchemicComposeWidget::SetActiveCategory()
{
	if (ActiveCategoryImg != nullptr)
	{
		ActiveCategoryImg->SetColorAndOpacity(FColor(51, 51, 51, 51));
	}

	switch (CurrentCategory)
	{
	case EItemCategory::E_Element:
		ActiveCategoryImg = ImgElement;
		break;
	case EItemCategory::E_Equipment:
		ActiveCategoryImg = ImgEquipment;
		break;
	case EItemCategory::E_Tool:
		ActiveCategoryImg = ImgTool;
		break;
	case EItemCategory::E_Potion:
		ActiveCategoryImg = ImgPotion;
		break;
	case EItemCategory::E_Food:
		ActiveCategoryImg = ImgFood;
		break;
	case EItemCategory::E_Material:
		ActiveCategoryImg = ImgMaterial;
		break;
	}

	if (ActiveCategoryImg != nullptr)
	{
		ActiveCategoryImg->SetColorAndOpacity(FColor(0, 0, 0, 255));
	}
}
