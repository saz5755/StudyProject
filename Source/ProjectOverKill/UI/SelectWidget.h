#pragma once

#include "../GameInfo.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Blueprint/UserWidget.h"
#include "SelectWidget.generated.h"


UCLASS()
class PROJECTOVERKILL_API USelectWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UButton* mStartButton;
	UEditableTextBox* mInputName;

protected:
	virtual void NativeConstruct();

public:
	void SetStartButtonEnable(bool Enable);

	UFUNCTION()
	void StartButtonClick();
};
