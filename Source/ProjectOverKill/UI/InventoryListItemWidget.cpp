// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryListItemWidget.h"
#include "InventoryItemData.h"

void UInventoryListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mIconImage = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	mNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	mCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
	mSelection = Cast<UImage>(GetWidgetFromName(TEXT("Selection")));
}

void UInventoryListItemWidget::SetItemData(
	UObject* ItemData)
{
	UInventoryItemData* Data = Cast<UInventoryItemData>(ItemData);

	mItemData = Data;

	Data->mItemWidget = this;

	mIconImage->SetBrushFromTexture(Data->mIconTexture);
	mNameText->SetText(FText::FromString(Data->mName));
	mCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Data->mCount)));
}

void UInventoryListItemWidget::SetSelectionColor(
	float r, float g, float b, float a)
{
	FSlateColor	Color(FLinearColor(r, g, b, a));

	mSelection->SetBrushTintColor(Color);
}
