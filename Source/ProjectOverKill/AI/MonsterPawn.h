#pragma once

#include "AIPawn.h"
#include "../Interfaces/HitInterface.h"
#include "MonsterPawn.generated.h"

struct FMonsterInfo	: public FAIInfo
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
struct FMonsterData : public FTableRowBase
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
	AMonsterPawn();

	static const FMonsterData* FindMonsterData(const FString& Name);

	void OnDissolve();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	virtual void Tick(float DeltaTime) override;

	virtual void ChangeAIAnimType(uint8 AnimType);

	virtual void OnConstruction(const FTransform& Transform);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser);

	virtual void NormalAttack();
	virtual void GetHit(const FVector& ImpactPoint, AActor* Hitter);

protected:
	virtual void BeginPlay() override;
	
};
