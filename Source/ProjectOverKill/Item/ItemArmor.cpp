// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemArmor.h"

AItemArmor::AItemArmor()
{
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	mMesh->SetupAttachment(mRoot);
}

void AItemArmor::BeginPlay()
{
	Super::BeginPlay();

}

void AItemArmor::SetMesh(USkeletalMesh* Mesh)
{
	mMesh->SetSkeletalMesh(Mesh);
}

void AItemArmor::SetMesh(const FString& Path)
{
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(GetWorld(),
		*Path);

	if (Mesh)
		mMesh->SetSkeletalMesh(Mesh);
}
