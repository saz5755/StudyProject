// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBoots.h"

AItemBoots::AItemBoots()
{
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	mMesh->SetupAttachment(mRoot);
}

void AItemBoots::BeginPlay()
{
	Super::BeginPlay();

}

void AItemBoots::SetMesh(USkeletalMesh* Mesh)
{
	mMesh->SetSkeletalMesh(Mesh);

}

void AItemBoots::SetMesh(const FString& Path)
{
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(GetWorld(),
		*Path);

	if (Mesh)
		mMesh->SetSkeletalMesh(Mesh);
}
