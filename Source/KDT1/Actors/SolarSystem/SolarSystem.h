// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolarSystem/SolarSystemComponent.h"
#include "SolarSystem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class KDT1_API ASolarSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASolarSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Axis = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USolarSystemComponent* Sun = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChildActorComponent* SunChildActorComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USolarSystemComponent* Earth = nullptr;

	// SkipSerialization
	UPROPERTY(EditAnywhere)
	int Value = 999;
};
