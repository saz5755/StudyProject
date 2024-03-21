// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Triggers/MyTriggerObjectBase.h"

// Sets default values
AMyTriggerObjectBase::AMyTriggerObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTriggerObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyTriggerObjectBase::Active()
{
	ReceiveActive();
}

void AMyTriggerObjectBase::Inactive()
{
	ReceiveInactive();
}

void AMyTriggerObjectBase::InTrigger()
{
	ReceiveInTrigger();
}

void AMyTriggerObjectBase::OutTrigger()
{
	ReceiveOutTrigger();
}

// Called every frame
void AMyTriggerObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

