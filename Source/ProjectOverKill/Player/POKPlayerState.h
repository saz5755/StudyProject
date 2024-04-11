#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "POKPlayerState.generated.h"

//UENUM(BlueprintType)
//enum class ECharacterState : uint8
//{
//	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
//	// ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Handed Weapon"),
//	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Handed Weapon")
//};

UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	None,
	Knight,
	Archer,
	Magicion,
	End
};

// FTableRowBase 구조체를 상속받아서 만들어야 데이터테이블에서 사용할 수 있는
// 구조체가 된다.
USTRUCT(BlueprintType)
struct FPlayerData :
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	EPlayerJob	mJob;

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
};

UCLASS()
class PROJECTOVERKILL_API APOKPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	FString		mName;
	EPlayerJob	mJob;
	int32		mAttackPoint;
	int32		mArmorPoint;
	int32		mHP;
	int32		mHPMax;
	int32		mMP;
	int32		mMPMax;
	int32		mLevel;
	int32		mExp;
	float		mMoveSpeed;
	float		mAttackDistance;

private:
	UDataTable* mPlayerDataTable;
	
public:
	APOKPlayerState();

protected:
	virtual void BeginPlay() override;

};
