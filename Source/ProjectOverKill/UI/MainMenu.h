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
	// �� �Լ��� ������ ������ �� �� 1���� ȣ��ȴ�.
	//  PlayerHUDWidget.h������ ȣ��ǰ� �����Ƿ� ���� ó��
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
