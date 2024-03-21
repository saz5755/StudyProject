// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Data/Projectile/ProjectileData.h"
#include "Components/SphereComponent.h"
#include "Enemy.generated.h"

UCLASS()
class KDT1_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
	void SetEnemyData(const FEnemyTable* NewTable);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	bool IsPendingDie() const { return bPendingDie; }

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RowType = "/Script/KDT1.EnemyTable"))
	FDataTableRowHandle EnemyTableHandle;
	const FEnemyTable* EnemyTable = nullptr;
	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstanceDynamic*> DynamicMaterials;
	FTimerHandle PaperBurnTimerHandle;

	UPROPERTY(EditAnywhere)
	float HP = 0;

	float Dissolve = 0.4f;
	bool bPendingDie = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* DefaultSceneRoot = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Collider = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPawnMovementComponent* MovementComponent;
};
