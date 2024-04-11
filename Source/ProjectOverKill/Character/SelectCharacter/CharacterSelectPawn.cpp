#include "CharacterSelectPawn.h"

ACharacterSelectPawn::ACharacterSelectPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

#if WITH_EDITORONLY_DATA

	mArrorw = CreateDefaultSubobject<UArrowComponent>(TEXT("mArrorw"));
	mArrorw->SetupAttachment(mRoot);

#endif

	SetRootComponent(mRoot);

	mRoot->bVisualizeComponent = true;
}

void ACharacterSelectPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterSelectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterSelectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

