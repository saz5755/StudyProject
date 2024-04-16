#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "HealthBar.generated.h"

class UProgressBar;

UCLASS()
class PROJECTOVERKILL_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

};
