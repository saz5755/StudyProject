#include "LevelSequenceTrigger.h"

ALevelSequenceTrigger::ALevelSequenceTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	mBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	mBox->bVisualizeComponent = true;

	SetRootComponent(mBox);

	mSequencePlayer = nullptr;
}

void ALevelSequenceTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	mBox->OnComponentBeginOverlap.AddDynamic(this,
		&ALevelSequenceTrigger::OverlapBegin);
}

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

