// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SolarSystem/AstronomicalObject.h"
#include "Components/SolarSystem/SolarSystemComponent.h"
#include "Planet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class KDT1_API APlanet : public AAstronomicalObject
{
	GENERATED_BODY()
public:
	APlanet();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void Init() override;
	void CalculateNightSide();

protected:
	// 하나만 적용 가능!! (지구용)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSkyAtmosphere = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CloudStaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* CloudMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double CloudRotationSpeed = 20.0;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<USolarSystemComponent*> NaturalSatellites;
};
