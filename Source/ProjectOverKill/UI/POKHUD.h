// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/HUD.h"
#include "POKHUD.generated.h"

struct FInteractableData;
class UInteractionWidget;
class UMainMenu;

UCLASS()
class PROJECTOVERKILL_API APOKHUD : public AHUD
{
	GENERATED_BODY()

public:
	// public : property
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;
	bool bIsMenuVisible;

	// public function
	APOKHUD();

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

protected:
	// protected : property
	UPROPERTY()
	UMainMenu* MainMenuWidget;
	
	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	// protected function
	virtual void BeginPlay() override;

};
