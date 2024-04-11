#pragma once

#include "../GameInfo.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Ghost.generated.h"

UCLASS()
class PROJECTOVERKILL_API AGhost : public AActor
{
	GENERATED_BODY()
	
public:	
	AGhost();

protected:
	UPROPERTY(VisibleAnywhere)
	UPoseableMeshComponent* mMesh;

	UMaterialInterface* mGhostMaterial;

	TArray<UMaterialInstanceDynamic*>	mMaterialArray;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void CopySkeletalMesh(USkeletalMeshComponent* Mesh);
};
