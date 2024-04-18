// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

UItemManager::UItemManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>	TableAsset(TEXT("/Script/Engine.DataTable'/Game/InVentory/ItemData/MundaneItems.MundaneItems'"));

	if (TableAsset.Succeeded())
		ItemDataTable = TableAsset.Object;
}

const FItemData* UItemManager::FindItem(const FString& Name)	const
{
	return ItemDataTable->FindRow<FItemData>(*Name, TEXT(""));
}
