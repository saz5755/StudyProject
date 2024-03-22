// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

// Sets default values
AGhost::AGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mMesh);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		MtrlAsset(TEXT("/Script/Engine.Material'/Game/Material/MT_Ghost.MT_Ghost'"));

	if (MtrlAsset.Succeeded())
		mGhostMaterial = MtrlAsset.Object;
}

// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGhost::CopySkeletalMesh(USkeletalMeshComponent* Mesh)
{
	mMesh->SetSkeletalMesh(Mesh->GetSkeletalMeshAsset());
	mMesh->CopyPoseFromSkeletalComponent(Mesh);

	int32	MtrlCount = Mesh->GetNumMaterials();

	for (int32 i = 0; i < MtrlCount; ++i)
	{
		mMaterialArray.Add(mMesh->CreateDynamicMaterialInstance(i, mGhostMaterial));
	}
}

