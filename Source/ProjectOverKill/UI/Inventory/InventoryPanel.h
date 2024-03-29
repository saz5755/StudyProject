#pragma once

#include "../../GameInfo.h"

#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

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
	UWrapBox* InventoryPanel;

	UPROPERTY()
	UTextBlock * WeightInfo;

	UPROPERTY()
	UTextBlock* CapacityInfo;

	UPROPERTY()
	AMainPlayerController* PlayerController;

	UPROPERTY()
	UInventoryComponent* InventoryReference;


protected:
	void SetInfoText() const;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
