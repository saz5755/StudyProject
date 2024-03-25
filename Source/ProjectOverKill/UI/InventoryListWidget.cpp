// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryListWidget.h"
#include "InventoryItemData.h"
#include "InventoryListItemWidget.h"
#include "../Item/ItemWeapon.h"
#include "../Character/PlayerCharacter.h"

void UInventoryListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mInventoryList = Cast<UListView>(GetWidgetFromName(TEXT("IntentoryList")));
	mCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	for (int32 i = 0; i < 10; ++i)
	{
		UInventoryItemData* Data = NewObject<UInventoryItemData>();

		Data->mIconTexture = LoadObject<UTexture2D>(GetWorld(),
			TEXT("/Script/Engine.Texture2D'/Game/Adventure_UI/Textures/Tex_victory.Tex_victory'"));
		Data->mName = TEXT("Sword");
		Data->mCount = 2;
		Data->mItemMesh = LoadObject<USkeletalMesh>(GetWorld(),
			TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Weapon_ForgingHammers/SK_Forging_Mallet_03.SK_Forging_Mallet_03'"));

		mInventoryList->AddItem(Data);
	}

	mInventoryList->OnItemClicked().AddUObject<UInventoryListWidget>(
		this, &UInventoryListWidget::ItemClick);
	mInventoryList->OnItemIsHoveredChanged().AddUObject<UInventoryListWidget>(
		this, &UInventoryListWidget::ItemHoveredChange);
	mInventoryList->OnItemDoubleClicked().AddUObject<UInventoryListWidget>(
		this, &UInventoryListWidget::ItemDoubleClick);
	//mInventoryList->OnItemSelectionChanged()

	// 처음 시작할때는 선택된 위젯이 없으므로 nullptr로
	// 초기화한다.
	mSelectWidget = nullptr;

	mCloseButton->OnClicked.AddDynamic(this,
		&UInventoryListWidget::CloseButtonClick);
}

void UInventoryListWidget::ItemClick(UObject* Obj)
{
	// 기존에 선택된 위젯이 있을 경우 해당 위젯의 Selection을
	// 안보이게 한다.
	if (mSelectWidget)
	{
		mSelectWidget->SetSelectionColor(0.f, 0.f, 0.f, 0.f);
	}

	UInventoryItemData* Data = Cast<UInventoryItemData>(Obj);

	// 선택된 위젯을 변경한다.
	mSelectWidget = Data->mItemWidget;

	mSelectWidget->SetSelectionColor(1.f, 1.f, 0.f, 0.3f);

	// 플레이어를 얻어온다.
	APlayerCharacter* PlayerCharacter =
		Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	PlayerCharacter->SetWeaponMesh(Data->mItemMesh);
}

void UInventoryListWidget::ItemDoubleClick(UObject* Obj)
{
	UInventoryItemData* Data = Cast<UInventoryItemData>(Obj);

	if (mSelectWidget == Data->mItemWidget)
	{
		Data->mItemWidget->SetSelectionColor(0.f, 0.f, 0.f, 0.f);
		mSelectWidget = nullptr;
	}

	//mInventoryList->ClearListItems();
	mInventoryList->RemoveItem(Obj);
}

void UInventoryListWidget::ItemHoveredChange(
	UObject* Obj, bool IsHovered)
{
	UInventoryItemData* Data = Cast<UInventoryItemData>(Obj);

	if (mSelectWidget == Data->mItemWidget)
		return;

	if (IsHovered)
	{
		Data->mItemWidget->SetSelectionColor(0.f, 1.f, 0.f, 0.3f);
	}

	else
	{
		Data->mItemWidget->SetSelectionColor(0.f, 0.f, 0.f, 0.f);
	}
}

void UInventoryListWidget::CloseButtonClick()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
