#pragma once

#include "../Inventory/World/Pickup.h"
#include "ItemArmor.generated.h"

UCLASS()
class PROJECTOVERKILL_API AItemArmor : public APickup
{
	GENERATED_BODY()

public:
	AItemArmor();

protected:
	USkeletalMeshComponent* mMesh;

protected:
	virtual void BeginPlay() override;

public:
	void SetMesh(USkeletalMesh* Mesh);
	void SetMesh(const FString& Path);

	static FLinearColor SetItemArmorColor();

};
