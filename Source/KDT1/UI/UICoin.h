// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UICoinInfo.h"
#include "UICoin.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API UUICoin : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	UUICoinInfo* GetCoinInfo() const { return CoinInfo; }

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UUICoinInfo* CoinInfo = nullptr;
};
