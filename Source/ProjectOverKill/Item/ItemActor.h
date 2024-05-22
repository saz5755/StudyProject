#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UCLASS()
class PROJECTOVERKILL_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemActor();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Blueprintcallable)
	virtual void OnSphereOverlap(AActor* OtherActor);

};
