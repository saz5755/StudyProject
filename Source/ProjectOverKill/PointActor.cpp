// Fill out your copyright notice in the Description page of Project Settings.


#include "PointActor.h"
#include "Components/BoxComponent.h"

// Sets default values
APointActor::APointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void APointActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

