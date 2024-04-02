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
	UStaticMeshComponent* mMesh;

protected:
	virtual void BeginPlay() override;

public:
	void SetMesh(UStaticMesh* Mesh);
	void SetMesh(const FString& Path);
	
};
