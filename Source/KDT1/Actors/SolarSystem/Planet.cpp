// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/Planet.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Star.h"

APlanet::APlanet()
{
	CloudStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cloud"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh{ TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorSphere.EditorSphere'") };
	if (!Mesh.Succeeded())
	{
		check(false);
	}
	CloudStaticMesh->SetStaticMesh(Mesh.Object);
	CloudStaticMesh->SetRelativeScale3D(FVector(1.01, 1.01, 1.01));
	CloudStaticMesh->SetupAttachment(AstronomicalStaticMesh);

	NaturalSatellites.SetNum(1, false);
	const int32 Num = NaturalSatellites.Num();
	for (int32 i = 0; i < Num; ++i)
	{
		NaturalSatellites[i] = CreateDefaultSubobject<USolarSystemComponent>(FName(TEXT("NatrualSatellite") + FString::Printf(TEXT("%2d"), i)));
		NaturalSatellites[i]->SetupAttachment(GetRootComponent());
		NaturalSatellites[i]->RotationSpeed = 360;
	}
}

void APlanet::BeginPlay()
{
	Super::BeginPlay();

	if (bSkyAtmosphere)
	{
		ASkyAtmosphere* SkyAtmosphere = Cast<ASkyAtmosphere>(UGameplayStatics::GetActorOfClass(GetWorld(), ASkyAtmosphere::StaticClass()));
		if (IsValid(SkyAtmosphere))
		{
			SkyAtmosphere->AttachToComponent(AstronomicalStaticMesh, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void APlanet::Init()
{
	Super::Init();
	CloudStaticMesh->SetMaterial(0, CloudMaterial);
	CalculateNightSide();
}

void APlanet::CalculateNightSide()
{
	if (!AstronomicalDynamicMaterial)
	{
		return;
	}
	FVector StarLocation = FVector::ZeroVector;
	AActor* Star = UGameplayStatics::GetActorOfClass(GetWorld(), AStar::StaticClass());
	if (IsValid(Star))
	{
		StarLocation = Star->GetActorLocation();
	}

	FVector PlanetLocation = GetActorLocation();
	FVector NormalizedDirectionalVector = StarLocation - PlanetLocation;
	NormalizedDirectionalVector.Normalize();
	AstronomicalDynamicMaterial->SetVectorParameterValue(TEXT("PointLightDirection"), NormalizedDirectionalVector);
}

void APlanet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const double DeltaSpeed = (double)DeltaSeconds * CloudRotationSpeed;
	const FRotator Rotator{ 0.0, DeltaSpeed, 0.0 };
	CloudStaticMesh->AddRelativeRotation(Rotator);

	CalculateNightSide();
}
