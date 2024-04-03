#include "UI/Inventory/InventoryItemSlot.h"
#include "Item/ItemBase.h"
#include "UI/Inventory/InventoryTooltip.h"
#include "UI/Inventory//DragItemVisual.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "Components/Image.h"
#include "Components/InventoryComponent.h"
#include "Player/MainPlayerController.h"
#include "Inventory/World/Pickup.h"


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
            ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.51f, 0.169f));
            break;
        case EItemQuality::Masterwork:
            ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.4f, 0.75f));
            break;
        case EItemQuality::Grandmaster:
            ItemBorder->SetBrushColor(FLinearColor(100.0f, 65.0f, 0.0f, 1.0f));
            break;
        }

        ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);

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
    FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
    }

    return Reply.Unhandled();
}

//FReply UInventoryItemSlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//    FReply Reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
//
//    FVector2D ClickedPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
//    //UWidget* ClickedWidget = InGeometry.FindWidgetAtPosition(ClickedPosition);
//    //ItemReference->ID 
//
//    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
//    {
//        // ���� ���콺 ��ư�� ���� Ŭ���� ��� ó��
//        UE_LOG(LogTemp, Warning, TEXT("Left mouse button double clicked!"));
//        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("%s"), *InGeometry.ToString()));
//
//        //PlayerCharacter->SetHelmetMesh(InventoryItem->AssetData.Mesh);
//       
//        // ó�� �� �̺�Ʈ�� ó���Ǿ����� ��ȯ
//        return Reply.Handled();
//    }
//
//    // ��Ŭ�� �� �ٸ� ��ư�� ���� Ŭ���� ��� �ٸ� ó���� �ϰų� ó������ �ʵ��� ����
//    // ���� ���, ��Ŭ���� ���� Ŭ���� ��� �̺�Ʈ�� ó������ �ʰ� �ٸ� ������ ������ �� �ֽ��ϴ�.
//    return Reply.Unhandled();
//
//}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);

}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    if(DragItemVisualClass)
    { 
        const TObjectPtr<UDragItemVisual> DragVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualClass);
        DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);
        DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());
        DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));

        ItemReference->NumericData.bIsStackable
            ? DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity))
            : DragVisual->ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);

        DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));

        UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
        DragItemOperation->SourceItem = ItemReference;
        DragItemOperation->SourceInventory = ItemReference->OwningInventory;

        DragItemOperation->DefaultDragVisual = DragVisual;
        DragItemOperation->Pivot = EDragPivot::TopLeft;

        OutOperation = DragItemOperation;
    }

}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}