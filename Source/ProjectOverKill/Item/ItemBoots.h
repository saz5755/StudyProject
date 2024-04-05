// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemActor.h"
#include "ItemBoots.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTOVERKILL_API AItemBoots : public AItemActor
{
	GENERATED_BODY()
	
public:
	AItemBoots();

protected:
	USkeletalMeshComponent* mMesh;

protected:
	virtual void BeginPlay() override;

public:
	void SetMesh(USkeletalMesh* Mesh);
	void SetMesh(const FString& Path);
};
