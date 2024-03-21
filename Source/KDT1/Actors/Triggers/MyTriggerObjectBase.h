// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTriggerObjectBase.generated.h"

UCLASS()
class KDT1_API AMyTriggerObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTriggerObjectBase();

public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Active"))
	void ReceiveActive();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Inactive"))
	void ReceiveInactive();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "InTrigger"))
	void ReceiveInTrigger();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OutTrigger"))
	void ReceiveOutTrigger();

	virtual void Active();
	virtual void Inactive();
	virtual void InTrigger();
	virtual void OutTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
