#pragma once

#include "../../Item/ItemActor.h"
#include "../Interfaces/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class UItemBase;
class AMainPlayerController;

UCLASS()
class PROJECTOVERKILL_API APickup : public AItemActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	APickup();

	void InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity);

	void InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity);

	FORCEINLINE UItemBase* GetItemData() { return ItemReference; }

	virtual void BeginFocus() override;
	virtual void EndFocus() override;

protected:
	// Property
	UPROPERTY(VisibleAnywhere, Category = "Pickup | Components")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, Category = "Pickup | Item Initialization")
	FString DesiredItemID;

	UPROPERTY(EditAnywhere, Category = "Pickup | Item Reference")
	UItemBase* ItemReference;

	UPROPERTY(EditAnywhere, Category = "Pickup | Interaction")
	FInteractableData InstanceInteractableData;

	UPROPERTY(EditAnywhere, Category = "Pickup | Item Initialization")
	int32 ItemQuantity;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* EmbersEffect;
	
public:
	void SetItemID(const FString& ID)
	{
		DesiredItemID = ID;
	}

	//UPROPERTY(EditAnywhere, Category = "Pickup | Interaction")
	//FItemNumericData NumericDataTest;

	// Function
	virtual void BeginPlay() override;

	virtual void Interact(AMainPlayerController* PlayerController) override;
	void UpdateInteractableData();

	void TakePickup(const AMainPlayerController* Taker);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif 

};
