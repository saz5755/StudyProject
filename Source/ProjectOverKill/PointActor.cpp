#include "PointActor.h"
#include "Components/BoxComponent.h"

APointActor::APointActor()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	SetRootComponent(mRoot);

	mTrigger->SetupAttachment(mRoot);

	mTrigger->SetBoxExtent(FVector(30.0, 30.0, 100.0));
	mTrigger->SetRelativeLocation(FVector(0.0, 0.0, 100.0));

	mTrigger->SetCollisionProfileName(TEXT("EnemyTrigger"));

	mRoot->bVisualizeComponent = true;
}

void APointActor::BeginPlay()
{
	Super::BeginPlay();
}

void APointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

