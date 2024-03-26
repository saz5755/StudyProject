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
	
// Public ���� �� �Ӽ� Section
public:

	/*UPROPERTY()
	UInventoryComponent* OwningInventory;*/

	// UI�� ��Ÿ�� �ּҰ��� 1�� �����ϸ鼭 0���� �������� �ʴ´ٸ� ��Ÿ���� �ʵ��� �Ѵ�.
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

	// PlayerCharacter �޾ƿ��� �ɵ�?
	UFUNCTION(category = "Item")
	virtual void Use(APlayerCharacter* Character);

protected:
	bool operator==(const FName& OtherID) const
	{
		return ID == OtherID;
	}
};
