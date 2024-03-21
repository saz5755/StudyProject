// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemActor.h"
#include "ItemWeapon.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API AItemWeapon : public AItemActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemWeapon();

protected:
	USkeletalMeshComponent* mMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetMesh(USkeletalMesh* Mesh);
	void SetMesh(const FString& Path);
};
