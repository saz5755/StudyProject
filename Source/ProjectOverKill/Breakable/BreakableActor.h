#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

UCLASS()
class PROJECTOVERKILL_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Capsule;

public:	
	ABreakableActor();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);

	UFUNCTION(BlueprintCallable)
	virtual void GetHit(const FVector& ImpactPoint, AActor* Hitter);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Breakable Properties")
	TArray<TSubclassOf<class ATreasureActor>> TreasureClasses;

	UPROPERTY(EditAnywhere, Category = "Item Properties")
	TArray<TSubclassOf<class APickup>> PickUpItemClasses;

	bool bBroken = false;

};
