#include "UI/Inventory/InventoryPanel.h"
#include "Player/MainPlayerController.h"
#include "Components/InventoryComponent.h"
#include "UI/Inventory/InventoryItemSlot.h"

void UInventoryPanel::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryPanel = Cast<UWrapBox>(GetWidgetFromName(TEXT("InventoryPanel")));
	WeightInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeightInfo")));
	CapacityInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("CapacityInfo")));

	PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	//PlayerController = Cast<AMainPlayerController>(GetOwningPlayerController());

	UE_LOG(LogTemp, Warning, TEXT("InventoryPanel - NativeConstruct()"));

	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryPanel -  PlayerController"));

		InventoryReference = PlayerController->GetInventory();
		UE_LOG(LogTemp, Warning, TEXT("Exist InventoryReference"));

		if (InventoryReference)
		{
			UE_LOG(LogTemp, Warning, TEXT("Exist InventoryReference"));

			InventoryReference->OnInventoryUpdated.AddUObject(this, &UInventoryPanel::RefreshInventory);
			SetInfoText();
		}
	}
}

void UInventoryPanel::SetInfoText() const
{
	WeightInfo->SetText(FText::Format(FText::FromString("{0}/{1}"), 
						InventoryReference->GetInventoryTotalWeight(),
						InventoryReference->GetWeightCapacity()));
	CapacityInfo->SetText(FText::Format(FText::FromString("{0}/{1}"), 
						InventoryReference->GetInventoryContents().Num(),
						InventoryReference->GetSlotsCapacity()));
}

void UInventoryPanel::RefreshInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("Start RefreshInventory"));

	if (/*InventoryReference &&*/ IventorySlotClass)
	{
		InventoryPanel->ClearChildren();
		
		UE_LOG(LogTemp, Warning, TEXT("if() ================= RefreshInventory"));

		for (UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		{
			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, IventorySlotClass);
						UE_LOG(LogTemp, Warning, TEXT("ItemSlot = CreateWidget<UInventoryItemSlot>"));

			ItemSlot->SetItemReference(InventoryItem);
			
			InventoryPanel->AddChildToWrapBox(ItemSlot);
		}
		SetInfoText();
	}

}


bool UInventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
