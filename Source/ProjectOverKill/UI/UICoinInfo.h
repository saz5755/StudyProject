// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UICoinInfo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTOVERKILL_API UUICoinInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetRemainCoinCount(const int NewCoinCount);

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CoinText = nullptr;
};
