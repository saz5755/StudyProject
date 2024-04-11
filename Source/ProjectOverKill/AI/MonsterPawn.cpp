#include "MonsterPawn.h"
#include "DefaultAIController.h"
#include "MonsterAnimInstance.h"
#include "../Interfaces/HitInterface.h"
#include "MonsterState.h"
#include "Effect/EffectBase.h"

UDataTable* AMonsterPawn::mMonsterDataTable = nullptr;

const FMonsterData* AMonsterPawn::FindMonsterData(
	const FString& Name)
{
	// 정상적으로 탐색이 되어서 찾았다면 찾아준 메모리 주소를 반환하고
	// 못찾았다면 nullptr을 반환한다.
	return mMonsterDataTable->FindRow<FMonsterData>(*Name, TEXT(""));
}

AMonsterPawn::AMonsterPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mState = CreateDefaultSubobject<UMonsterState>(TEXT("MonsterState"));

	mMonsterState = Cast<UMonsterState>(mState);

	AIControllerClass = ADefaultAIController::StaticClass();

	mCapsule->SetCollisionProfileName(TEXT("Enemy"));

	static ConstructorHelpers::FObjectFinder<UDataTable>
		MonsterTable(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Main/Monster/DT_MonsterData.DT_MonsterData'"));

	if (!IsValid(mMonsterDataTable) && MonsterTable.Succeeded())
		mMonsterDataTable = MonsterTable.Object;

	mDissolveEnable = false;
	mDissolve = 1.5f;

	mDissolveDuration = 1.f;
	mDissolveTime = 0.f;
}

void AMonsterPawn::ChangeAIAnimType(uint8 AnimType)
{
	mAnimInst->ChangeAnimType((EMonsterAnimType)AnimType);
}

void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();

	mAIInfo = new FMonsterInfo;

	FMonsterInfo* MonsterInfo = (FMonsterInfo*)mAIInfo;

	const FMonsterData* Data = FindMonsterData(mTableRowName);

	mAttackPoint = Data->mAttackPoint;

	MonsterInfo->mAttackPoint = Data->mAttackPoint;
	MonsterInfo->mArmorPoint = Data->mArmorPoint;
	MonsterInfo->mHP = Data->mHPMax;
	MonsterInfo->mHPMax = Data->mHPMax;
	MonsterInfo->mMP = Data->mMPMax;
	MonsterInfo->mMPMax = Data->mMPMax;
	MonsterInfo->mMoveSpeed = Data->mMoveSpeed;
	MonsterInfo->mAttackDistance = Data->mAttackDistance;
	MonsterInfo->mInteractionDistance = Data->mTraceDistance;

	mMovement->MaxSpeed = MonsterInfo->mMoveSpeed;

	// Cast<>() 함수는 형변환을 해주는 함수이다.
	// <> 안에 지정된 타입과 다른 타입으로 생성된 객체인 경우 nullptr을 반환한다.
	mAnimInst = Cast<UMonsterAnimInstance>(mMesh->GetAnimInstance());

	mCapsule->OnComponentBeginOverlap.AddDynamic(this,
		&AMonsterPawn::BeginOverlap);
}

void AMonsterPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	mState->mDataTableRowName = mTableRowName;

	// 메쉬가 가지고 있는 머티리얼이 몇개인지를 얻어온다.
	int32	ElementCount = mMesh->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);

		mMaterialArray.Add(Mtrl);
	}
}

void AMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mHitEnable)
	{
		mHitTime += DeltaTime;

		if (mHitTime >= mHitDuration)
		{
			mHitEnable = false;
			mHitTime = 0.f;

			for (auto Mtrl : mMaterialArray)
			{
				Mtrl->SetScalarParameterValue(TEXT("HitEnable"), 0.f);
			}
		}
	}

	if (mDissolveEnable)
	{
		// 시간을 구한다.
		mDissolveTime += DeltaTime;

		// 지속시간과의 비율을 구한다.
		float	Ratio = mDissolveTime / mDissolveDuration;

		// 2.5 : 전체 구간
		// 1.5 : 시작
		// Ratio : 전체 구간 비율
		mDissolve = 1.5f - 2.5f * Ratio;

		for (auto Mtrl : mMaterialArray)
		{
			Mtrl->SetScalarParameterValue(TEXT("Dissolve"), mDissolve);
		}

		if (mDissolve <= -1.f)
			Destroy();
	}
}

float AMonsterPawn::TakeDamage(float DamageAmount, 
	FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent,
		EventInstigator, DamageCauser);

	if (!mHitEnable)
	{
		for (auto Mtrl : mMaterialArray)
		{
			Mtrl->SetScalarParameterValue(TEXT("HitEnable"), 1.f);
		}

		mHitEnable = true;
		mHitTime = 0.f;
	}

	mMonsterState->mHP -= DamageAmount;

	if (mMonsterState->mHP <= 0)
	{
		mAnimInst->ChangeAnimType(EMonsterAnimType::Death);
	}

	return DamageAmount;
}

void AMonsterPawn::NormalAttack()
{
}

void AMonsterPawn::GetHit(const FVector& ImpactPoint, AActor* Hitter)
{
	//mAnimInst->ChangeAnimType(EMonsterAnimType::HitReact);

	if (mAnimInst)
	{
		const FVector Forward = GetActorForwardVector();
		const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);

		const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();
		const double CosTheta = FVector::DotProduct(Forward, ToHit);
		double Theta = FMath::Acos(CosTheta);
		Theta = FMath::RadiansToDegrees(Theta);

		const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
		if (CrossProduct.Z < 0)
		{
			Theta *= -1.f;
		}

		////From Back
		//mAnimInst->AnimNotify_HitReact(1);

		//if (Theta >= -45.f && Theta < 45.f)
		//{
		//	// FromFront
		//	mAnimInst->AnimNotify_HitReact(0);
		//}
		//else if (Theta >= -135.f && Theta < -45.f)
		//{
		//	// FromLeft
		//	mAnimInst->AnimNotify_HitReact(2);
		//}
		//else if (Theta >= 45.f && Theta < 135.f)
		//{
		//	// FromRight
		//	mAnimInst->AnimNotify_HitReact(3);
		//}

		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		//	FString::Printf(TEXT("Theta %f"), Theta));
	}

	FActorSpawnParameters SpawnParam;

	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(
		GetActorLocation(),
		GetActorRotation(), SpawnParam);

	Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonMinions/FX/Particles/Minions/Minion_melee/FX/Impacts/P_Minion_Impact_Default.P_Minion_Impact_Default'"));
	Effect->SetSoundAsset(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/sfx_HitMonster.sfx_HitMonster'"));

}

void AMonsterPawn::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		TEXT("Monster Overlap"));
}

void AMonsterPawn::OnDissolve()
{
	mDissolveEnable = true;

	for (auto Mtrl : mMaterialArray)
	{
		Mtrl->SetScalarParameterValue(TEXT("DissolveEnable"), 1.f);
	}
}

