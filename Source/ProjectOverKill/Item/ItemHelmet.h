#pragma once

#include "Item/ItemActor.h"
#include "ItemHelmet.generated.h"


UCLASS()
class PROJECTOVERKILL_API AItemHelmet : public AItemActor
{
	GENERATED_BODY()

public:
	AItemHelmet();

protected:
	USkeletalMeshComponent* mMesh;

protected:
	virtual void BeginPlay() override;

public:
	void SetMesh(USkeletalMesh* Mesh);
	void SetMesh(const FString& Path);
	
};
