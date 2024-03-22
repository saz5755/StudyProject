// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightCharacter.h"

AKnightCharacter::AKnightCharacter()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);

	mFaceCapture->SetRelativeLocation(FVector(0.0, 76.0, 143.0));
	mFaceCapture->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mCameraArm->SetRelativeLocation(FVector(0.0, 0.0, 54.0));
	mCameraArm->SetRelativeRotation(FRotator(-15.0, 0.0, 0.0));

	mCameraArm->TargetArmLength = 500.f;

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -96.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprint/Main/Animation/Knight/AB_PlayerKnight.AB_PlayerKnight_C'"));

	if(AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
}
