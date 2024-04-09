#include "MainPlayerController.h"
#include "../Character/PlayerCharacter.h"
#include "../UI/POKHUD.h"
#include "Inventory/World/Pickup.h"
#include "../UI/MainViewportWidget.h"
#include "../AI/AIPawn.h"
#include "Components/InventoryComponent.h"

#include "Data/Input/BasicInputDataConfig.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>
		MainWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Main/UI/UI_MainViewport.UI_MainViewport_C'"));
	
	if (MainWidgetClass.Succeeded())
		mMainWidgetClass = MainWidgetClass.Class;

	InteractionCheckFrequency = 0.5f;
	InteractionCheckDistance = 225.0f;

	//GetPawn()->BaseEyeHeight = 76.f;

	PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	PlayerInventory->SetSlotsCapacity(20);
	PlayerInventory->SetWeightCapacity(50.0f);
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI	input;
	SetInputMode(input);

	bShowMouseCursor = true;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	const UMainInputDataConfig* MainInputDataConfig = GetDefault<UMainInputDataConfig>();
	Subsystem->AddMappingContext(MainInputDataConfig->DefaultContext, 0);

	// 위젯을 생성한다.
	mMainWidget = CreateWidget<UMainViewportWidget>(GetWorld(), mMainWidgetClass);
	mMainWidget->AddToViewport(10);

	HUD = Cast<APOKHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// InputComponent : 입력관리 컴포넌트. 플레이어 컨트롤러가 이미 가지고 있는 객체이다.

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UMainInputDataConfig* MainInputDataConfig = GetDefault<UMainInputDataConfig>();
	EnhancedInputComponent->BindAction(MainInputDataConfig->LookMouse, ETriggerEvent::Triggered, this, &ThisClass::OnLookMouse);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Attack, ETriggerEvent::Triggered, this, &ThisClass::OnAttack);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Jump, ETriggerEvent::Triggered, this, &ThisClass::OnJump);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Skill0, ETriggerEvent::Completed, this, &ThisClass::OnSkill0);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Skill1, ETriggerEvent::Completed, this, &ThisClass::OnSkill1);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Skill2, ETriggerEvent::Completed, this, &ThisClass::OnSkill2);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Skill3, ETriggerEvent::Completed, this, &ThisClass::OnSkill3);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Detect, ETriggerEvent::Completed, this, &ThisClass::OnDetect);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Ghost, ETriggerEvent::Completed, this, &ThisClass::OnGhost);
	
	EnhancedInputComponent->BindAction(MainInputDataConfig->Interaction, ETriggerEvent::Completed, this, &ThisClass::BeginInteract);
	//EnhancedInputComponent->BindAction(MainInputDataConfig->Interaction, ETriggerEvent::Completed, this, &ThisClass::EndInteract);

	EnhancedInputComponent->BindAction(MainInputDataConfig->ToggleMenu, ETriggerEvent::Completed, this, &ThisClass::ToggleMenu);

}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}

	if (mDetectEnable)
	{
		mDetectTime += DeltaTime;

		mDetectDelayTime += DeltaTime;

		if (mDetectDelayTime >= mDetectDelay)
		{
			mDetectDelayTime -= mDetectDelay;

			// 충돌처리를 진행한다.
			APawn* ControlPawn = GetPawn();
			FCollisionQueryParams	param(NAME_None, false, ControlPawn);

			FVector	Location = ControlPawn->GetActorLocation();

			TArray<FHitResult>	resultArray;
			bool IsCollision = GetWorld()->SweepMultiByChannel(
				resultArray, Location, Location,
				FQuat::Identity, ECC_GameTraceChannel8,
				FCollisionShape::MakeSphere(1000.f),
				param);

#if ENABLE_DRAW_DEBUG

			// 구를 그린다.
			FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;

			DrawDebugSphere(GetWorld(), Location,
				1000.f, 20, DrawColor, false,
				0.35f);
#endif

			if (IsCollision)
			{
				// 기존에 충돌되고 있던 액터들의 Occlusion을 모두
				// 제거한다.
				for (auto Actor : mDetectActorArray)
				{
					AAIPawn* AI = Cast<AAIPawn>(Actor);

					if (IsValid(AI))
					{
						AI->OnOcclusion(false);
					}

					else
					{
						APlayerCharacter* PlayerCharacter =
							Cast<APlayerCharacter>(Actor);

						if (IsValid(PlayerCharacter))
						{
							PlayerCharacter->OnOcclusion(false);
						}
					}
				}

				// 목록에 액터가 있을 경우 전부 비워준다.
				if (!mDetectActorArray.IsEmpty())
					mDetectActorArray.RemoveAll([](AActor* Actor) { return true; });

				for (auto& Hit : resultArray)
				{
					mDetectActorArray.Add(Hit.GetActor());

					AAIPawn* AI = Cast<AAIPawn>(Hit.GetActor());

					if (IsValid(AI))
					{
						AI->OnCustomDepthStencil(true);
						AI->OnOcclusion(true);
					}

					else
					{
						APlayerCharacter* PlayerCharacter =
							Cast<APlayerCharacter>(Hit.GetActor());

						if (IsValid(PlayerCharacter))
						{
							PlayerCharacter->OnCustomDepthStencil(true);
							PlayerCharacter->OnOcclusion(true);
						}
					}
				}
			}

			else
			{
				// 기존에 충돌되고 있던 액터들의 Occlusion을 모두
				// 제거한다.
				for (auto Actor : mDetectActorArray)
				{
					AAIPawn* AI = Cast<AAIPawn>(Actor);

					if (IsValid(AI))
					{
						AI->OnOcclusion(false);
					}

					else
					{
						APlayerCharacter* PlayerCharacter =
							Cast<APlayerCharacter>(Actor);

						if (IsValid(PlayerCharacter))
						{
							PlayerCharacter->OnOcclusion(false);
						}
					}
				}

				// 목록에 액터가 있을 경우 전부 비워준다.
				if (!mDetectActorArray.IsEmpty())
					mDetectActorArray.RemoveAll([](AActor* Actor) { return true; });
			}
		}

		if (mDetectTime >= mDetectDuration)
		{
			mDetectEnable = false;
			mDetectTime = 0.f;

			// 기존에 충돌되고 있던 액터들의 Occlusion을 모두
			// 제거한다.
			for (auto Actor : mDetectActorArray)
			{
				AAIPawn* AI = Cast<AAIPawn>(Actor);

				if (IsValid(AI))
				{
					AI->OnOcclusion(false);
				}

				else
				{
					APlayerCharacter* PlayerCharacter =
						Cast<APlayerCharacter>(Actor);

					if (IsValid(PlayerCharacter))
					{
						PlayerCharacter->OnOcclusion(false);
					}
				}
			}

			// 목록에 액터가 있을 경우 전부 비워준다.
			if (!mDetectActorArray.IsEmpty())
				mDetectActorArray.RemoveAll([](AActor* Actor) { return true; });
		}
	}
}

void AMainPlayerController::OnLookMouse(const FInputActionValue& InputActionValue)
{
	const FVector ActionValue = InputActionValue.Get<FVector>();
	AddYawInput(ActionValue.X);
	AddPitchInput(ActionValue.Y);
}

void AMainPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();

	const FRotator Rotation = K2_GetActorRotation();
	const FRotator YawRotation = FRotator(0.0, Rotation.Yaw, 0.0);
	const FVector ForwardVector = YawRotation.Vector();
	const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

	// 앞 뒤 이동
	const FVector ActionValue = InputActionValue.Get<FVector>();
	ControlledPawn->AddMovementInput(ForwardVector, ActionValue.Y);
	// 좌 우 이동
	ControlledPawn->AddMovementInput(RightVector, ActionValue.X);

	// 이동 방향을 저장한다.
	// 먼저 ActionValue.X 는 왼쪽일때 -1, 오른쪽일때 1, 좌우로 움직이지 않을경우
	// 0이 들어오게 된다.
	mMoveDir = ActionValue.X * 90.f;

	// ActionValue.Y는 앞일때 1, 뒤일때 -1, 앞뒤로 움직이지 않을 경우 0이다.
	// 앞으로 이동할 경우
	if (ActionValue.Y > 0.f)
	{
		// 앞으로 이동하는데 왼쪽으로 이동하고 있을 경우
		// 왼쪽 전방 대각선 이동이다.
		if (ActionValue.X < 0.f)
			mMoveDir = -45.f;

		// 앞으로 이동하는데 오른쪽으로 이동하고 있을 경우
		// 오른쪽 전방 대각선 이동이다.
		else if (ActionValue.X > 0.f)
			mMoveDir = 45.f;
	}

	// 뒤로 이동할 경우
	else if (ActionValue.Y < 0.f)
	{
		// 뒤로 이동하는데 왼쪽으로 이동하고 있을 경우
		// 왼쪽 후방 대각선 이동이다.
		if (ActionValue.X < 0.f)
			mMoveDir = -135.f;

		// 뒤로 이동하는데 오른쪽으로 이동하고 있을 경우
		// 오른쪽 후방 대각선 이동이다.
		else if (ActionValue.X > 0.f)
			mMoveDir = 135.f;

		// 뒤로 이동할 경우
		else
			mMoveDir = 180.f;
	}
}

void AMainPlayerController::OnAttack(const FInputActionValue& InputActionValue)
{
	// 컨트롤하는 캐릭터의 애니메이션을 공격 모션으로 전환한다.
	// 애님인스턴스는 플레이어 캐릭터의 SkeletalMeshComponent에 있으므로
	// PlayerCharacter 를 얻어온다.
	APlayerCharacter* ControlledPawn = GetPawn<APlayerCharacter>();

	// PlayAttackMontage에서는 애님인스턴스의 공격 몽타주를 재생시켜준다.
	ControlledPawn->PlayAttackMontage();
}

void AMainPlayerController::OnJump(const FInputActionValue& InputActionValue)
{
	APlayerCharacter* ControlledPawn = GetPawn<APlayerCharacter>();

	ControlledPawn->PlayJump();
}

void AMainPlayerController::OnSkill0(const FInputActionValue& InputActionValue)
{
	APlayerCharacter* ControlledPawn = GetPawn<APlayerCharacter>();

	ControlledPawn->PlaySkillMontage(0);
}

void AMainPlayerController::OnSkill1(const FInputActionValue& InputActionValue)
{
	APlayerCharacter* ControlledPawn = GetPawn<APlayerCharacter>();

	ControlledPawn->PlaySkillMontage(1);
}

void AMainPlayerController::OnSkill2(const FInputActionValue& InputActionValue)
{
	APlayerCharacter* ControlledPawn = GetPawn<APlayerCharacter>();

	ControlledPawn->PlaySkillMontage(2);
}

void AMainPlayerController::OnSkill3(const FInputActionValue& InputActionValue)
{
	APlayerCharacter* ControlledPawn = GetPawn<APlayerCharacter>();

	ControlledPawn->PlaySkillMontage(3);
}

void AMainPlayerController::OnDetect(const FInputActionValue& InputActionValue)
{
	if (!mDetectEnable)
	{
		mDetectEnable = true;
		mDetectTime = 0.f;
		mDetectDelayTime = mDetectDelay;
	}
}

void AMainPlayerController::OnGhost(const FInputActionValue& InputActionValue)
{
	APlayerCharacter* PlayerCharacter = GetPawn<APlayerCharacter>();

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->OnGhost();
	}
}

void AMainPlayerController::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	// 연동이 안되어서 Pawn 하나 받은 후 적용
	FVector TraceStart{ GetPawn()->GetPawnViewLocation() };
	FVector TraceEnd{ TraceStart + (GetPawn()->GetViewRotation().Vector() * InteractionCheckDistance) };

	float LookDirection = FVector::DotProduct(GetPawn()->GetActorForwardVector(), GetPawn()->GetViewRotation().Vector());

	if (LookDirection > 0)
	{
		
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(GetPawn());
		FHitResult TraceHit;

		bool HitDetected = GetWorld()->SweepSingleByChannel(TraceHit, TraceStart, TraceEnd, 
			FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(100.f), QueryParams);

		if (HitDetected)
		{
			/*UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *TraceHit.GetActor()->GetName());
			UE_LOG(LogTemp, Warning, TEXT("Actor Location: %s"), *TraceHit.ImpactPoint.ToString());*/

			if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
				{
					//const float Distance = TraceHit.Distance;
				if (TraceHit.GetActor() != InteractionData.CurrentInteractable /*&& Distance <= InteractionCheckDistance*/)
				{
					FoundInteractable(TraceHit.GetActor());

					return;
				}

				if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
				{
					return;
				}
			}
		}
#if ENABLE_DRAW_DEBUG

		FVector CapsuleOrigin = TraceStart + (TraceEnd - TraceStart) * 0.5f;
		float CapsuleHalfHeight = 100.f;
		FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

		//DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, 100.f, FRotationMatrix::MakeFromZ(GetPawn()->GetActorForwardVector()).ToQuat(), DrawColor, false, 2.0f);

#endif
	}
	NoInteractableFound();

}

void AMainPlayerController::FoundInteractable(AActor* NewInteractable)
{
	if (IsInteracting())
	{
		EndInteract();
	}

	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}
	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);

	TargetInteractable->BeginFocus();
}

void AMainPlayerController::NoInteractableFound()
{

	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	// 이 라인은 아이템을 들고 있다면 인벤토리에 다시 집어넣을 때 
	// 가능하지를 체크할 수 있는 수단이 되기도 하기에 작성.
	// 및 충돌 발생할 가능성을 조금이나마 차단
	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		HUD->HideInteractionWidget();

		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}

}

void AMainPlayerController::BeginInteract()
{

	// verify nothing has changed with the interactable state since beginning interaction
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();

			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("else Interact"));

				GetWorldTimerManager().SetTimer(TimerHandle_Interaction,
					this,
					&AMainPlayerController::Interact,
					TargetInteractable->InteractableData.InteractionDuration,
					false);
			}

		}
	}

}

void AMainPlayerController::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Start EndInteract"));

	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}

	UE_LOG(LogTemp, Warning, TEXT("End EndInteract"));
}

void AMainPlayerController::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}

void AMainPlayerController::UpdateInteractionWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}

void AMainPlayerController::DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop)
{
	if (PlayerInventory->FindMatchingItem(ItemToDrop))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
		const FVector MainPlayerControllerSpawnLocation{ GetPawn()->GetActorLocation()+ (GetPawn()->GetActorForwardVector() * 50.0f)};

		const FTransform SpawnTransform(GetPawn()->GetActorRotation(), MainPlayerControllerSpawnLocation);

		const int32 RemovedQuantity = PlayerInventory->RemoveAmountOfItem(ItemToDrop, QuantityToDrop);

		APickup* Pickup = GetWorld()->SpawnActor<APickup>(APickup::StaticClass(), SpawnTransform, SpawnParams);
		Pickup->InitializeDrop(ItemToDrop, QuantityToDrop);
	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item to drop was somehow null!"));
	}

}

void AMainPlayerController::ToggleMenu()
{
	HUD->ToggleMenu();
}



