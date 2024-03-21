// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItemData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class KDT1_API UInventoryItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UTexture2D* mIconTexture;
	FString		mName;
	int32		mCount;
	USkeletalMesh* mItemMesh;
	class UInventoryListItemWidget* mItemWidget;
};
