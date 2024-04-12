#pragma once

#include "Item/ItemActor.h"
#include "TreasureActor.generated.h"

UCLASS()
class PROJECTOVERKILL_API ATreasureActor : public AItemActor
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

};
