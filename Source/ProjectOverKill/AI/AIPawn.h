#pragma once

#include "../GameInfo.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

struct FAIInfo
{
	float		mMoveSpeed;
	float		mInteractionDistance;
};

UCLASS()
class PROJECTOVERKILL_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	AAIPawn();

protected:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mMesh;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* mMovement;

	UPROPERTY(EditAnywhere)
	class UAIState* mState;

	FAIInfo* mAIInfo;
	
	bool	mAttackEnd;

	// SpawnPoint를 통해 생성이 되었을 경우 어떤 SpawnPoint에서
	// 생성이 되었는지를 가지고 있게 한다.
	class AAISpawnPoint* mSpawnPoint;

	// 전투중이 아닐 경우 이동을 하는 AI가 동작할 포인트를 저장한다.
	UPROPERTY(EditAnywhere)
	TArray<class APointActor*>	mPatrolArray;
	
	// 위에서 받아온 액터의 위치를 이용하여 최종 방문해야 하는 경로를
	// 위치로 만들어준다.
	TArray<FVector>		mPatrolPointArray;

	int32		mPatrolIndex;
	int32		mPatrolDir;

	int32		mAttackPoint;
	int32		mArmorPoint;

	int32		mStencilValue = 1;

public:
	template <typename T>
	T* GetAIInfo()
	{
		return (T*)mAIInfo;
	}

	template <typename T>
	T* GetState()
	{
		return Cast<T>(mState);
	}

public:
	void NextPatrolPointIndex()
	{
		mPatrolIndex += mPatrolDir;

		// 배열의 인덱스 범위를 벗어났는지 판단한다.
		if (mPatrolIndex >= mPatrolPointArray.Num())
		{
			// 방향을 역방향으로 바꿔준다.
			mPatrolDir = -1;

			// 마지막 위치의 이전 위치 인덱스로 지정한다.
			mPatrolIndex -= 2;
		}

		else if (mPatrolIndex < 0)
		{
			// 방향을 정방향으로 바꿔준다.
			mPatrolDir = 1;

			// 처음 위치의 다음 위치 인덱스로 지정한다.
			mPatrolIndex = 1;
		}
	}

	FVector GetPatrolPoint()
	{
		return mPatrolPointArray[mPatrolIndex];
	}

	bool IsPatrolPointEmpty()
	{
		return mPatrolPointArray.IsEmpty();
	}

	void SetPatrolArray(const TArray<class APointActor*>& PatrolArray);

	void SetSpawnPoint(class AAISpawnPoint* Point)
	{
		mSpawnPoint = Point;
	}

	void SetAttackEnd(bool End)
	{
		mAttackEnd = End;
	}

	bool IsAttackEnd()
	{
		return mAttackEnd;
	}

public:
	float GetHalfHeight()	const
	{
		return mCapsule->GetScaledCapsuleHalfHeight();
	}

	float GetCapsuleRadius()
	{
		return mCapsule->GetScaledCapsuleRadius();
	}

public:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void Tick(float DeltaTime) override;

	virtual void ChangeAIAnimType(uint8 AnimType);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser);

public:
		void OnCustomDepthStencil(bool Enable);
		void SetCustomStencil(int32 Stencil);
		void OnOutLine(bool OnOff);
		void OnOcclusion(bool OnOff);
		void SetColor(int32 Color);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

};
