#include "ItemActor.h"

// Sets default values
AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mRoot->bVisualizeComponent = true;
	SetRootComponent(mRoot);
	
	EmbersEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	EmbersEffect->SetupAttachment(mRoot);
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemActor::OnSphereOverlap(AActor* OtherActor)
{
	if (OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemActor - OnSphereOverlap. OtherActor: %s"), *OtherActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemActor - OnSphereOverlap. OtherActor is nullptr"));
	}
}

