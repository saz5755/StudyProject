#include "Breakable/BreakableActor_SpawnWeapon.h"
#include "../Item/ItemBase.h"
#include "Item/ItemWeapon.h"

ABreakableActor_SpawnWeapon::ABreakableActor_SpawnWeapon()
{
}

void ABreakableActor_SpawnWeapon::GetHit(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit(ImpactPoint, Hitter);

	FVector Location = GetActorLocation();
	Location.Z += 75.0f;

	UWorld* World = GetWorld();
}
