// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "MyTriggerBaseInterface.generated.h"

UCLASS()
class KDT1_API AMyTriggerBaseInterface : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTriggerBaseInterface();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Active"))
	void ReceiveActive();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Inactive"))
	void ReceiveInactive();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "InTrigger"))
	void ReceiveInTrigger();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OutTrigger"))
	void ReceiveOutTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// return: interface를 가지고 있으면 해당 Actor의 pointer
	//		   interface를 가지고 있지 않다면 nullptr
	AActor* GetTriggerObject() const;
	void Active();
	void Inactive();
	void InTrigger();
	void OutTrigger();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnActiveRadiusBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActiveRadiusEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* DefaultSceneRoot = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* ActiveRadius = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Trigger = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChildActorComponent* TriggerObject = nullptr;

};
