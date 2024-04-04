#pragma once

#include "CoreMinimal.h"
#include "Item/ItemActor.h"
#include "ItemArmor.generated.h"

UCLASS()
class PROJECTOVERKILL_API AItemArmor : public AItemActor
{
	GENERATED_BODY()

public:
	AItemArmor();

protected:
	USkeletalMeshComponent* mMesh;

protected:
	virtual void BeginPlay() override;

public:
	void SetMesh(USkeletalMesh* Mesh);
	void SetMesh(const FString& Path);

	
};
