// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "../Inventory/Interfaces/InteractionInterface.h"
#include "MainPlayerController.generated.h"

class APOKHUD;
class UInventoryComponent;
class UItemBase;
struct FInputActionValue;

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f)
	{

	};

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;
};


UCLASS()
class PROJECTOVERKILL_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	APOKHUD* HUD;

private:
	TSubclassOf<UUserWidget>	mMainWidgetClass;
	class UMainViewportWidget* mMainWidget;
	float	mMoveDir;

	bool	mDetectEnable = false;
	float	mDetectTime = 0.f;
	float	mDetectDuration = 4.f;
	float	mDetectDelayTime = 0.f;
	float	mDetectDelay = 0.4f;
	TArray<AActor*>	mDetectActorArray;

public:
	AMainPlayerController();
	virtual void Tick(float DeltaTime) override;
	
	class UMainViewportWidget* GetMainWidget(){return mMainWidget;}
	float GetMoveDir(){return mMoveDir;}

	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };
	FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory; };
	void UpdateInteractionWidget() const;
	void DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void OnLookMouse(const FInputActionValue& InputActionValue);
	void OnMove(const FInputActionValue& InputActionValue);
	void OnAttack(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
	void OnDetect(const FInputActionValue& InputActionValue);
	void OnGhost(const FInputActionValue& InputActionValue);
	
	void OnSkill0(const FInputActionValue& InputActionValue);
	void OnSkill1(const FInputActionValue& InputActionValue);
	void OnSkill2(const FInputActionValue& InputActionValue);
	void OnSkill3(const FInputActionValue& InputActionValue);

	// Inventory Section
protected:
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	UInventoryComponent* PlayerInventory;

	float InteractionCheckFrequency;
	float InteractionCheckDistance;

	FTimerHandle TimerHandle_Interaction;

	FInteractionData InteractionData;

	// Inventory Function

	void ToggleMenu();

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();
};
