#pragma once
#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "BasicInputDataConfig.generated.h"

//class UBasicInputDataConfig : public UDataAsset
UCLASS()
class UBasicInputDataConfig : public UObject
{
	GENERATED_BODY()
public:
	UBasicInputDataConfig();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultContext = nullptr;

public:
	UInputAction* Move = nullptr;
	UInputAction* Look = nullptr;
};

UCLASS()
class UTankInputDataConfig : public UObject
{
	GENERATED_BODY()
public:
	UTankInputDataConfig();
public:
	UInputMappingContext* DefaultContext = nullptr;

public:
	UInputAction* Attack = nullptr;
	UInputAction* Zoom = nullptr;
};

UCLASS()
class USelectInputDataConfig : public UObject
{
	GENERATED_BODY()
public:
	USelectInputDataConfig();
public:
	UInputMappingContext* DefaultContext = nullptr;

public:
	UInputAction* Select = nullptr;
};

UCLASS()
class UMainInputDataConfig : public UObject
{
	GENERATED_BODY()
public:
	UMainInputDataConfig();
public:
	UInputMappingContext* DefaultContext = nullptr;

public:
	UInputAction* Move = nullptr;
	UInputAction* Attack = nullptr;
	UInputAction* Jump = nullptr;
	UInputAction* Skill1 = nullptr;
	UInputAction* Detect = nullptr;
	UInputAction* Ghost = nullptr;
};