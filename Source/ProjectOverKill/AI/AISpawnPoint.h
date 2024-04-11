#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "AISpawnPoint.generated.h"

UCLASS()
class PROJECTOVERKILL_API AAISpawnPoint : public AActor
{
	GENERATED_BODY()

protected:
	USceneComponent* mRoot;

#if WITH_EDITORONLY_DATA
	UArrowComponent* mArror;
#endif

	// 이 포인트에서 생성할 클래스 타입을 가지고 있게 한다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAIPawn>	mSpawnClass;

	// 위의 클래스를 이용해서 실제로 생성된 객체의 메모리 주소를
	// 저장해둔다.
	class AAIPawn* mSpawnAI;

	// 실제 생성된 객체가 제거되고 여기에 지정된 시간 이후에
	// 다시 생성하게 하기위한 변수이다.
	UPROPERTY(EditAnywhere)
	float	mSpawnTime;

	// 생성을 위해 시간을 계산하기 위한 변수.
	float	mAccTime;

	// 전투중이 아닐 경우 이동을 하는 AI가 동작할 포인트를 저장한다.
	UPROPERTY(EditAnywhere)
	TArray<class APointActor*>	mPatrolArray;
	
	// Function
public:	
	AAISpawnPoint();

	virtual void Tick(float DeltaTime) override;

	void ClearSpawnObject();

protected:
	virtual void BeginPlay() override;

private:
	void Spawn();

};
