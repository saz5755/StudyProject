#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class AMainPlayerController;

UCLASS()
class PROJECTOVERKILL_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	// 이 함수는 위젯이 생성될 때 딱 1번만 호출된다.
	//  PlayerHUDWidget.h에서도 호출되고 있으므로 추후 처리
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(
		const FGeometry& InGeometry, 
		const FDragDropEvent& InDragDropEvent, 
		UDragDropOperation* InOperation) override;

public:
	UPROPERTY()
	AMainPlayerController* PlayerController;

	
};
