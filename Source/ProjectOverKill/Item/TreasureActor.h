#pragma once

#include "../Inventory/World/Pickup.h"
#include "TreasureActor.generated.h"

UCLASS()
class PROJECTOVERKILL_API ATreasureActor : public APickup
{
	GENERATED_BODY()

public:
	ATreasureActor();

	virtual void OnSphereOverlap(AActor* OtherActor) override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* AcquireSound;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TreasureMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Treasure Properties")
	int32 Gold;

};
