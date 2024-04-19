#include "Breakable/BreakableActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Item//TreasureActor.h"
#include "../Inventory/World/Pickup.h"
#include "../Item/ItemBase.h"
#include "Item/ItemWeapon.h"
#include "Item/ItemArmor.h"

ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	SetRootComponent(GeometryCollection);
	GeometryCollection->SetGenerateOverlapEvents(true);
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(GetRootComponent());
	Capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void ABreakableActor::GetHit(const FVector& ImpactPoint, AActor* Hitter)
{
	if (bBroken) return;
	bBroken = true;

	UE_LOG(LogTemp, Warning, TEXT("BreakableActor - GetHit"));
	
	CreateFields(ImpactPoint);
	
	FVector Location = GetActorLocation();
	Location.Z += 75.0f;

	UWorld* World = GetWorld();
	if (World && TreasureClasses.Num() > 0)
	{
		const int32 Selection = FMath::RandRange(0, TreasureClasses.Num() - 1);
		World->SpawnActor<ATreasureActor>(TreasureClasses[Selection], Location, GetActorRotation());
	}
	if (World && PickUpItemClasses.Num() > 0)
	{
		const int32 Selection = FMath::RandRange(0, PickUpItemClasses.Num() - 1);
		/*APickup* PickupActor = World->SpawnActor<APickup>(PickUpItemClasses[Selection], Location, GetActorRotation());

		PickupActor->SetItemID(TEXT("Weapon01"));*/

		AItemArmor* PickupActor = NewObject<AItemArmor>();
		PickupActor = World->SpawnActor<AItemArmor>(Location, GetActorRotation());

		PickupActor->SetItemID(TEXT("Armor"));
		PickupActor->InitializePickup(UItemBase::StaticClass(), 1);
	}
}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

