// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "../Player/PlayerAnimInstance.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class PROJECTOVERKILL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	FORCEINLINE EPlayerAnimType GetCharacterState() const { return mAnimType; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* mCameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* mFaceCapture;

	// Character 클래스가 가지고 있는 SkeletalMeshComponent에 지정된 AnimInstance를
	// 얻어놓는다.
	class UPlayerAnimInstance* mAnimInst;

	class APOKPlayerState* mState;

	class AItemWeapon* mWeapon;
	class AItemHelmet* mHelmet;
	class AItemArmor* mArmor;
	class AItemBoots* mBoots;

	int32	mStencilValue = 1;

	bool	mGhostEnable = false;
	FTimerHandle	mGhostTimer;
	int32			mGhostTimerCount = 10;


private:
	EPlayerAnimType mAnimType = EPlayerAnimType::Default;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	APlayerCharacter();

	virtual void OnConstruction(const FTransform& Transform);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser);

public:
	void PlayAttackMontage();
	void PlaySkillMontage(int32 Index);
	void PlayJump();

public:
	virtual void NormalAttack();

public:
	void SetWeaponMesh(USkeletalMesh* WeaponMesh);
	void SetHelmetMesh(USkeletalMesh* HelmetMesh);
	void SetArmorMesh(USkeletalMesh* ArmorMesh);
	void SetBootsMesh(USkeletalMesh* BootsMesh);

public:
	void OnCustomDepthStencil(bool Enable);
	void SetCustomStencil(int32 Stencil);
	void OnOutLine(bool OnOff);
	void OnOcclusion(bool OnOff);
	void SetColor(int32 Color);

	void OnStep(bool Left);

	void OnGhost();

private:
	UFUNCTION()
	void GhostTimer();

};
