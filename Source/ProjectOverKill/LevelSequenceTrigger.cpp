// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequenceTrigger.h"

// Sets default values
ALevelSequenceTrigger::ALevelSequenceTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	mBox->bVisualizeComponent = true;

	SetRootComponent(mBox);

	mSequencePlayer = nullptr;
}

// Called when the game starts or when spawned
void ALevelSequenceTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	mBox->OnComponentBeginOverlap.AddDynamic(this,
		&ALevelSequenceTrigger::OverlapBegin);
}

// Called every frame
void ALevelSequenceTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSequenceTrigger::OverlapBegin(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(mSequence))
	{
		if (!IsValid(mSequencePlayer))
		{
			ALevelSequenceActor* SequenceActor = nullptr;

			mSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(), mSequence, mSetting, SequenceActor);
		}

		if (!mSequencePlayer->IsPlaying())
			mSequencePlayer->Play();
	}
}

