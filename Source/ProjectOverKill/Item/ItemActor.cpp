#include "ItemActor.h"

// Sets default values
AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mRoot->bVisualizeComponent = true;

	SetRootComponent(mRoot);
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

