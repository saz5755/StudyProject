// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "SelectPlayer.generated.h"

UCLASS()
class KDT1_API ASelectPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelectPlayer();

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh;

	class USelectAnimInstance* mAnimInst;

	UPROPERTY(EditAnywhere)
	EPlayerType		mPlayerType;

public:
	EPlayerType GetPlayerType()
	{
		return mPlayerType;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSelect(bool Select);
	void OnCustomDepth(bool Enable);
};
