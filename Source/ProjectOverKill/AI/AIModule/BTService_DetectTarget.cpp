#include "BTService_DetectTarget.h"
#include "../DefaultAIController.h"
#include "../AIPawn.h"
#include "../AIState.h"

UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("DetectTarget");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 이 Service를 사용하고 있는 AIController를 얻어온다.
	AAIController* Controller = OwnerComp.GetAIOwner();

	// 위에서 얻어온 AIController가 빙의되어 있는 Pawn을 얻어온다.
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
		return;

	FVector	AILocation = Pawn->GetActorLocation();

	AILocation.Z -= Pawn->GetHalfHeight();
	
	// 주변에 Target이 있는지 판단한다.
	FCollisionQueryParams	param(NAME_None, false, Pawn);

	UAIState* AIState = Pawn->GetState<UAIState>();

	if (!IsValid(AIState))
		return;

	FHitResult	result;
	bool IsCollision = GetWorld()->SweepSingleByChannel(result, AILocation, AILocation, 
		FQuat::Identity, ECC_GameTraceChannel4, 
		FCollisionShape::MakeSphere(AIState->mInteractionDistance),
		param);

#if ENABLE_DRAW_DEBUG

	// 구를 그린다.
	FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), AILocation, 
		AIState->mInteractionDistance, 20, DrawColor, false,
		0.35f);

#endif

	// Target을 찾았을 경우
	if (IsCollision)
	{
		// AIController에 지정된 Blackboard에 Target을 저장한다.
		// result.GetActor() : 충돌된 액터를 얻어온다.
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"),
			result.GetActor());
	}

	// 충돌이 안될경우 nullptr을 지정한다.
	else
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"),
			nullptr);
	}
}
