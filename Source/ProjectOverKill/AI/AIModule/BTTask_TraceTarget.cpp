#include "BTTask_TraceTarget.h"
#include "../DefaultAIController.h"
#include "../AIPawn.h"
#include "../MonsterAnimInstance.h"
#include "../MonsterState.h"

UBTTask_TraceTarget::UBTTask_TraceTarget()
{
	NodeName = TEXT("TraceTarget");

	// Tick 함수 호출이 가능하게 한다.
	bNotifyTick = true;

	// OnTaskFinished 이벤트를 사용할 수 있게 한다.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_TraceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	// 위에서 얻어온 AIController가 빙의되어 있는 Pawn을 얻어온다.
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
		return EBTNodeResult::Failed;

	// 블랙보드에 있는 Target을 Actor로 얻어온다.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		// 이동을 멈추게 한다.
		Controller->StopMovement();

		// 애니메이션을 Idle 로 변경한다.
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	// Target이 정상이라면 Target을 향해 이동을 시켜준다.
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

	// 애니메이션을 Run 으로 변경한다.
	Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Run);

	return EBTNodeResult::InProgress;
}

void UBTTask_TraceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	// 위에서 얻어온 AIController가 빙의되어 있는 Pawn을 얻어온다.
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
	{
		// Task를 종료한다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();

		return;
	}

	// 블랙보드에 있는 Target을 Actor로 얻어온다.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		// Task를 종료한다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();

		// 애니메이션을 Idle 로 변경한다.
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return;
	}

	// 속도 벡터를 가져와서 방향을 구한다.
	// 방향은 x, y의 값을 이용해서 방향을 구한다.
	FVector	Dir = Pawn->GetMovementComponent()->Velocity;
	Dir.Z = 0.f;

	Dir.Normalize();

	Pawn->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));

	// 타겟과의 거리를 체크한다.
	FVector	AILocation = Pawn->GetActorLocation();
	FVector	TargetLocation = Target->GetActorLocation();

	AILocation.Z -= Pawn->GetHalfHeight();

	UCapsuleComponent* TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

	if (IsValid(TargetCapsule))
	{
		TargetLocation.Z -= TargetCapsule->GetScaledCapsuleHalfHeight();
	}

	// FVector::Distance : 두 위치 사이의 거리를 구한다.
	float	Distance = FVector::Distance(AILocation, TargetLocation);

	/*Distance -= Pawn->GetCapsuleRadius();

	if (IsValid(TargetCapsule))
	{
		Distance -= TargetCapsule->GetScaledCapsuleRadius();
	}*/

	UMonsterState* State = Pawn->GetState<UMonsterState>();

	if (Distance <= State->mAttackDistance)
	{
		// Task를 종료한다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		Controller->StopMovement();

		// 애니메이션을 Idle 로 변경한다.
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);
	}
}

void UBTTask_TraceTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
