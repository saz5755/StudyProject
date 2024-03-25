// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Data/Input/BasicInputDataConfig.h"
#include "SelectPlayer.h"
#include "../UI/SelectWidget.h"
#include "../GameInstance/POKGameInstance.h"

ACharacterSelectPlayerController::ACharacterSelectPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;

	mHitActor = nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget>	SelectWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/CharacterSelect/UI_Select.UI_Select_C'"));

	if (SelectWidgetClass.Succeeded())
		mSelectWidgetClass = SelectWidgetClass.Class;
}

void ACharacterSelectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	mSelectWidget = CreateWidget<USelectWidget>(GetWorld(), mSelectWidgetClass);
	mSelectWidget->AddToViewport();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	const USelectInputDataConfig* MainInputDataConfig = GetDefault<USelectInputDataConfig>();
	Subsystem->AddMappingContext(MainInputDataConfig->DefaultContext, 0);

	FInputModeGameAndUI	InputMode;

	SetInputMode(InputMode);
}

void ACharacterSelectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// InputComponent : 입력관리 컴포넌트. 플레이어 컨트롤러가 이미 가지고 있는 객체이다.

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const USelectInputDataConfig* MainInputDataConfig = GetDefault<USelectInputDataConfig>();
	EnhancedInputComponent->BindAction(MainInputDataConfig->Select,
		ETriggerEvent::Completed, this, &ThisClass::OnSelect);
}

void ACharacterSelectPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult	result;
	bool Hit = GetHitResultUnderCursor(ECC_GameTraceChannel4, false, result);

	if (Hit)
	{
		mHitActor = result.GetActor();

		ASelectPlayer* SelectPlayer = Cast<ASelectPlayer>(mHitActor);

		if (IsValid(SelectPlayer))
		{
			SelectPlayer->OnCustomDepth(true);
		}
	}

	else
	{
		if (IsValid(mHitActor))
		{
			ASelectPlayer* SelectPlayer = Cast<ASelectPlayer>(mHitActor);

			if (IsValid(SelectPlayer))
			{
				SelectPlayer->OnCustomDepth(false);
			}
		}

		mHitActor = nullptr;
	}
}

void ACharacterSelectPlayerController::OnSelect(
	const FInputActionValue& InputActionValue)
{
	// 클릭을 했을때 마우스와 충돌되고 있는 Actor가 있을 경우
	if (IsValid(mHitActor))
	{
		ASelectPlayer* SelectPlayer = Cast<ASelectPlayer>(mHitActor);

		if (IsValid(SelectPlayer))
		{
			SelectPlayer->SetSelect(true);

			mSelectWidget->SetStartButtonEnable(true);

			mSelectPlayerType = SelectPlayer->GetPlayerType();
			GetWorld()->GetGameInstance<UPOKGameInstance>()->SetPlayerType(SelectPlayer->GetPlayerType());
		}
	}

	else
	{
		mSelectWidget->SetStartButtonEnable(false);
	}
}
