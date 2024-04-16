#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UProgressBar;

UCLASS()
class PROJECTOVERKILL_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct();

public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

};
