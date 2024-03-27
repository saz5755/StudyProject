#pragma once

#include "CoreMinimal.h"
#include "ItemDataStructs.h"
#include "../Character/PlayerCharacter.h"
#include "ItemBase.generated.h"

class UInventoryComponent;

UCLASS()
class PROJECTOVERKILL_API UItemBase : public UObject
{
	GENERATED_BODY()
	
// Public 변수 및 속성 Section
public:

	UPROPERTY()
	UInventoryComponent* OwningInventory;

	// UI에 나타낼 최소값을 1로 설정하면서 0개로 존재하지 않는다면 나타내지 않도록 한다.
	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName ID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 Quantity;
	
	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemTextData TextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemNumericData NumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemAssetData AssetData;

	bool bIsCopy;
	bool bIsPickup;

// Public Functions Section
public:
	UItemBase();

	void ResetItemFlags();

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

	UFUNCTION(category = "Item")
	virtual void Use(APlayerCharacter* Character);

protected:
	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}
};
