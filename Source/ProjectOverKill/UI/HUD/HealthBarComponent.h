#pragma once

#include "../../GameInfo.h"
#include "Components/WidgetComponent.h"
#include "HealthBarComponent.generated.h"

UCLASS()
class PROJECTOVERKILL_API UHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	void SetHealthPercent(float Percent);
	UHealthBar* GetHealthBarWidget() {return HealthBarWidget;}

private:
	UPROPERTY()
	class UHealthBar* HealthBarWidget;
};