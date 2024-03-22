// Fill out your copyright notice in the Description page of Project Settings.


#include "MainViewportWidget.h"
#include "PlayerHUDWidget.h"
#include "UObject/UnrealTypePrivate.h"
#include "Animation/WidgetAnimation.h"
#include "MovieScene.h"

void UMainViewportWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mInventoryButton = Cast<UButton>(GetWidgetFromName(TEXT("InventoryButton")));

	mInventoryButton->OnClicked.AddDynamic(this,
		&UMainViewportWidget::InventoryButtonClick);

	mInventoryButton->OnHovered.AddDynamic(this,
		&UMainViewportWidget::InventoryButtonHovered);

	mInventoryButton->OnUnhovered.AddDynamic(this,
		&UMainViewportWidget::InventoryButtonUnHovered);

	BindAnimation();

	mCheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBoxTest")));

	mCheckBox->OnCheckStateChanged.AddDynamic(this,
		&UMainViewportWidget::CheckStateTest);

	mSlider = Cast<USlider>(GetWidgetFromName(TEXT("SliderTest")));

	mSlider->OnValueChanged.AddDynamic(this,
		&UMainViewportWidget::ChangeSliderValue);

	mSlider->SetValue(600.f);
	//mSpinBox->SetValue(600.f);

	mComboBox = Cast<UComboBoxString>(GetWidgetFromName(TEXT("ComboBoxTest")));

	mComboBox->AddOption(TEXT("Option Add1"));
	mComboBox->OnSelectionChanged.AddDynamic(this,
		&UMainViewportWidget::ComboBoxSelectionChange);

	mEditTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBoxTest")));

	mEditTextBox->OnTextChanged.AddDynamic(this,
		&UMainViewportWidget::TextChanged);
	mEditTextBox->OnTextCommitted.AddDynamic(this,
		&UMainViewportWidget::TextCommit);
}

void UMainViewportWidget::SetName(const FString& Text)
{
	UI_PlayerHUD->SetName(Text);
}

void UMainViewportWidget::SetHP(int32 HP, int32 HPMax)
{
	UI_PlayerHUD->SetHP(HP, HPMax);
}

void UMainViewportWidget::SetMP(int32 MP, int32 MPMax)
{
	UI_PlayerHUD->SetMP(MP, MPMax);
}

void UMainViewportWidget::InventoryButtonClick()
{
	//ESlateVisibility::Visible
}

void UMainViewportWidget::InventoryButtonHovered()
{
	PlayAnimation(mButtonScale, 0.f, 1,
		EUMGSequencePlayMode::Forward);
}

void UMainViewportWidget::InventoryButtonUnHovered()
{
	PlayAnimation(mButtonScale, 0.f, 1,
		EUMGSequencePlayMode::Reverse);
}

void UMainViewportWidget::CheckStateTest(bool IsChecked)
{
	if (IsChecked)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f,
			FColor::Red, TEXT("Check"));
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f,
			FColor::Red, TEXT("UnCheck"));
	}
}

void UMainViewportWidget::ChangeSliderValue(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f,
		FColor::Red, FString::Printf(TEXT("Value : %.5f"),
			Value));
}

void UMainViewportWidget::ComboBoxSelectionChange(
	FString Option, ESelectInfo::Type Type)
{
	int32	Index = mComboBox->GetSelectedIndex();
	FString Option1 = mComboBox->GetOptionAtIndex(Index);

	GEngine->AddOnScreenDebugMessage(-1, 1.f,
		FColor::Blue, Option);

	switch (Type)
	{
	case ESelectInfo::OnKeyPress:
		break;
	case ESelectInfo::OnNavigation:
		break;
	case ESelectInfo::OnMouseClick:
		break;
	case ESelectInfo::Direct:
		break;
	}
}

void UMainViewportWidget::TextChanged(const FText& Text)
{
	/*GEngine->AddOnScreenDebugMessage(-1, 1.f,
		FColor::Red, Text.ToString());*/
}

void UMainViewportWidget::TextCommit(const FText& Text, 
	ETextCommit::Type Type)
{
	switch (Type)
	{
	case ETextCommit::Default:
		GEngine->AddOnScreenDebugMessage(-1, 1.f,
			FColor::Red, Text.ToString() + TEXT("_Default"));
		break;
	case ETextCommit::OnCleared:
		GEngine->AddOnScreenDebugMessage(-1, 1.f,
			FColor::Red, Text.ToString() + TEXT("_Cleared"));
		mEditTextBox->SetText(FText::FromString(TEXT("")));
		//mEditTextBox->GetText();
		//mEditTextBox->GetText();
		break;
	case ETextCommit::OnEnter:
		GEngine->AddOnScreenDebugMessage(-1, 1.f,
			FColor::Red, Text.ToString());
		break;
	case ETextCommit::OnUserMovedFocus:
		GEngine->AddOnScreenDebugMessage(-1, 1.f,
			FColor::Red, Text.ToString() + TEXT("_Focus"));
		break;
	}
}

void UMainViewportWidget::BindAnimation()
{
	//TArray<FName>	NameArray;
	//NameArray.Add(TEXT("ButtonScale"));

	// ButtonScale Property를 얻어온다.
	FProperty* Prop = GetClass()->FindPropertyByName(TEXT("ButtonScale"));

	// FObjectProperty로 형변환한다.
	FObjectProperty* ObjProp = CastField<FObjectProperty>(Prop);

	if (ObjProp)
	{
		// WidgetAnimation 타입인지 판단한다.
		if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
		{
			// ObjectProperty로부터 실제 WidgetAnimation 객체를
			// 얻어온다.
			UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);

			// UObject로 얻어온 객체를 WidgetAnimation 타입으로
			// 형변환한다.
			UWidgetAnimation* Anim = Cast<UWidgetAnimation>(Obj);

			mButtonScale = Anim;
		}
	}
}
