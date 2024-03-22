// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/TileView.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTileWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTOVERKILL_API UInventoryTileWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UTileView* mTileView;

protected:
	virtual void NativeConstruct();
};
