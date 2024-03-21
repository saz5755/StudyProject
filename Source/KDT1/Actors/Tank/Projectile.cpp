// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/Projectile.h"
#include "Misc/NameTable.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 5.f;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));

	Collider->SetupAttachment(GetRootComponent());
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collider->SetCollisionProfileName(NameTable::Collision::Projectile);
	Collider->bDynamicObstacle = true;

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (ProjectileTableHandle.IsNull()) { return; }
	if (ProjectileTableHandle.RowName == TEXT("None")) { return; }

	const FProjectileTable* NewProjectileTable = ProjectileTableHandle.GetRow<FProjectileTable>(TEXT(""));
	ensure(NewProjectileTable);
	if (ProjectileTable == NewProjectileTable) { return; }

	SetProjectileData(NewProjectileTable);
}

void AProjectile::SetProjectileData(const FProjectileTable* NewTable)
{
	ProjectileTable = NewTable;
	if (!ProjectileTable)
	{
		return;
	}

	StaticMeshComponent->SetStaticMesh(ProjectileTable->StaticMesh);
	StaticMeshComponent->SetRelativeScale3D(ProjectileTable->Scale3D);
	StaticMeshComponent->SetRelativeRotation(ProjectileTable->MeshRotator);
	SetActorRelativeRotation(GetActorRotation() +  ProjectileTable->ActorRotator);
	Collider->SetSphereRadius(ProjectileTable->ColliderRadius);
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::ApplyDamage(Other, ProjectileTable->Damage, GetInstigatorController(), GetInstigator(), nullptr);

	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ProjectileTable)
	{
		return;
	}

	FVector Location = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector FanalLocation = Location + ForwardVector * ProjectileTable->Speed * DeltaTime;

	SetActorLocation(FanalLocation);
}

