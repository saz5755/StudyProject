#pragma once

#include "GameInfo.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "GameFramework/Actor.h"
#include "LevelSequenceTrigger.generated.h"

UCLASS()
class PROJECTOVERKILL_API ALevelSequenceTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelSequenceTrigger();

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* mBox;

	UPROPERTY(EditAnywhere)
	ULevelSequence* mSequence;

	UPROPERTY(EditAnywhere)
	FMovieSceneSequencePlaybackSettings	mSetting;

	ULevelSequencePlayer* mSequencePlayer;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
};
