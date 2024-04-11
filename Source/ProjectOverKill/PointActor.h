#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointActor.generated.h"

UCLASS()
class PROJECTOVERKILL_API APointActor : public AActor
{
	GENERATED_BODY()
	
protected:
	USceneComponent* mRoot;

	UPROPERTY(EditAnywhere)
	UBoxComponent* mTrigger;

public:	
	APointActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
