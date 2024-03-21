// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Ghost.generated.h"

UCLASS()
class KDT1_API AGhost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhost();

protected:
	UPROPERTY(VisibleAnywhere)
	UPoseableMeshComponent* mMesh;

	UMaterialInterface* mGhostMaterial;

	TArray<UMaterialInstanceDynamic*>	mMaterialArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CopySkeletalMesh(USkeletalMeshComponent* Mesh);
};
