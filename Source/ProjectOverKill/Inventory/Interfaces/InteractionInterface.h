// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UENUM()
enum class EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	NonPlayerCharacter UMETA(DisplayName = "NonPlayerCharacter"),
	Device UMETA(DisplayName = "Device"),
	Toggle UMETA(DisplayName = "Toggle"),
	Container UMETA(DisplayName = "Container")
};

USTRUCT()
struct FInteractableData
{
	GENERATED_USTRUCT_BODY()

	FInteractableData() : InteractableType(EInteractableType::Pickup),
		Name(FText::GetEmpty()),
		Action(FText::GetEmpty()),
		Quantity(0),
		InteractionDuration(0.0f)
	{

	};

	UPROPERTY(EditInstanceOnly)
	EInteractableType InteractableType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Action;

	// 현재는 0~255까지만 있어도 충분하기에 int8 사용하였고 
	// 추후 기호에 따라 int32와 같은 다른 타입으로 변경하기
	// Used Only for Pickups
	UPROPERTY(EditInstanceOnly)
	int8 Quantity;

	// Used for things like valves, doors, etc. that require an interaction timer
	UPROPERTY(EditInstanceOnly)
	float InteractionDuration;

};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTOVERKILL_API IInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact(AMainPlayerController* PlayerController);

	FInteractableData InteractableData;
};
