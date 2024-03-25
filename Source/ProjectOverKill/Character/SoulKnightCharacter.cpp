// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SoulKnightCharacter.h"

ASoulKnightCharacter::ASoulKnightCharacter()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.f);
	GetCapsuleComponent()->SetCapsuleRadius(32.f);

	mFaceCapture->SetRelativeLocation(FVector(0.0, 76.0, 143.0));
	mFaceCapture->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mCameraArm->SetRelativeLocation(FVector(0.0, 0.0, 54.0));
	mCameraArm->SetRelativeRotation(FRotator(-15.0, 0.0, 0.0));

	mCameraArm->TargetArmLength = 500.f;

	GetMesh()->SetRelativeLocation(FVector(-6.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0f, 0.0));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonYin/Characters/Heroes/Yin/Meshes/Yin.Yin'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprint/Main/Animation/SoulKnight/AB_PlayerSoulKnight.AB_PlayerSoulKnight_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
}
