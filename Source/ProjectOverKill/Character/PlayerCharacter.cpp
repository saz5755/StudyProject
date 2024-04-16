#include "PlayerCharacter.h"
#include "Player/PlayerAnimInstance.h"
#include "../Effect/EffectBase.h"
#include "Player/POKPlayerState.h"
#include "Player/MainPlayerController.h"
#include "../UI/MainViewportWidget.h"

#include "../Item/ItemWeapon.h"
#include "../Item/ItemHelmet.h"
#include "../Item/ItemArmor.h"
#include "../Item/ItemBoots.h"

#include "../Effect/Ghost.h"
#include "../Material/PhysicalMaterial/POKPhysicalMaterialBase.h"
#include "NiagaraActor.h"
#include "DrawDebugHelpers.h"
#include "../Interfaces/HitInterface.h"
#include "Breakable/BreakableActor.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mFaceCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("FaceCapture"));

	mFaceCapture->SetupAttachment(GetMesh());

	mFaceCapture->PrimitiveRenderMode = 
		ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	mFaceCapture->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D>
		FaceTarget(TEXT("/Script/Engine.TextureRenderTarget2D'/Game/Blueprint/Main/RT_PlayerFace.RT_PlayerFace'"));

	if (FaceTarget.Succeeded())
		mFaceCapture->TextureTarget = FaceTarget.Object;

	mCameraArm->SetupAttachment(GetCapsuleComponent());
	mCamera->SetupAttachment(mCameraArm);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	//SetCanBeDamaged(true);

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Character 클래스의 SkeletalMeshComponent가 가지고 있는 AnimInstance 객체를 얻어온다.
	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	mState = GetPlayerState<APOKPlayerState>();

	mFaceCapture->ShowOnlyActors.Add(this);

	FActorSpawnParameters	param;

	param.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	mWeapon = GetWorld()->SpawnActor<AItemWeapon>(
		FVector::ZeroVector, FRotator::ZeroRotator,
		param);

	mWeapon->AttachToComponent(GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		TEXT("WeaponSocket_L"));
	
	mHelmet = GetWorld()->SpawnActor<AItemHelmet>(
		FVector::ZeroVector, FRotator::ZeroRotator,
		param);

	mHelmet->AttachToComponent(GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		TEXT("HelmetSocket"));
	
	mArmor = GetWorld()->SpawnActor<AItemArmor>(
		FVector::ZeroVector, FRotator::ZeroRotator,
		param);

	mArmor->AttachToComponent(GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		TEXT("ArmorSocket"));
	
	mBoots = GetWorld()->SpawnActor<AItemBoots>(
		FVector::ZeroVector, FRotator::ZeroRotator,
		param);

	mBoots->AttachToComponent(GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		TEXT("BootsSocket"));

}

void APlayerCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	int32	Dmg = DamageAmount - mState->mArmorPoint;

	Dmg = Dmg < 1 ? 1 : Dmg;

	mState->mHP -= Dmg;

	if (mState->mHP <= 0)
	{
		mState->mHP = 0;
	}

	// UI에 전달한다.
	GetController<AMainPlayerController>()->GetMainWidget()->SetHP(
		mState->mHP, mState->mHPMax);

	return DamageAmount;
}

void APlayerCharacter::PlayAttackMontage()
{
	mAnimInst->PlayAttackMontage();
}

void APlayerCharacter::PlaySkillMontage(int32 Index)
{
	mAnimInst->PlaySkillMontage(Index);
}

void APlayerCharacter::PlayJump()
{
	// CanJump() : 점프 가능 상태인지를 판단한다.
	if (CanJump())
	{
		Jump();
		mAnimInst->PlayJump();
	}
}

void APlayerCharacter::NormalAttack()
{
	FCollisionQueryParams	param(NAME_None, false, this);

	APOKPlayerState* State = GetPlayerState<APOKPlayerState>();

	FVector	StartLocation = GetActorLocation();

	FVector	EndLocation = StartLocation + GetActorForwardVector() * State->mAttackDistance;

	TArray<FHitResult>	resultArray;
	bool IsCollision = GetWorld()->SweepMultiByChannel(resultArray, 
		StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(50.f), param);

#if ENABLE_DRAW_DEBUG

	// 구를 그린다.
	FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;

	/*DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
		State->mAttackDistance / 2.f, 50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 3.f);*/
#endif

	if (IsCollision)
	{
		for (int32 i = 0; i < resultArray.Num(); ++i)
		{
			FDamageEvent	DmgEvent;

			resultArray[i].GetActor()->TakeDamage(State->mAttackPoint, DmgEvent,
				GetController(), this);

			// 이펙트 출력 및 사운드 재생.
			FActorSpawnParameters SpawnParam;

			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(
				resultArray[i].ImpactPoint,
				resultArray[i].ImpactNormal.Rotation(), SpawnParam);
		
			IHitInterface* HitInterface = Cast<IHitInterface>(resultArray[i].GetActor());
			if (HitInterface)
			{
				HitInterface->GetHit(resultArray[i].ImpactPoint, resultArray[i].GetActor());
			}
		}
	}
}

void APlayerCharacter::SetWeaponMesh(USkeletalMesh* WeaponMesh)
{
	if (mWeapon)
	{
		mWeapon->SetMesh(WeaponMesh);
		//mAnimType = EPlayerAnimType::AttackMode;
	}
}

void APlayerCharacter::SetHelmetMesh(USkeletalMesh* HelmetMesh)
{
	if (mHelmet)
	{
	mHelmet->SetMesh(HelmetMesh);
	}
}

void APlayerCharacter::SetArmorMesh(USkeletalMesh* ArmorMesh)
{
	if (mArmor)
	{
		mArmor->SetMesh(ArmorMesh);
	}
}

void APlayerCharacter::SetBootsMesh(USkeletalMesh* BootsMesh)
{
	if (mBoots)
	{
		mBoots->SetMesh(BootsMesh);
	}
}

void APlayerCharacter::OnCustomDepthStencil(bool Enable)
{
	// CustomDepthStencil 버퍼에 값을 쓸지 결정한다.
	GetMesh()->SetRenderCustomDepth(Enable);
}

void APlayerCharacter::SetCustomStencil(int32 Stencil)
{
	mStencilValue = Stencil;

	GetMesh()->SetCustomDepthStencilValue(mStencilValue);
}

void APlayerCharacter::OnOutLine(bool OnOff)
{
	if (OnOff)
	{
		// 10의 자리의 값을 얻어온다.
		// 127일 경우 2가 나오게 된다.
		int32	Value = (mStencilValue / 10) % 10;

		// Value = 2 | 1 = 10 | 01 = 11
		Value |= 1;

		// 100의 자리의 값을 얻어온다.
		int32	Value100 = (mStencilValue / 100) % 10;
		int32	Color = mStencilValue % 10;

		mStencilValue = Value100 * 100 + Value * 10 + Color;
	}

	else
	{
		// 10의 자리의 값을 얻어온다.
		// 127일 경우 2가 나오게 된다.
		int32	Value = (mStencilValue / 10) % 10;

		// Value = 2 | 1 = 10 | 01 = 11
		if (Value & 1)
			Value ^= 1;

		// 100의 자리의 값을 얻어온다.
		int32	Value100 = (mStencilValue / 100) % 10;
		int32	Color = mStencilValue % 10;

		mStencilValue = Value100 * 100 + Value * 10 + Color;
	}

	GetMesh()->SetCustomDepthStencilValue(mStencilValue);
}

void APlayerCharacter::OnOcclusion(bool OnOff)
{
	if (OnOff)
	{
		// 10의 자리의 값을 얻어온다.
		// 127일 경우 2가 나오게 된다.
		int32	Value = (mStencilValue / 10) % 10;

		// Value = 2 | 2 = 10 | 10 = 10
		Value |= 2;

		// 100의 자리의 값을 얻어온다.
		int32	Value100 = (mStencilValue / 100) % 10;
		int32	Color = mStencilValue % 10;

		mStencilValue = Value100 * 100 + Value * 10 + Color;
	}

	else
	{
		// 10의 자리의 값을 얻어온다.
		// 127일 경우 2가 나오게 된다.
		int32	Value = (mStencilValue / 10) % 10;

		// Value = 2 | 2 = 10 | 10 = 10
		if (Value & 2)
			Value ^= 2;

		// 100의 자리의 값을 얻어온다.
		int32	Value100 = (mStencilValue / 100) % 10;
		int32	Color = mStencilValue % 10;

		mStencilValue = Value100 * 100 + Value * 10 + Color;
	}

	GetMesh()->SetCustomDepthStencilValue(mStencilValue);
}

void APlayerCharacter::SetColor(int32 Color)
{
	// 1의 자리를 0으로 만들어준다.
	// 127이 있다고 가정할 경우 7을 제거한 120을 만들어주고
	// Color를 더해준다.
	// Color % 10을 해준 이유는 실수로 10 이상인 수를 넣었을 경우
	// 1의 자리의 숫자만 꺼내오기 위해서이다.
	mStencilValue = mStencilValue - (mStencilValue % 10) +
		(Color % 10);

	GetMesh()->SetCustomDepthStencilValue(mStencilValue);
}

void APlayerCharacter::OnStep(bool Left)
{
	FVector	StartLocation;

	if (Left)
		StartLocation = GetMesh()->GetSocketLocation(TEXT("Foot_L"));

	else
		StartLocation = GetMesh()->GetSocketLocation(TEXT("Foot_R"));

	FVector	EndLocation = StartLocation + FVector::DownVector * 50.f;

	FHitResult	result;

	FCollisionQueryParams	param(NAME_None, false, this);
	param.bReturnPhysicalMaterial = true;
	bool IsCollision = GetWorld()->LineTraceSingleByChannel(result, StartLocation,
		EndLocation, ECC_Visibility, param);

	if (IsCollision)
	{
		UPOKPhysicalMaterialBase* Phys = Cast<UPOKPhysicalMaterialBase>(result.PhysMaterial);

		if (IsValid(Phys))
		{
			if (IsValid(Phys->GetParticle()))
			{
				FActorSpawnParameters	ActorParam;
				ActorParam.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				ANiagaraActor* Effect = GetWorld()->SpawnActor<ANiagaraActor>(
					result.ImpactPoint,
					FRotator::ZeroRotator, ActorParam);

				Effect->GetNiagaraComponent()->SetAsset(Phys->GetParticle());

				// 나이아가라 시스템이 종료되면 액터를 자동으로 제거한다.
				Effect->SetDestroyOnSystemFinish(true);
			}

			if (IsValid(Phys->GetSound()))
			{
				UGameplayStatics::PlaySoundAtLocation(this,
					Phys->GetSound(), result.ImpactPoint,
					10.f);

				// 배경음 처리
				/*UGameplayStatics::PlaySound2D(this, Phys->GetSound(),
					10.f);*/
			}
		}
	}
}

void APlayerCharacter::OnGhost()
{
	if (!mGhostEnable)
	{
		mGhostEnable = true;

		mGhostTimerCount = 10;

		//GetWorld()->GetTimerManager()
		/*
		4번인자 : 
		5번인자 : 
		6번인자 : 
		*/
		GetWorldTimerManager().SetTimer(mGhostTimer, this,
			&ThisClass::GhostTimer, 0.25f, true);
	}
}

void APlayerCharacter::GhostTimer()
{
	--mGhostTimerCount;

	FActorSpawnParameters	param;

	param.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AGhost* Ghost = GetWorld()->SpawnActor<AGhost>(
		GetMesh()->GetComponentLocation(),
		GetMesh()->GetComponentRotation(), param);

	Ghost->SetLifeSpan(3.f);

	Ghost->CopySkeletalMesh(GetMesh());

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
		TEXT("Timer"));

	if (mGhostTimerCount == 0)
	{
		mGhostEnable = false;
		mGhostTimerCount = 10;
		GetWorldTimerManager().ClearTimer(mGhostTimer);
	}
}


