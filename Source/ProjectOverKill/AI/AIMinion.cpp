#include "AIMinion.h"
#include "DefaultAIController.h"
#include "MonsterAnimInstance.h"
#include "../Effect/EffectBase.h"
#include "MonsterState.h"

AAIMinion::AAIMinion()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Melee_Dusk.Minion_Lane_Melee_Dusk'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprint/Main/Monster/AB_Minion.AB_Minion_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);
	
	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -90.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mCapsule->SetCapsuleHalfHeight(90.f);
	mCapsule->SetCapsuleRadius(30.f);

	mTableRowName = TEXT("Minion");
}

void AAIMinion::BeginPlay()
{
	Super::BeginPlay();
}

void AAIMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIMinion::NormalAttack()
{
	FCollisionQueryParams	param(NAME_None, false, this);

	// 액터 위치 + 액터의 전방방향 * 50 이므로 현재 액터의 위치에서 앞으로 50cm 만큼 이동한
	// 위치를 시작위치로 구한다.
	FVector	StartLocation = GetActorLocation() + GetActorForwardVector() * 50.f;

	// 시작위치 + 액터의 전방방향 * 150 이므로 시작위치에서 앞으로 150cm 만큼 이동한
	// 위치를 끝 위치로 구한다.
	FVector	EndLocation = StartLocation + GetActorForwardVector() * 150.f;

	FHitResult	result;
	bool IsCollision = GetWorld()->SweepSingleByChannel(result, StartLocation, EndLocation,
		FQuat::Identity, ECC_GameTraceChannel5, FCollisionShape::MakeSphere(50.f),
		param);

#if ENABLE_DRAW_DEBUG

	// 구를 그린다.
	FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;

	/*DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
		75.f, 50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 3.f);*/

#endif

	if (IsCollision)
	{
		FDamageEvent	DmgEvent;
		result.GetActor()->TakeDamage(mMonsterState->mAttackPoint, DmgEvent, GetController(), this);

		// 이펙트 출력 및 사운드 재생.
		FActorSpawnParameters	SpawnParam;

		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEffectBase*	Effect = GetWorld()->SpawnActor<AEffectBase>(result.ImpactPoint,
			result.ImpactNormal.Rotation(), SpawnParam);

		Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonMinions/FX/Particles/Minions/Minion_melee/FX/Impacts/P_Minion_Impact_Default.P_Minion_Impact_Default'"));
	}
}
