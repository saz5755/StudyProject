// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ItemDataStructs.h"
#include "../Character/PlayerCharacter.h"
#include "ItemBase.generated.h"


UCLASS()
class PROJECTOVERKILL_API UItemBase : public UObject
{
	GENERATED_BODY()
	
// Public 변수 및 속성 Section
public:

	/*UPROPERTY()
	UInventoryComponent* OwningInventory;*/

	// UI에 나타낼 최소값을 1로 설정하면서 0개로 존재하지 않는다면 나타내지 않도록 한다.
	UPROPERTY(VisibleAnywhere, Category = "Item Data", meta = (UIMin=1, UIMax=100))
	int32 Quantity;
	
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData NumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;

// Public Functions Section
public:
	UItemBase();

	UFUNCTION(category = "Item")
	UItemBase* CreateItemCopy() const;
	
	UFUNCTION(category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * NumericData.Weight; };

	UFUNCTION(category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return  NumericData.Weight; };

	UFUNCTION(category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == NumericData.MaxStackSize; };
	
	UFUNCTION(category = "Item")
	void SetQuantity(const int32 NewQuantity);

	// PlayerCharacter 받아오면 될듯?
	UFUNCTION(category = "Item")
	virtual void Use(APlayerCharacter* Character);

protected:
	bool operator==(const FName& OtherID) const
	{
		return ID == OtherID;
	}
};
