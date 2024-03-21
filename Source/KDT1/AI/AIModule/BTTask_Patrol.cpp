// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include "../DefaultAIController.h"
#include "../AIPawn.h"
#include "../MonsterAnimInstance.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol");

	// Tick 함수 호출이 가능하게 한다.
	bNotifyTick = true;

	// OnTaskFinished 이벤트를 사용할 수 있게 한다.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	// 위에서 얻어온 AIController가 빙의되어 있는 Pawn을 얻어온다.
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
		return EBTNodeResult::Failed;

	// PatrolPointArray가 비어있을 경우 방문할 위치가 없기 때문에
	// Task를 종료시킨다.
	if (Pawn->IsPatrolPointEmpty())
		return EBTNodeResult::Failed;

	// 블랙보드에 있는 Target을 Actor로 얻어온다.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	// Patrol은 비 전투시에 동작하기 때문에 Target이 있으면
	// 전투상태가 되므로 Task를 종료해야 한다.
	if (IsValid(Target))
	{
		// 이동을 멈추게 한다.
		Controller->StopMovement();

		// 애니메이션을 Idle 로 변경한다.
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	// 방문할 위치를 꺼내온다.
	FVector	Point = Pawn->GetPatrolPoint();

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller,
		Point);

	// 애니메이션을 Walk 로 변경한다.
	Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Walk);

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
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

	// Patrol은 비 전투시에 동작하기 때문에 Target이 있으면
	// 전투상태가 되므로 Task를 종료해야 한다.
	if (IsValid(Target))
	{
		// 이동을 멈추게 한다.
		Controller->StopMovement();

		// 애니메이션을 Idle 로 변경한다.
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		// Task를 종료한다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

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

	// 방문할 위치를 꺼내온다.
	FVector	TargetLocation = Pawn->GetPatrolPoint();

	AILocation.Z -= Pawn->GetHalfHeight();

	// FVector::Distance : 두 위치 사이의 거리를 구한다.
	float	Distance = FVector::Distance(AILocation, TargetLocation);

	if (Distance <= 50.f)
	{
		// Task를 종료한다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		Controller->StopMovement();

		// 애니메이션을 Idle 로 변경한다.
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		// 패트롤 인덱스를 구해준다.
		Pawn->NextPatrolPointIndex();
	}
}
