// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWeapon.h"

AItemWeapon::AItemWeapon()
{
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	mMesh->SetupAttachment(mRoot);
}

void AItemWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AItemWeapon::SetMesh(USkeletalMesh* Mesh)
{
	mMesh->SetSkeletalMesh(Mesh);
}

void AItemWeapon::SetMesh(const FString& Path)
{
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(GetWorld(),
		*Path);

	if (Mesh)
		mMesh->SetSkeletalMesh(Mesh);
}
