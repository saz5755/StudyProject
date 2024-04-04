#include "UI/Inventory/InventoryPanel.h"
#include "Player/MainPlayerController.h"
#include "Components/InventoryComponent.h"
#include "UI/Inventory/InventoryItemSlot.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "Item/ItemBase.h"

void UInventoryPanel::NativeConstruct()
{
	Super::NativeConstruct();

	//InventoryWrapBox = Cast<UWrapBox>(GetWidgetFromName(TEXT("InventoryWrapBox")));

	InventoryListview = Cast<UListView>(GetWidgetFromName(TEXT("InventoryListviewTest")));
	WeightInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeightInfo")));
	CapacityInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("CapacityInfo")));

	PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	
	// InventoryReference = PlayerController->GetInventory();

	if (PlayerController)
	{
		InventoryReference = PlayerController->GetInventory();
		if (InventoryReference)
		{
			InventoryReference->OnInventoryUpdated.AddUObject(this, &UInventoryPanel::RefreshInventory);
			SetInfoText();
		}
	}
	SelectItem = nullptr;

	InventoryListview->OnItemDoubleClicked().AddUObject<UInventoryPanel>(
		this, &UInventoryPanel::ItemDoubleClick);
}

void UInventoryPanel::ItemDoubleClick(UObject* Obj)
{
	UInventoryItemSlot* Data = Cast<UInventoryItemSlot>(Obj);
	SelectItem = Data->GetItemReference();
	EItemType Type = SelectItem->ItemType;

	APlayerCharacter* PlayerCharacter =
		Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// 아이템 타입에 따라 SetMesh 설정하기
	switch (Type)
	{
		case EItemType::Weapon:
		PlayerCharacter->SetWeaponMesh(SelectItem->AssetData.SkeletalMesh);
		break;
		
		case EItemType::Shield:
		PlayerCharacter->SetHelmetMesh(SelectItem->AssetData.SkeletalMesh);
		break;
	}
}

void UInventoryPanel::SetInfoText() const
{
	const FString WeightInfoValue
	{	FString::SanitizeFloat(InventoryReference->GetInventoryTotalWeight()) + "/" + 
		FString::SanitizeFloat(InventoryReference->GetWeightCapacity())
	};

	const FString CapacityInfoValue{
		FString::FromInt(InventoryReference->GetInventoryContents().Num()) + "/" +
		FString::FromInt(InventoryReference->GetSlotsCapacity())
	};

	WeightInfo->SetText(FText::FromString(WeightInfoValue));
	CapacityInfo->SetText(FText::FromString(CapacityInfoValue));
}

void UInventoryPanel::RefreshInventory()
{
	if (InventoryReference && IventorySlotClass)
	{
		//InventoryWrapBox->ClearChildren();

		InventoryListview->ClearListItems();

		for (UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		{
			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, IventorySlotClass);
			
			ItemSlot->SetItemReference(InventoryItem);
		
			//InventoryWrapBox->AddChildToWrapBox(ItemSlot);
			InventoryListview->AddItem(ItemSlot);
		}

		SetInfoText();
	}

}

bool UInventoryPanel::NativeOnDrop(
	const FGeometry& InGeometry, 
	const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	if (ItemDragDrop->SourceItem && InventoryReference)
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected an item drop on InventoryPanel."))

		// returning true will stop the drop operation at this widget 
		return true;
	}

	// returning false will cause the drop operation to fall through to underlying widgets (if any)
	return false;
}
