#pragma once

#include "../Inventory/World/Pickup.h"
#include "ItemWeapon.generated.h"

UCLASS()
class PROJECTOVERKILL_API AItemWeapon : public APickup
{
	GENERATED_BODY()

public:
	AItemWeapon();

protected:
	USkeletalMeshComponent* mMesh;

protected:
	virtual void BeginPlay() override;

public:
	void SetMesh(USkeletalMesh* Mesh);
	void SetMesh(const FString& Path);

	static FLinearColor SetItemWeaponColor();
};
