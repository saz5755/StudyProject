// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/Tank.h"
#include "Data/Projectile/ProjectileData.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATank::ATank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATank::Attack()
{
	if (bFireDelay) { return; }
	bFireDelay = true;

	ReceiveAttack();
	UWorld* World = GetWorld();
	{
		UDataSubsystem* DataSubsystem = World->GetGameInstance()->GetSubsystem<UDataSubsystem>();
		const FProjectileTable* ProjectileTable = DataSubsystem->FindProjectile(TEXT("Test"));

		FRotator Rotator = ProjectileSpawnLocation->GetComponentRotation();
		FVector Translation = ProjectileSpawnLocation->GetComponentLocation();
		FTransform Transform(Rotator, Translation);

		AProjectile* NewProjectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(), Transform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		NewProjectile->SetProjectileData(ProjectileTable);

		UGameplayStatics::FinishSpawningActor(NewProjectile, Transform);
	}
	
	World->GetTimerManager().SetTimer(FireTimerHandle,
		// this, &ThisClass::FunctionName
		[this]()
		{
			bFireDelay = false;
		},
		FireDelay, false);
}

void ATank::ZoomIn()
{
	ReceiveZoomIn();
}

void ATank::ZoomOut()
{
	ReceiveZoomOut();
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	ZoomOut();
}

void ATank::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	FireTimerHandle.Invalidate();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

