// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/Star.h"

AStar::AStar()
{
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(GetRootComponent());
	PointLight->bUseInverseSquaredFalloff = false;
	PointLight->LightFalloffExponent = 0.0001f;
	PointLight->Intensity = 10.f;
	PointLight->AttenuationRadius = 10000000.f;

	ConstructorHelpers::FObjectFinder<UMaterial> Material{ TEXT("/Script/Engine.Material'/Game/Blueprint/SolarSystem/MT_Sun.MT_Sun'") };
	if (!Material.Succeeded())
	{
		check(false);
	}
	AstronomicalStaticMesh->SetMaterial(0, Material.Object);
}

void AStar::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AStar::BeginPlay()
{
	Super::BeginPlay();
}

void AStar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (AstronomicalDynamicMaterial)
	{
		AccTime += DeltaSeconds * PlusMinus;

		if (AccTime > 1.f)
		{
			PlusMinus *= -1;
			AccTime = 1.f;
		}
		else if (AccTime < 0.f)
		{
			PlusMinus *= -1;
			AccTime = 0.f;
		}

		const float Result = FMath::Lerp(10.f, 100.f, AccTime);
		AstronomicalDynamicMaterial->SetScalarParameterValue(TEXT("SunPower"), Result);
	}
}

void AStar::Init()
{
	Super::Init();
}
