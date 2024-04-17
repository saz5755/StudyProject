#include "AIPawn.h"
#include "DefaultAIController.h"
#include "AISpawnPoint.h"
#include "../PointActor.h"
#include "UI/HUD//HealthBarComponent.h"

AAIPawn::AAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mAttackEnd = false;

	// 컴포넌트 생성
	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	mMovement->SetUpdatedComponent(mCapsule);

	// 루트컴포넌트로 캡슐을 지정한다.
	SetRootComponent(mCapsule);

	// Mesh를 Capsule의 Child로 지정한다.
	mMesh->SetupAttachment(mCapsule);

	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(mCapsule);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//AIControllerClass = ADefaultAIController::StaticClass();

	static ConstructorHelpers::FClassFinder<AAIController>	AIClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Main/AI/BP_DefaultAIController.BP_DefaultAIController_C'"));

	if (AIClass.Succeeded())
		AIControllerClass = AIClass.Class;

	mSpawnPoint = nullptr;

	mPatrolIndex = -1;
	mPatrolDir = 1;

	mAIInfo = nullptr;
}


void AAIPawn::SetPatrolArray(const TArray<class APointActor*>& PatrolArray)
{
	// 포인트가 비어 있을 경우 예외처리
	if (PatrolArray.IsEmpty())
		return;

	mPatrolArray = PatrolArray;

	FVector	StartPoint = GetActorLocation() -
		FVector(0.0, 0.0, (double)GetHalfHeight());

	mPatrolPointArray.Add(StartPoint);

	for (auto Point : mPatrolArray)
	{
		mPatrolPointArray.Add(Point->GetActorLocation());
	}
}

void AAIPawn::ChangeAIAnimType(uint8 AnimType)
{
}

void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	// 0번인덱스에는 이 AI의 시작 위치를 넣어주고 있기 때문에
	// 1번 인덱스부터 방문할 수 있게 한다.
	mPatrolIndex = 1;

}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 이 AIPawn을 생성해준 SpawnPoint가 있을 경우
	// 해당 SpawnPoint의 생성된 오브젝트 정보를 초기화한다.
	if (mSpawnPoint)
	{
		mSpawnPoint->ClearSpawnObject();
	}

	// 만약 AIInfo가 동적할당되어 메모리 주소를 가지고 있다면
	// 메모리를 해제한다.
	if (mAIInfo)
	{
		delete mAIInfo;
	}
}

void AAIPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AAIPawn::TakeDamage(float DamageAmount, 
	FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//Destroy();
	return DamageAmount;
}

void AAIPawn::OnCustomDepthStencil(bool Enable)
{
	// CustomDepthStencil 버퍼에 값을 쓸지 결정한다.
	mMesh->SetRenderCustomDepth(Enable);
}

void AAIPawn::SetCustomStencil(int32 Stencil)
{
	mStencilValue = Stencil;

	mMesh->SetCustomDepthStencilValue(mStencilValue);
}

void AAIPawn::OnOutLine(bool OnOff)
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

	mMesh->SetCustomDepthStencilValue(mStencilValue);
}

void AAIPawn::OnOcclusion(bool OnOff)
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

	mMesh->SetCustomDepthStencilValue(mStencilValue);
}

void AAIPawn::SetColor(int32 Color)
{
	// 1의 자리를 0으로 만들어준다.
	// 127이 있다고 가정할 경우 7을 제거한 120을 만들어주고
	// Color를 더해준다.
	// Color % 10을 해준 이유는 실수로 10 이상인 수를 넣었을 경우
	// 1의 자리의 숫자만 꺼내오기 위해서이다.
	mStencilValue = mStencilValue - (mStencilValue % 10) + 
		(Color % 10);

	mMesh->SetCustomDepthStencilValue(mStencilValue);
}

void AAIPawn::HideHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
}

void AAIPawn::ShowHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}
}

