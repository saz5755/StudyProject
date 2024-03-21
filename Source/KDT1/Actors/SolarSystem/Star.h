// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SolarSystem/AstronomicalObject.h"
#include "Components/PointLightComponent.h"
#include "Star.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class KDT1_API AStar : public AAstronomicalObject
{
	GENERATED_BODY()
	
public:
	AStar();

	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void Init() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPointLightComponent* PointLight = nullptr;

private:
	float AccTime = 0.f;
	float PlusMinus = 1;
};