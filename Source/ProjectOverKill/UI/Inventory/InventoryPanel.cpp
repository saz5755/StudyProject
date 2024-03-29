#include "UI/Inventory/InventoryPanel.h"
#include "Player/MainPlayerController.h"
#include "Components/InventoryComponent.h"
#include "UI/Inventory/InventoryItemSlot.h"

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
		
		for (UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		{
			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, IventorySlotClass);

			ItemSlot->SetItemReference(InventoryItem);
			
			InventoryWrapBox->AddChildToWrapBox(ItemSlot);
		}
		SetInfoText();
	}

}


bool UInventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
