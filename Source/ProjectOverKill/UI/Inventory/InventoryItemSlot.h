#pragma once

#include "../../GameInfo.h"

#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "Blueprint/UserWidget.h"

#include "InventoryItemSlot.generated.h"

class UInventoryTooltip;
class UDragItemVisual;
class UItemBase;
class APlayerController;
class APickup;

UCLASS()
class PROJECTOVERKILL_API UInventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetItemReference(UItemBase* ItemIn) { ItemReference = ItemIn; };
	FORCEINLINE UItemBase* GetItemReference() const { return ItemReference; };
		
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
	TSubclassOf<UDragItemVisual> DragItemVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
	TSubclassOf<UInventoryTooltip> ToolTipClass;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
	UItemBase* ItemReference;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
	UBorder* ItemBorder;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
	UImage* ItemIcon;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot") 
	UTextBlock* ItemQuantity;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot") 
	UInventoryItemSlot* Data;

	UPROPERTY()
	AMainPlayerController* PlayerController;

	UPROPERTY()
	UInventoryComponent* InventoryReference;	
	
	UFUNCTION(BlueprintCallable)
	void SetItem(UObject* ItemData);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	//virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
