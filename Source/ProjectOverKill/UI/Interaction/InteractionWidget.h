#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class AMainPlayerController;
struct FInteractableData;
class UTextBlock;
class UProgressBar;

UCLASS()
class PROJECTOVERKILL_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Player Reference")
	AMainPlayerController* PlayerReference;

	void UpdateWidget(const FInteractableData* InteractableData) const;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	UTextBlock* ActionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	UTextBlock* QuantityText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	UTextBlock* KeyPressText;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	UProgressBar* InteractionProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interaction Data")
	float CurrentInteractionDuration;

	UFUNCTION(Category = "Interaction Widget | Interaction Data")
	float UpdateInteractionProgress();

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
};
