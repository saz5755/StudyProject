// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectPawn.h"

// Sets default values
ACharacterSelectPawn::ACharacterSelectPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

#if WITH_EDITORONLY_DATA

	mArrorw = CreateDefaultSubobject<UArrowComponent>(TEXT("mArrorw"));

	mArrorw->SetupAttachment(mRoot);

#endif

	SetRootComponent(mRoot);

	mRoot->bVisualizeComponent = true;
}

// Called when the game starts or when spawned
void ACharacterSelectPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterSelectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterSelectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

