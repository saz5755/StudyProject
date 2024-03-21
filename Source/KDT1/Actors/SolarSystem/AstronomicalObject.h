// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AstronomicalObject.generated.h"

UCLASS(BlueprintType, Blueprintable)
class KDT1_API AAstronomicalObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstronomicalObject();
	float GetRotationSpeed() const { return RotationSpeed; }
	void SetRotationSpeed(const float InRotationSpeed) { RotationSpeed = InRotationSpeed; }

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void Init();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Axis = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* AstronomicalStaticMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* AstronomicalMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double RotationSpeed = 40.;

protected:
	UMaterialInstanceDynamic* AstronomicalDynamicMaterial = nullptr;
};
