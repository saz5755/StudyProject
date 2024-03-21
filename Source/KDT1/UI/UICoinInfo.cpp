// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UICoinInfo.h"

void UUICoinInfo::SetRemainCoinCount(const int NewCoinCount)
{
	if (!IsValid(CoinText)) 
	{
		ensureAlwaysMsgf(false, TEXT("CoinText is nullptr"));
		return; 
	}
	const FText Text = FText::Format(NSLOCTEXT("Dumy","Key", "Coin: {0}"), NewCoinCount);
	CoinText->SetText(Text);
}
