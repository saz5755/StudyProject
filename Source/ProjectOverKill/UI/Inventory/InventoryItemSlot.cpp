#include "UI/Inventory/InventoryItemSlot.h"

#include "Item/ItemBase.h"
#include "UI/Inventory/InventoryTooltip.h"

void UInventoryItemSlot::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UInventoryItemSlot::NativeConstruct()
{
    Super::NativeConstruct();

    ItemBorder = Cast<UBorder>(GetWidgetFromName(TEXT("ItemBorder")));
    ItemIcon = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
    ItemQuantity = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemQuantity")));

    // Tooltip 
    if (ToolTipClass)
    {
        UInventoryTooltip* ToolTip = CreateWidget<UInventoryTooltip>(this, ToolTipClass);
        ToolTip->InventorySlotBeginHovered = this;
        SetToolTip(ToolTip);
    }

    if (ItemReference)
    {
        switch(ItemReference->ItemQuality)
        {
        case EItemQuality::Shoddy:
            ItemBorder->SetBrushColor(FLinearColor::Gray);
            break; 
        case EItemQuality::Common:
            ItemBorder->SetBrushColor(FLinearColor::White);
            break; 
        case EItemQuality::Quality:
            ItemBorder->SetBrushColor(FLinearColor::Green);
            break;
        case EItemQuality::Masterwork:
            ItemBorder->SetBrushColor(FLinearColor::Blue);
            break;
        case EItemQuality::Grandmaster:
            ItemBorder->SetBrushColor(FLinearColor(100.0f, 65.0f, 0.0f, 1.0f));
            break;
        }
        UE_LOG(LogTemp, Warning, TEXT("Begin ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon)"))

        ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);

        UE_LOG(LogTemp, Warning, TEXT("After ItemIcon->SetBrushFromTexture"))

        if (ItemReference->NumericData.bIsStackable)
        {
            ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
        }
        else
        {
            ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);

}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
