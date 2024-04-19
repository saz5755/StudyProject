#include "Inventory/World/Pickup.h"
#include "../../Item/ItemBase.h"
#include "Components/InventoryComponent.h"
#include "Player/MainPlayerController.h"
#include "Item/ItemManager.h"
#include "Item/ItemWeapon.h"
#include "Item/ItemArmor.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetSimulatePhysics(true);
	PickupMesh->SetupAttachment(mRoot);

	// pickup가능한 아이템의 경우에는 메시 하위로 이펙트를 적용시킴으로써 
	// 아이템의 좌표가 바뀌어도 따라가도록 설정
	EmbersEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	EmbersEffect->SetupAttachment(PickupMesh);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> ItemEffect(TEXT("/Script/Niagara.NiagaraSystem'/Game/Effect/Niaraga/NS_Embers.NS_Embers'"));

	if (ItemEffect.Succeeded())
	{
		EmbersEffect->SetAsset(ItemEffect.Object);
	}
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(UItemBase::StaticClass(), ItemQuantity);

}

void APickup::InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
	if (!DesiredItemID.IsEmpty())
	{
		const UItemManager* Mgr = GetDefault<UItemManager>();
		const FItemData* ItemData = Mgr->FindItem(DesiredItemID);

		ItemReference = NewObject<UItemBase>(this, BaseClass);

		ItemReference->ID = ItemData->ID;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->ItemQuality = ItemData->ItemQuality;
		ItemReference->NumericData = ItemData->NumericData;
		ItemReference->TextData = ItemData->TextData;
		ItemReference->AssetData = ItemData->AssetData;
		
		ItemReference->NumericData.bIsStackable = (ItemData->NumericData.MaxStackSize > 1) ? true : false;
		InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

		PickupMesh->SetStaticMesh(ItemData->AssetData.Mesh);
	
		UpdateInteractableData();

		switch (ItemReference->ItemType)
		{
		case EItemType::Armor:
			EmbersEffect->SetColorParameter(TEXT("Color"), AItemArmor::SetItemArmorColor());
			break;
		case EItemType::Weapon:
			EmbersEffect->SetColorParameter(TEXT("Color"), AItemWeapon::SetItemWeaponColor());
			break;
		case EItemType::Shield:
			break;
		case EItemType::Spell:
			break;
		case EItemType::Boots:
			break;
		case EItemType::Consumable:
			break;
		case EItemType::Quest:
			break;
		case EItemType::Mundane:
			break;
		}
	}
}

void APickup::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	ItemReference = ItemToDrop;

	InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);
	ItemReference->NumericData.Weight = ItemToDrop->GetItemSingleWeight();
	ItemReference->OwningInventory = nullptr;
	PickupMesh->SetStaticMesh(ItemToDrop->AssetData.Mesh);

	UpdateInteractableData();

}

void APickup::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Action = ItemReference->TextData.InteractionText;
	InstanceInteractableData.Name = ItemReference->TextData.Name;
	InstanceInteractableData.Quantity = ItemReference->Quantity;
	InteractableData = InstanceInteractableData;
}

void APickup::BeginFocus()
{
	if (PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(true);
	}
}

void APickup::EndFocus()
{
	if (PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(false);
	}
}

void APickup::Interact(AMainPlayerController* PlayerController)
{
	if (PlayerController)
	{
		TakePickup(PlayerController);
	}
}


void APickup::TakePickup(const AMainPlayerController* Taker)
{
	if (!IsPendingKillPending())
	{
		if (ItemReference)
		{
			if (UInventoryComponent* PlayerInventory = Taker->GetInventory())
			{
				const FItemAddResult AddResult = PlayerInventory->HandleAddItem(ItemReference);

				switch (AddResult.OperationResult)
				{
					case EItemAddResult::IAR_NoItemAdded:
						break;

					case EItemAddResult::IAR_PartialAmountItemAdded:
						UpdateInteractableData();
						Taker->UpdateInteractionWidget();  
						break;

					case EItemAddResult::IAR_AllItemAdded:
						Destroy();
						break;
				}
				UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player inventory component is null!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup internal item reference was somehow null!"));

		}
	}
}

void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickup, DesiredItemID))
	{
		const UItemManager* Mgr = GetDefault<UItemManager>();

		const FItemData* ItemData = Mgr->FindItem(DesiredItemID);

		if (ItemData)
		{
			PickupMesh->SetStaticMesh(ItemData->AssetData.Mesh);
		}
	}
}

