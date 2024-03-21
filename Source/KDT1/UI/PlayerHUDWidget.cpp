// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"

void UPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPlayerHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	mMPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));
}

void UPlayerHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPlayerHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPlayerHUDWidget::SetName(const FString& Text)
{
	NameText->SetText(FText::FromString(Text));
}

void UPlayerHUDWidget::SetHP(int32 HP, int32 HPMax)
{
	mHPBar->SetPercent(HP / (float)HPMax);
}

void UPlayerHUDWidget::SetMP(int32 MP, int32 MPMax)
{
	mMPBar->SetPercent(MP / (float)MPMax);
}
