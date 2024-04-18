#include "Item/PickupItemWeapon.h"
#include "NiagaraComponent.h"

APickupItemWeapon::APickupItemWeapon()
{
	EmbersEffect->SetColorParameter(TEXT("Color"), FLinearColor(100.f, 100.f, 20.f, 1.f));
}
