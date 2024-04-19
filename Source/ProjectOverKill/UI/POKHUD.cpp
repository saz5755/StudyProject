#include "UI/POKHUD.h"
#include "UI/MainMenu.h"
#include "UI/Interaction/InteractionWidget.h"

APOKHUD::APOKHUD()
{
	static ConstructorHelpers::FClassFinder<UMainMenu> InventoryMenuRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Main/UI/InventoryUI/WBP_MainMenu.WBP_MainMenu_C'"));
	if (InventoryMenuRef.Succeeded())
	{
		MainMenuClass = InventoryMenuRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UInteractionWidget> InteractionWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Main/UI/InventoryUI/WBP_InteractionWidget.WBP_InteractionWidget_C'"));
	if (InteractionWidgetRef.Succeeded())
	{
		InteractionWidgetClass = InteractionWidgetRef.Class;
	}
}

void APOKHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APOKHUD::DisplayMenu()
{
	if (MainMenuClass)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APOKHUD::HideMenu()
{
	if (MainMenuClass)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APOKHUD::ToggleMenu()
{
	if (bIsMenuVisible)
	{
		HideMenu();

		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisplayMenu();
		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void APOKHUD::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APOKHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		// 확인 필요
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APOKHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractableData);
	}
}
