// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/SpinBox.h"
#include "Types/SlateEnums.h"
#include "Blueprint/UserWidget.h"
#include "MainViewportWidget.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API UMainViewportWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UPlayerHUDWidget* UI_PlayerHUD;

	UButton* mInventoryButton;

	UCheckBox* mCheckBox;
	USlider* mSlider;
	UComboBoxString* mComboBox;
	USpinBox* mSpinBox;
	UEditableTextBox* mEditTextBox;

	//UPROPERTY(meta=(BindWidgetAnim), Transient)
	//UWidgetAnimation* ButtonScale;

	UWidgetAnimation* mButtonScale;

protected:
	virtual void NativeConstruct();

public:
	void SetName(const FString& Text);
	void SetHP(int32 HP, int32 HPMax);
	void SetMP(int32 MP, int32 MPMax);

protected:
	UFUNCTION()
	void InventoryButtonClick();

	UFUNCTION()
	void InventoryButtonHovered();

	UFUNCTION()
	void InventoryButtonUnHovered();

	UFUNCTION()
	void CheckStateTest(bool IsChecked);

	UFUNCTION()
	void ChangeSliderValue(float Value);

	UFUNCTION()
	void ComboBoxSelectionChange(FString Option,
		ESelectInfo::Type Type);

	UFUNCTION()
	void TextChanged(const FText& Text);

	UFUNCTION()
	void TextCommit(const FText& Text, ETextCommit::Type Type);

private:
	void BindAnimation();
};
