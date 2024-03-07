// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/AlchemicComposeWidget.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TileView.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
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
	BtnTool->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnToolClicked);
	BtnMaterial->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnMaterialClicked);

	BtnMinus->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnMinusClicked);
	BtnPlus->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnPlusClicked);
	BtnCompose->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnComposeClicked);

	EdtNum->OnTextChanged.AddDynamic(this, &UAlchemicComposeWidget::OnTextChanged);

	BtnOk->OnClicked.AddDynamic(this, &UAlchemicComposeWidget::OnClickedOK);

	LeftSlotIdx = -1;
	RightSlotIdx = -1;
	Amount = 1;
}

FReply UAlchemicComposeWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::Tab)
	{
		AAcmeCharacter* Character = GetOwningPlayerPawn<AAcmeCharacter>();
		Character->CloseInteractWidget();
	}

	return Result;
}

void UAlchemicComposeWidget::OnElementClicked()
{
	CurrentCategory = EItemCategory::E_Element;
	WSInven->SetActiveWidgetIndex(0);
	SetActiveCategory();
}

void UAlchemicComposeWidget::OnToolClicked()
{
	CurrentCategory = EItemCategory::E_Tool;
	WSInven->SetActiveWidgetIndex(1);
	SetActiveCategory();
}

void UAlchemicComposeWidget::OnMaterialClicked()
{
	CurrentCategory = EItemCategory::E_Material;
	WSInven->SetActiveWidgetIndex(2);
	SetActiveCategory();
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

	if (ComposeResults.Num() == 0)
	{
		//Alert
		ShowAlert();
		return;
	}

	LeftSlot->Compose();
	RightSlot->Compose();

	if (!OwnerCharacter) OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());
	OwnerCharacter->UseItem(LeftItem.Category, LeftSlotIdx, Amount);
	OwnerCharacter->UseItem(RightItem.Category, RightSlotIdx, Amount);

	//Add
	LVResult->ClearListItems();
	for (FItem result : ComposeResults)
	{
		//Set TVResult
		UItemData* Data = NewObject<UItemData>();
		Data->ItemInfo.Num = Amount;
		Data->SetItem(result);

		LVResult->AddItem(Data);

		for (int i = 0; i < Amount; i++)
		{
			if (!OwnerCharacter->AddItem(result))
			{
				FActorSpawnParameters SpawnParams;
				FRotator rotator;
				FVector  SpawnLocation = OwnerCharacter->GetActorLocation();
				SpawnLocation.Z += 10;

				AInteractiveItem* ResultItem = GetWorld()->SpawnActor<AInteractiveItem>(DropItemClass, SpawnLocation, rotator, SpawnParams);
			}
		}
	}
	
	SetItemList();
	Amount = 1;
	EdtNum->SetText(FText::AsNumber(Amount));
	LeftSlotIdx = -1;
	RightSlotIdx = -1;
}

void UAlchemicComposeWidget::OnTextChanged(const FText& newText)
{
	//숫자가 아니면 걸러야 함
	int num = UKismetStringLibrary::Conv_StringToInt(EdtNum->GetText().ToString());
	if (num == 0) return;

	SetNumTxt(newText);
}

void UAlchemicComposeWidget::SetNumTxt(const FText& newText)
{
	EdtNum->SetText(newText);
}

void UAlchemicComposeWidget::SetItemList()
{
	if (!OwnerCharacter) OwnerCharacter = Cast<AAcmeCharacter>(GetOwningPlayerPawn());

	{
		TVElement->ClearListItems();

		TArray<FItem>& Items = OwnerCharacter->GetItems(EItemCategory::E_Element).Get();
		for (int i = 0; i < Items.Num(); i++)
		{
			FItem& item = Items[i];

			UItemData* Data = NewObject<UItemData>();
			Data->SetItem(item);
			Data->SetIndex(i);
			Data->SetParentRef(this);

			TVElement->AddItem(Data);
		}
	}

	{
		TVTool->ClearListItems();

		TArray<FItem>& Items = OwnerCharacter->GetItems(EItemCategory::E_Tool).Get();
		for (int i = 0; i < Items.Num(); i++)
		{
			FItem& item = Items[i];

			UItemData* Data = NewObject<UItemData>();
			Data->SetItem(item);
			Data->SetIndex(i);
			Data->SetParentRef(this);

			TVTool->AddItem(Data);
		}
	}

	{
		TVMaterial->ClearListItems();

		TArray<FItem>& Items = OwnerCharacter->GetItems(EItemCategory::E_Material).Get();
		for (int i = 0; i < Items.Num(); i++)
		{
			FItem& item = Items[i];

			UItemData* Data = NewObject<UItemData>();
			Data->SetItem(item);
			Data->SetIndex(i);
			Data->SetParentRef(this);

			TVMaterial->AddItem(Data);
		}
	}
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
	case EItemCategory::E_Tool:
		ActiveCategoryImg = ImgTool;
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

void UAlchemicComposeWidget::ShowAlert()
{
	//TODO: SFX
	BorderAlert->SetVisibility(ESlateVisibility::Visible);
}

void UAlchemicComposeWidget::OnClickedOK()
{
	BorderAlert->SetVisibility(ESlateVisibility::Hidden);
}

UTileView* UAlchemicComposeWidget::GetCurrentCategory()
{
	switch (CurrentCategory)
	{
	case EItemCategory::E_Element:
		return TVElement;
	case EItemCategory::E_Tool:
		return TVTool;
	case EItemCategory::E_Material:
		return TVMaterial;
	}

	return TVElement;
}

bool UAlchemicComposeWidget::AddToSlot(int idx)
{
	UItemData* Data = Cast<UItemData>(GetCurrentCategory()->GetItemAt(idx));
	FItem item = Data->GetItemInfo();

	if (LeftSlot->IsSame(item, idx) || RightSlot->IsSame(item, idx)) return false;

	if (LeftSlot->IsEmpty())
	{
		LeftSlot->SetSlot(item, idx);
		LeftSlotIdx = idx;

		return true;
	}
	else if(RightSlot->IsEmpty())
	{
		RightSlot->SetSlot(item, idx);
		RightSlotIdx = idx;

		return true;
	}

	return false;
}

bool UAlchemicComposeWidget::RemoveFromSlot(int idx)
{
	UItemData* Data = Cast<UItemData>(GetCurrentCategory()->GetItemAt(idx));
	FItem item = Data->GetItemInfo();

	if (LeftSlot->IsSame(item, idx))
	{
		LeftSlot->SetEmpty();
		LeftSlotIdx = -1;

		return true;
	}
	else if (RightSlot->IsSame(item, idx))
	{
		RightSlot->SetEmpty();
		RightSlotIdx = -1;

		return true;
	}

	return false;
}