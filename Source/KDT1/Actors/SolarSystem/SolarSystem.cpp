// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/SolarSystem.h"
#include "SolarSystem/Star.h"
#include "SolarSystem/Planet.h"

// Sets default values
ASolarSystem::ASolarSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Axis = CreateDefaultSubobject<USceneComponent>(TEXT("Axis"));
	SetRootComponent(Axis);

	Sun = CreateDefaultSubobject<USolarSystemComponent>(TEXT("Sun"));
	Sun->SetupAttachment(GetRootComponent());
	Sun->ChildActor->SetChildActorClass(AStar::StaticClass());

	Earth = CreateDefaultSubobject<USolarSystemComponent>(TEXT("Earth"));
	Earth->SetupAttachment(GetRootComponent());
	Earth->ChildActor->SetChildActorClass(APlanet::StaticClass());
	Earth->ChildActor->SetRelativeLocation(FVector(1000.0, 0.0, 0.0));
}

// Called when the game starts or when spawned
void ASolarSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASolarSystem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

