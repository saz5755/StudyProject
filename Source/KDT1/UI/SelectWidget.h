// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Blueprint/UserWidget.h"
#include "SelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API USelectWidget : public UUserWidget
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
