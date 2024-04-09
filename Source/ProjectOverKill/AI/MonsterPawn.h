// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIPawn.h"
#include "../Interfaces/HitInterface.h"
#include "MonsterPawn.generated.h"

struct FMonsterInfo	:
	public FAIInfo
{
	int32		mAttackPoint;
	int32		mArmorPoint;
	int32		mHP;
	int32		mHPMax;
	int32		mMP;
	int32		mMPMax;
	float		mAttackDistance;
};

USTRUCT(BlueprintType)
struct FMonsterData :
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32		mAttackPoint;

	UPROPERTY(EditAnywhere)
	int32		mArmorPoint;

	UPROPERTY(EditAnywhere)
	int32		mHPMax;

	UPROPERTY(EditAnywhere)
	int32		mMPMax;

	UPROPERTY(EditAnywhere)
	float		mMoveSpeed;

	UPROPERTY(EditAnywhere)
	float		mAttackDistance;

	UPROPERTY(EditAnywhere)
	float		mTraceDistance;
};


UCLASS()
class PROJECTOVERKILL_API AMonsterPawn : public AAIPawn, public IHitInterface
{
	GENERATED_BODY()

protected:
	static UDataTable* mMonsterDataTable;

public:
	static const FMonsterData* FindMonsterData(const FString& Name);

public:
	AMonsterPawn();

protected:
	class UMonsterAnimInstance* mAnimInst;
	FString		mTableRowName;
	class UMonsterState* mMonsterState;
	TArray<UMaterialInstanceDynamic*> mMaterialArray;

	bool	mDissolveEnable;
	float	mDissolve;
	float	mDissolveTime;
	float	mDissolveDuration;

	bool	mHitEnable = false;
	float	mHitTime = 0.f;
	float	mHitDuration = 0.3f;

public:
	virtual void ChangeAIAnimType(uint8 AnimType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser);

	virtual void NormalAttack();

	virtual void GetHit(const FVector& ImpactPoint, AActor* Hitter);

public:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

public:
	void OnDissolve();
};
