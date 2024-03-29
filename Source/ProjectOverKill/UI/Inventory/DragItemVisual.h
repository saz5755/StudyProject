#pragma once

#include "../../GameInfo.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Blueprint/UserWidget.h"
#include "DragItemVisual.generated.h"

UCLASS()
class PROJECTOVERKILL_API UDragItemVisual : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	UBorder* ItemBorder;

	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	UTextBlock* ItemQuantity;
	
};
