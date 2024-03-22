// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTOVERKILL_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// BindWidget을 해주면 여기에 선언된 변수의 이름과 동일한 이름의 위젯을 찾아서
	// 이 변수에 찾아준 위젯 객체의 메모리 주소를 저장해준다.
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* NameText;

	UProgressBar* mHPBar;
	UProgressBar* mMPBar;
	
protected:
	// 이 함수는 위젯이 생성될 때 딱 1번만 호출된다.
	virtual void NativeOnInitialized();

	// Construct 함수들은 AddToViewport 함수를 호출하면 호출된다.
	virtual void NativePreConstruct();
	virtual void NativeConstruct();

	// 이 함수는 RemoveFromParent 함수를 호출할 때 호출된다. Viewport에서 Remove될때
	// 호출되는 방식이다.
	virtual void NativeDestruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetName(const FString& Text);
	void SetHP(int32 HP, int32 HPMax);
	void SetMP(int32 MP, int32 MPMax);
};
