#include "Item/ItemHelmet.h"

AItemHelmet::AItemHelmet()
{
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	mMesh->SetupAttachment(mRoot);
}

void AItemHelmet::BeginPlay()
{
	Super::BeginPlay();

}

void AItemHelmet::SetMesh(USkeletalMesh* Mesh)
{
	mMesh->SetSkeletalMesh(Mesh);
}

void AItemHelmet::SetMesh(const FString& Path)
{
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(GetWorld(),
		*Path);

	if (Mesh)
		mMesh->SetSkeletalMesh(Mesh);
}
