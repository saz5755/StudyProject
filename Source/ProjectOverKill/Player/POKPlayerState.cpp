// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/POKPlayerState.h"
#include "MainPlayerController.h"
#include "../UI/MainViewportWidget.h"
#include "../Subsystem/DataSubsystem.h"

APOKPlayerState::APOKPlayerState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		PlayerDataAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Main/DT_PlayerData.DT_PlayerData'"));

	if (PlayerDataAsset.Succeeded())
		mPlayerDataTable = PlayerDataAsset.Object;
}

void APOKPlayerState::BeginPlay()
{
	Super::BeginPlay();

	FPlayerData* Data =
		mPlayerDataTable->FindRow<FPlayerData>(TEXT("Knight"), TEXT(""));

	if (Data)
	{
		mJob = Data->mJob;
		mAttackPoint = Data->mAttackPoint;
		mArmorPoint = Data->mArmorPoint;
		mHP = Data->mHPMax;
		mHPMax = Data->mHPMax;
		mMP = Data->mMPMax;
		mMPMax = Data->mMPMax;
		mMoveSpeed = Data->mMoveSpeed;
		mAttackDistance = Data->mAttackDistance;

		mLevel = 1;
		mExp = 0;
	}

	AMainPlayerController* Controller =
		GetWorld()->GetFirstPlayerController<AMainPlayerController>();

	Controller->GetMainWidget()->SetHP(mHP, mHPMax);
	Controller->GetMainWidget()->SetMP(mMP, mMPMax);
}
