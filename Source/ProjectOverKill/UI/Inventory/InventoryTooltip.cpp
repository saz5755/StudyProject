#include "UI/Inventory/InventoryTooltip.h"
#include "UI/Inventory/InventoryItemSlot.h"
#include "Item//ItemBase.h"
#include "Components/TextBlock.h"


void UInventoryTooltip::NativeConstruct()
{
	Super::NativeConstruct();

	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemType = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemType")));
	DamageValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageValue")));
	ArmorRating = Cast<UTextBlock>(GetWidgetFromName(TEXT("ArmorRating")));
	UsageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UsageText")));
	StackSize = Cast<UTextBlock>(GetWidgetFromName(TEXT("StackSize")));
	MaxStackSize = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxStackSize")));
	StackWeight = Cast<UTextBlock>(GetWidgetFromName(TEXT("StackWeight")));
	ItemDescription = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDescription")));

	const UItemBase* ItemBeingHovered = InventorySlotBeginHovered->GetItemReference();

	switch (ItemBeingHovered->ItemType)
	{
	case EItemType::Armor:
		break;

	case EItemType::Weapon:
		break;

	case EItemType::Shield:
		break;

	case EItemType::Spell:
		break;

	case EItemType::Consumable:
		ItemType->SetText(FText::FromString("Consumable"));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
		break;

	case EItemType::Quest:
		break;

	case EItemType::Mundane:
		ItemType->SetText(FText::FromString("Mundane Item"));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
		UsageText->SetVisibility(ESlateVisibility::Collapsed);
		break;

	default: ;
	}

	//ItemName->SetText(ItemBeingHovered->TextData.Name);
	//DamageValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.DamageValue));
	//ArmorRating->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.ArmorRating));
	//UsageText->SetText(ItemBeingHovered->TextData.UsageText);
	//ItemDescription->SetText(ItemBeingHovered->TextData.Description);
	////SellValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.SellValue));
	//StackWeight->SetText(FText::AsNumber(ItemBeingHovered->GetItemStackWeight()));

	if (ItemBeingHovered->NumericData.bIsStackable)
	{
		MaxStackSize->SetText(FText::AsNumber(ItemBeingHovered->NumericData.MaxStackSize));
	}
	else
	{
		MaxStackSize->SetVisibility(ESlateVisibility::Collapsed);
	}
}
