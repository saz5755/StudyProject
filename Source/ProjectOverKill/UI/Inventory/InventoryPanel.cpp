#include "UI/Inventory/InventoryPanel.h"
#include "Player/MainPlayerController.h"
#include "Components/InventoryComponent.h"
#include "UI/Inventory/InventoryItemSlot.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "Item//ItemBase.h"

void UInventoryPanel::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryWrapBox = Cast<UWrapBox>(GetWidgetFromName(TEXT("InventoryWrapBox")));
	WeightInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeightInfo")));
	CapacityInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("CapacityInfo")));

	PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	//PlayerController = Cast<AMainPlayerController>(GetOwningPlayerController());

	if (PlayerController)
	{
		InventoryReference = PlayerController->GetInventory();
		if (InventoryReference)
		{
			InventoryReference->OnInventoryUpdated.AddUObject(this, &UInventoryPanel::RefreshInventory);
			SetInfoText();
		}
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
		InventoryWrapBox->ClearChildren();
	
		/*APlayerCharacter* PlayerCharacter =
			Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());*/

		for (UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		{
			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, IventorySlotClass);

			ItemSlot->SetItemReference(InventoryItem);
			
			InventoryWrapBox->AddChildToWrapBox(ItemSlot);

			//PlayerCharacter->SetWeaponMesh(InventoryItem->AssetData.SkeletalMesh);
			//PlayerCharacter->SetHelmetMesh(InventoryItem->AssetData.Mesh);
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
