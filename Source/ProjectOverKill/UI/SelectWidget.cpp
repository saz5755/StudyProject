#include "SelectWidget.h"
#include "../Character/SelectCharacter/CharacterSelectPlayerController.h"

void USelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStartButton")));
	mInputName = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("InputName")));

	mStartButton->OnClicked.AddDynamic(this, &USelectWidget::StartButtonClick);
}

void USelectWidget::SetStartButtonEnable(bool Enable)
{
	mStartButton->SetIsEnabled(Enable);
}

void USelectWidget::StartButtonClick()
{	
	// 이름을 입력하지 않았다면 처리하지 않는다.
	if (mInputName->GetText().IsEmpty())
		return;

	EPlayerType	Type = 
		GetOwningPlayer<ACharacterSelectPlayerController>()->GetPlayerType();

	FString	Name = mInputName->GetText().ToString();

	UE_LOG(PROJECTOVERKILL, Warning, TEXT("Name : %s"), *Name);

	FString	Option = FString::Printf(TEXT("Type=%d?InputName=%s"),
		(int32)Type, *Name);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainForest"), true,
		Option);
}
