#include "DataSubsystem.h"

UDataSubsystem::UDataSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Tank/DT_Projectile.DT_Projectile'"));
		ensure(Asset.Object);
		ProjectileDataTable = Asset.Object;
	}

	/*{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Tank/DT_Projectile.DT_Projectile'"));
		ensure(Asset.Object);
		EnemyDataTable = Asset.Object;
	}*/
}

const FProjectileTable* UDataSubsystem::FindProjectile(const FName& InKey)
{
	FProjectileTable* Table = ProjectileDataTable->FindRow<FProjectileTable>(InKey, TEXT(""));
	ensure(Table);
	return Table;
}

const FEnemyTable* UDataSubsystem::FindEnemy(const FName& InKey)
{
	FEnemyTable* Table = EnemyDataTable->FindRow<FEnemyTable>(InKey, TEXT(""));
	ensure(Table);
	return Table;
}
