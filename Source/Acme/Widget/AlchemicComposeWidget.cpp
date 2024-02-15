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
#include "Acme/Item/InteractiveItem.h"

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

	LeftSlotIdx = -1;
	RightSlotIdx = -1;
	Amount = 1;
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
	if (Amount == 1) return;
	Amount--;

	if (Amount < 1) Amount = 1;
	SetNumTxt(FText::AsNumber(Amount));
}

void UAlchemicComposeWidget::OnPlusClicked()
{
	if (Amount == 99) return;
	if (LeftSlotIdx == -1 || RightSlotIdx == -1) return;

	FItem LeftItem = LeftSlot->GetItemInfo();
	FItem RightItem = RightSlot->GetItemInfo();

	if (Amount >= LeftItem.Num || Amount >= RightItem.Num) return;

	Amount++;

	if (Amount > 99) Amount = 99;
	SetNumTxt(FText::AsNumber(Amount));
}

void UAlchemicComposeWidget::OnComposeClicked()
{
	//check
	if (LeftSlot->IsEmpty() || RightSlot->IsEmpty()) return;

	FItem LeftItem = LeftSlot->GetItemInfo();
	FItem RightItem = RightSlot->GetItemInfo();

	if (!GameInstance) GameInstance = Cast<UAcmeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TArray<FItem> ComposeResults = GameInstance->GetComposeResult(LeftItem, RightItem);

	LeftSlot->Compose();
	RightSlot->Compose();

	if (!OwnerCharacter) OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	OwnerCharacter->UseItem(LeftItem.Category, LeftSlotIdx, Amount);
	OwnerCharacter->UseItem(RightItem.Category, RightSlotIdx, Amount);

	//Add
	for (FItem result : ComposeResults)
	{
		if (!OwnerCharacter->AddItem(result))
		{
			FActorSpawnParameters SpawnParams;
			//SpawnParams.Owner = Player;
			FRotator rotator;
			FVector  SpawnLocation = OwnerCharacter->GetActorLocation();
			SpawnLocation.Z += 10;

			AInteractiveItem* ResultItem = GetWorld()->SpawnActor<AInteractiveItem>(DropItemClass, SpawnLocation, rotator, SpawnParams);
		}
	}
	
	SetItemList();
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
		Data->SetParentRef(this);

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

bool UAlchemicComposeWidget::AddToSlot(int idx)
{
	if (LeftSlotIdx == idx || RightSlotIdx == idx) return false;

	if (LeftSlot->IsEmpty())
	{
		//Add
		UItemData* Data = Cast<UItemData>(TVItem->GetItemAt(idx));
		FItem info = Data->GetItemInfo();

		LeftSlot->SetSlot(info);
		LeftSlotIdx = idx;

		return true;
	}
	else if(RightSlot->IsEmpty())
	{
		UItemData* Data = Cast<UItemData>(TVItem->GetItemAt(idx));
		FItem info = Data->GetItemInfo();

		RightSlot->SetSlot(info);
		RightSlotIdx = idx;

		return true;
	}

	return false;
}

bool UAlchemicComposeWidget::RemoveFromSlot(int idx)
{
	if (LeftSlotIdx == idx)
	{
		LeftSlot->SetEmpty();
		LeftSlotIdx = -1;

		return true;
	}
	else if (RightSlotIdx == idx)
	{
		RightSlot->SetEmpty();
		RightSlotIdx = -1;

		return true;
	}

	return false;
}