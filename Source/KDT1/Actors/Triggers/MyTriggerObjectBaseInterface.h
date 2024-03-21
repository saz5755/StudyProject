// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerInterface.h"
#include "MyTriggerObjectBaseInterface.generated.h"

UCLASS()
class KDT1_API AMyTriggerObjectBaseInterface : public AActor, public ITriggerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTriggerObjectBaseInterface();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
