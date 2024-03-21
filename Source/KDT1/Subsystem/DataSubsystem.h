#pragma once
#include "CoreMinimal.h"
#include "Data/Projectile/ProjectileData.h"
#include "DataSubsystem.generated.h"

UCLASS()
class UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UDataSubsystem();

	const FProjectileTable* FindProjectile(const FName& InKey);
	const FEnemyTable* FindEnemy(const FName& InKey);

protected:
	UPROPERTY()
	UDataTable* ProjectileDataTable;
	UPROPERTY()
	UDataTable* EnemyDataTable;
};