#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "ProjectileData.generated.h"

USTRUCT()
struct FEnemyTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float ColliderRadius = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HP = 1.f;
};

USTRUCT()
struct FProjectileTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	FVector Scale3D = FVector::OneVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	FRotator MeshRotator = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	FRotator ActorRotator = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float ColliderRadius = 32.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float Damage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float Speed = 200.f;
};