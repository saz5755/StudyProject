#pragma once

#include "../GameInfo.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "InventoryListItemWidget.generated.h"


UCLASS()
class PROJECTOVERKILL_API UInventoryListItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UImage* mIconImage;
	UTextBlock* mNameText;
	UTextBlock* mCountText;
	UImage* mSelection;
	class UInventoryItemData* mItemData;

protected:
	virtual void NativeConstruct();

protected:
	UFUNCTION(BlueprintCallable)
	void SetItemData(UObject* ItemData);

public:
	void SetSelectionColor(float r, float g, float b, float a);
};
