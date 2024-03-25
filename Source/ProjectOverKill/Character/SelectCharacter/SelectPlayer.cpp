// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayer.h"
#include "SelectAnimInstance.h"

// Sets default values
ASelectPlayer::ASelectPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	mMesh->SetupAttachment(mCapsule);

	SetRootComponent(mCapsule);

	mCapsule->bVisualizeComponent = true;

	// Mesh의 충돌을 없앤다.
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Capsule의 충돌을 Player로 지정한다.
	mCapsule->SetCollisionProfileName(TEXT("Player"));
}

// Called when the game starts or when spawned
void ASelectPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	mAnimInst = Cast<USelectAnimInstance>(mMesh->GetAnimInstance());
}

// Called every frame
void ASelectPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelectPlayer::SetSelect(bool Select)
{
	if (IsValid(mAnimInst))
		mAnimInst->SetSelect(Select);
}

void ASelectPlayer::OnCustomDepth(bool Enable)
{
	mMesh->SetRenderCustomDepth(Enable);
	//mMesh->SetCustomDepthStencilValue(17);
}

