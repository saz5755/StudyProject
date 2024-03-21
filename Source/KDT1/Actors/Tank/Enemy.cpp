// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/Enemy.h"
#include "Misc/NameTable.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	
	Collider->SetupAttachment(GetRootComponent());
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collider->SetCollisionProfileName(NameTable::Collision::Enemy);
	Collider->bDynamicObstacle = true;

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent>(TEXT("MovementComponent"));
}

void AEnemy::SetEnemyData(const FEnemyTable* NewTable)
{
	EnemyTable = NewTable;
	if (!EnemyTable)
	{
		return;
	}

	StaticMeshComponent->SetStaticMesh(EnemyTable->StaticMesh);
	const int32 NumberOfMayerials = StaticMeshComponent->GetMaterials().Num();
	DynamicMaterials.Empty();
	DynamicMaterials.Reserve(NumberOfMayerials);
	for (int32 i = 0; i < NumberOfMayerials; ++i)
	{
		UMaterialInstanceDynamic* MID = StaticMeshComponent->CreateDynamicMaterialInstance(i, StaticMeshComponent->GetMaterial(i));
		DynamicMaterials.Add(MID);
	}
	Collider->SetSphereRadius(EnemyTable->ColliderRadius);

	for (auto It : DynamicMaterials)
	{
		It->SetScalarParameterValue(TEXT("Dissolve"), 1.f);
	}

	HP = EnemyTable->HP;
}

float AEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	HP -= NewDamage;
	if (HP <= 0.f)
	{
		bPendingDie = true;
		Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		GetWorld()->GetTimerManager().SetTimer(PaperBurnTimerHandle,
			// this, &ThisClass::FunctionName
			[this]()
			{
				Destroy();
			},
			1.2f * 5.f, false);
	}

	return NewDamage;
}

void AEnemy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (EnemyTableHandle.IsNull()) { return; }
	if (EnemyTableHandle.RowName == TEXT("None")) { return; }

	const FEnemyTable* NewProjectileTable = EnemyTableHandle.GetRow<FEnemyTable>(TEXT(""));
	ensure(NewProjectileTable);
	if (EnemyTable == NewProjectileTable) { return; }
	SetEnemyData(NewProjectileTable);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(PaperBurnTimerHandle);
	PaperBurnTimerHandle.Invalidate();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPendingDie)
	{
		Dissolve -= DeltaTime * 0.2f;
		for (auto It : DynamicMaterials)
		{
			It->SetScalarParameterValue(TEXT("Dissolve"), Dissolve);
		}
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

