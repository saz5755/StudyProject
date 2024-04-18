// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemDataStructs.h"
#include "UObject/NoExportTypes.h"
#include "ItemManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTOVERKILL_API UItemManager : public UObject
{
	GENERATED_BODY()

public:
	UItemManager();

protected:
	UDataTable* ItemDataTable;

public:
	const FItemData* FindItem(const FString& Name)	const;
};
