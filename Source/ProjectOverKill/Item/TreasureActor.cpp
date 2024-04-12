#include "Item/TreasureActor.h"
#include "Character/PlayerCharacter.h"

void ATreasureActor::BeginPlay()
{
	Super::BeginPlay();
}

ATreasureActor::ATreasureActor()
{
	TreasureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreasureMesh"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	TreasureMesh->SetupAttachment(mRoot);
	SphereComponent->SetupAttachment(mRoot);

}

void ATreasureActor::OnSphereOverlap(AActor* OtherActor)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		if (AcquireSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				AcquireSound,
				GetActorLocation());
		}
		Destroy();
	}
}

