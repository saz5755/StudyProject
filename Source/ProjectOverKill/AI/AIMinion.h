// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterPawn.h"
#include "AIMinion.generated.h"



UCLASS()
class PROJECTOVERKILL_API AAIMinion : public AMonsterPawn
{
	GENERATED_BODY()
	
public:
	AAIMinion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NormalAttack();
};
