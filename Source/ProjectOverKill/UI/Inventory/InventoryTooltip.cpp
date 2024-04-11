#include "UI/Inventory/InventoryTooltip.h"
#include "UI/Inventory/InventoryItemSlot.h"
#include "Item//ItemBase.h"
#include "Components/TextBlock.h"


void UInventoryTooltip::NativeConstruct()
{
	Super::NativeConstruct();

	ToolTipItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ToolTipItemName")));
	ItemType = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemType")));
	DamageValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageValue")));
	ArmorRating = Cast<UTextBlock>(GetWidgetFromName(TEXT("ArmorRating")));
	UsageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UsageText")));
	StackSize = Cast<UTextBlock>(GetWidgetFromName(TEXT("StackSize")));
	MaxStackSize = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxStackSize")));
	StackWeight = Cast<UTextBlock>(GetWidgetFromName(TEXT("StackWeight")));
	ItemDescription = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDescription")));
}

void UInventoryTooltip::SetItemToolTip(UObject* ItemData)
{
	const UInventoryItemSlot* ItemBeingHovered = Cast<UInventoryItemSlot>(ItemData);

	switch (ItemBeingHovered->GetItemReference()->ItemType)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inswitch ItemBeingHovered"));

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

	default:
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("Begin ItemName->SetText"));

	ToolTipItemName->SetText(ItemBeingHovered->GetItemReference()->TextData.Name);
	DamageValue->SetText(FText::AsNumber(ItemBeingHovered->GetItemReference()->ItemStatistics.DamageValue));
	ArmorRating->SetText(FText::AsNumber(ItemBeingHovered->GetItemReference()->ItemStatistics.ArmorRating));
	UsageText->SetText(ItemBeingHovered->GetItemReference()->TextData.UsageText);
	ItemDescription->SetText(ItemBeingHovered->GetItemReference()->TextData.Description);

	const FString WeightInfo =
	{ "Weight" + FString::SanitizeFloat(ItemBeingHovered->GetItemReference()->GetItemStackWeight()) };

	StackWeight->SetText(FText::AsNumber(ItemBeingHovered->GetItemReference()->GetItemStackWeight()));

	if (ItemBeingHovered->GetItemReference()->NumericData.bIsStackable)
	{
		const FString StackInfo =
		{ " Max stack size : " + FString::FromInt(ItemBeingHovered->GetItemReference()->NumericData.MaxStackSize) };

		MaxStackSize->SetText(FText::AsNumber(ItemBeingHovered->GetItemReference()->NumericData.MaxStackSize));
	}
	else
	{
		MaxStackSize->SetVisibility(ESlateVisibility::Collapsed);
	}
}
