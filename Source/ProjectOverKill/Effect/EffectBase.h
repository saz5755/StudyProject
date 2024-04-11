#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "EffectBase.generated.h"

UCLASS()
class PROJECTOVERKILL_API AEffectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEffectBase();

protected:
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* mParticle;

	UPROPERTY(EditAnywhere)
	UAudioComponent* mAudio;
	//USoundBase* mSound;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetParticleAsset(const FString& Path);
	void SetParticleAsset(UParticleSystem* Particle);
	void SetSoundAsset(const FString& Path);
	void SetSoundAsset(USoundBase* Sound);

	UFUNCTION()
	void OnParticleFinish(UParticleSystemComponent* Particle);
};
