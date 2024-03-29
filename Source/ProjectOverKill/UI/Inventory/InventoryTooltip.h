#pragma once

#include "../../GameInfo.h"

#include "Components/TextBlock.h"

#include "Blueprint/UserWidget.h"
#include "InventoryTooltip.generated.h"

class UInventoryItemSlot;

UCLASS()
class PROJECTOVERKILL_API UInventoryTooltip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	UInventoryItemSlot* InventorySlotBeginHovered;

	UPROPERTY()
	UTextBlock* ToolTipItemName;

	UPROPERTY()
	UTextBlock* ItemType;	
	
	UPROPERTY()
	UTextBlock* DamageValue;	
	
	UPROPERTY()
	UTextBlock* ArmorRating;

	UPROPERTY()
	UTextBlock* UsageText;

	UPROPERTY()
	UTextBlock* StackSize;

	UPROPERTY()
	UTextBlock* MaxStackSize;

	UPROPERTY()
	UTextBlock* StackWeight;

	UPROPERTY()
	UTextBlock* ItemDescription;

protected:
	virtual void NativeConstruct() override;

};
