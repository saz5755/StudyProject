// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/AstronomicalObject.h"

// Sets default values
AAstronomicalObject::AAstronomicalObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Axis = CreateDefaultSubobject<USceneComponent>(TEXT("Axis"));
	SetRootComponent(Axis);
	AstronomicalStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	AstronomicalStaticMesh->SetupAttachment(Axis);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh{ TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorSphere.EditorSphere'") };
	if (!Mesh.Succeeded())
	{
		check(false);
	}
	AstronomicalStaticMesh->SetStaticMesh(Mesh.Object);
}

// Called when the game starts or when spawned
void AAstronomicalObject::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AAstronomicalObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Init();
}

// Called every frame
void AAstronomicalObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const double DeltaSpeed = (double)DeltaSeconds * RotationSpeed;
	const FRotator Rotator{ 0.0, DeltaSpeed, 0.0 };
	AstronomicalStaticMesh->AddRelativeRotation(Rotator);
}

void AAstronomicalObject::Init()
{
	if (AstronomicalMaterial)
	{
		AstronomicalDynamicMaterial = AstronomicalStaticMesh->CreateDynamicMaterialInstance(0, AstronomicalMaterial);
		//AstronomicalStaticMesh->SetMaterial(0, AstronomicalMaterial);
	}
}

