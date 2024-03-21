// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SolarSystem/SolarSystemComponent.h"

// Sets default values for this component's properties
USolarSystemComponent::USolarSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ChildActor = CreateDefaultSubobject<UChildActorComponent>(FName(GetName() + TEXT("ChildActor")));
	ChildActor->SetupAttachment(this);
}


// Called when the game starts
void USolarSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USolarSystemComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
	ChildActor->SetupAttachment(this);
}

void USolarSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const double DeltaSpeed = (double)DeltaTime * RotationSpeed;
	const FRotator Rotator{ 0.0, DeltaSpeed, 0.0 };
	AddRelativeRotation(Rotator);
}

