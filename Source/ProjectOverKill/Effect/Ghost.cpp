#include "Ghost.h"

// Sets default values
AGhost::AGhost()
{
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mMesh);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		MtrlAsset(TEXT("/Script/Engine.Material'/Game/Material/MT_Ghost.MT_Ghost'"));

	if (MtrlAsset.Succeeded())
		mGhostMaterial = MtrlAsset.Object;
}

void AGhost::BeginPlay()
{
	Super::BeginPlay();
	
}

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

