#include "Item/ItemHelmet.h"

AItemHelmet::AItemHelmet()
{
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	mMesh->SetupAttachment(mRoot);
}

void AItemHelmet::BeginPlay()
{
	Super::BeginPlay();

}

void AItemHelmet::SetMesh(UStaticMesh* Mesh)
{
	mMesh->SetStaticMesh(Mesh);
}

void AItemHelmet::SetMesh(const FString& Path)
{
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(GetWorld(),
		*Path);

	if (Mesh)
		mMesh->SetStaticMesh(Mesh);
}
