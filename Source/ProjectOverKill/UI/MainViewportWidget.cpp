#include "MainViewportWidget.h"
#include "PlayerHUDWidget.h"
#include "UObject/UnrealTypePrivate.h"
#include "Animation/WidgetAnimation.h"
#include "MovieScene.h"

void UMainViewportWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainViewportWidget::SetName(const FString& Text)
{
	UI_PlayerHUD->SetName(Text);
}

void UMainViewportWidget::SetHP(int32 HP, int32 HPMax)
{
	UI_PlayerHUD->SetHP(HP, HPMax);
}

void UMainViewportWidget::SetMP(int32 MP, int32 MPMax)
{
	UI_PlayerHUD->SetMP(MP, MPMax);
}
