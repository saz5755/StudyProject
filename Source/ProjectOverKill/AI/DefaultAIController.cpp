// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIController.h"

ADefaultAIController::ADefaultAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITree(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/Main/AI/BT_Default.BT_Default'"));

	if (AITree.Succeeded())
		mBehaviourTree = AITree.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>	Data(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/Main/AI/BB_Default.BB_Default'"));

	if (Data.Succeeded())
		mBlackboard = Data.Object;
}

void ADefaultAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 블랙보드가 있을 경우
	if (mBlackboard)
	{
		// AI 컨트롤러가 가지고 있는 Blackboard 컴포넌트에 읽어온 블랙보드를 지정한다.
		UBlackboardComponent* BlackboardRef = Blackboard;

		if (UseBlackboard(mBlackboard, BlackboardRef))
		{
			RunBehaviorTree(mBehaviourTree);
		}
	}
}

void ADefaultAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
