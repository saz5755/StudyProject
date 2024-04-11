#pragma once

#include "../../GameInfo.h"

#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/ListView.h"

#include "Blueprint/UserWidget.h"
#include "InventoryPanel.generated.h"

class UInventoryItemSlot;
class AMainPlayerController;
class UInventoryComponent;

UCLASS()
class PROJECTOVERKILL_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void RefreshInventory();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryItemSlot> IventorySlotClass;

	UPROPERTY()
	UListView* InventoryListview;

	UPROPERTY()
	UTextBlock * WeightInfo;

	UPROPERTY()
	UTextBlock* CapacityInfo;

	UPROPERTY()
	AMainPlayerController* PlayerController;

	UPROPERTY()
	UInventoryComponent* InventoryReference;

	UPROPERTY()
	UItemBase* SelectItem;
	
	UFUNCTION()
	void ItemDoubleClick(UObject* Obj);

protected:
	void SetInfoText() const;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
