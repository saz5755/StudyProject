// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Tank.generated.h"

UCLASS()
class KDT1_API ATank : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATank();

public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Attack"))
	void ReceiveAttack();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ZoomIn"))
	void ReceiveZoomIn();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ZoomOut"))
	void ReceiveZoomOut();

	void Attack();
	void ZoomIn();
	void ZoomOut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ProjectileSpawnLocation = nullptr;

	bool bFireDelay = false;
	float FireDelay = 0.1f;
	FTimerHandle FireTimerHandle;
};
