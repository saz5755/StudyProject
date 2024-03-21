// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Triggers/MyTriggerObjectBaseInterface.h"

// Sets default values
AMyTriggerObjectBaseInterface::AMyTriggerObjectBaseInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTriggerObjectBaseInterface::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTriggerObjectBaseInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

