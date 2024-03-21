// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "InventoryListWidget.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API UInventoryListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UListView* mInventoryList;
	UButton* mCloseButton;
	class UInventoryListItemWidget* mSelectWidget;

protected:
	virtual void NativeConstruct();

protected:
	UFUNCTION()
	void ItemClick(UObject* Obj);

	UFUNCTION()
	void ItemDoubleClick(UObject* Obj);

	UFUNCTION()
	void ItemHoveredChange(UObject* Obj, bool IsHovered);

	UFUNCTION()
	void CloseButtonClick();
};
