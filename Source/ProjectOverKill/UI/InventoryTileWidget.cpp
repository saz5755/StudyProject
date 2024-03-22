// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTileWidget.h"

void UInventoryTileWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mTileView = Cast<UTileView>(GetWidgetFromName(TEXT("TileView")));

	//mTileView->AddItem();
}
