// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBase.h"

// Sets default values
AEffectBase::AEffectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	SetRootComponent(mParticle);

	mAudio->SetupAttachment(mParticle);

	mParticle->bVisualizeComponent = true;
}

// Called when the game starts or when spawned
void AEffectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffectBase::SetParticleAsset(const FString& Path)
{
	UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, *Path);

	SetParticleAsset(Particle);
}

void AEffectBase::SetParticleAsset(UParticleSystem* Particle)
{
	if (IsValid(Particle))
	{
		// 파티클 컴포넌트에 파티클을 지정한다.
		mParticle->SetTemplate(Particle);
		mParticle->OnSystemFinished.AddDynamic(this, &AEffectBase::OnParticleFinish);
	}
}

void AEffectBase::SetSoundAsset(const FString& Path)
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);

	SetSoundAsset(Sound);
}

void AEffectBase::SetSoundAsset(USoundBase* Sound)
{
	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);
		mAudio->Play();
	}
}

void AEffectBase::OnParticleFinish(UParticleSystemComponent* Particle)
{
	// 파티클이 끝났을 경우 액터를 제거한다.
	Destroy();
}

