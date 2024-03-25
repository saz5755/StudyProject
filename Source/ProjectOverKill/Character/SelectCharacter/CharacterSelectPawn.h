// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "CharacterSelectPawn.generated.h"

UCLASS()
class PROJECTOVERKILL_API ACharacterSelectPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACharacterSelectPawn();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

#if WITH_EDITORONLY_DATA
	UArrowComponent* mArror;
#endif

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
