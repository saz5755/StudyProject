// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "KDT1PhysicalMaterial.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTOVERKILL_API UKDT1PhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	USoundBase* mSound;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* mParticle;

public:
	UNiagaraSystem* GetParticle()
	{
		return mParticle;
	}

	USoundBase* GetSound()
	{
		return mSound;
	}
};