#include "BasicInputDataConfig.h"

UBasicInputDataConfig::UBasicInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprint/Lobby/Input/IMC_Lobby.IMC_Lobby'") };
		if (Asset.Succeeded())
		{
			DefaultContext = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Lobby/Input/IA_Move.IA_Move'") };
		if (Asset.Succeeded())
		{
			Move = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Lobby/Input/IA_LookMouse.IA_LookMouse'") };
		if (Asset.Succeeded())
		{
			Look = Asset.Object;
		}
	}
}

USelectInputDataConfig::USelectInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprint/CharacterSelect/Input/IMC_Select.IMC_Select'") };
		if (Asset.Succeeded())
		{
			DefaultContext = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/CharacterSelect/Input/IA_Select.IA_Select'") };
		if (Asset.Succeeded())
		{
			Select = Asset.Object;
		}
	}
}

UMainInputDataConfig::UMainInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprint/Main/Input/IMC_MainDefault.IMC_MainDefault'") };
		if (Asset.Succeeded())
		{
			DefaultContext = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_LookMouse.IA_LookMouse'") };
		if (Asset.Succeeded())
		{
			LookMouse = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_Move.IA_Move'") };
		if (Asset.Succeeded())
		{
			Move = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_MainAttack.IA_MainAttack'") };
		if (Asset.Succeeded())
		{
			Attack = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_Jump.IA_Jump'") };
		if (Asset.Succeeded())
		{
			Jump = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_Skill0.IA_Skill0'") };
		if (Asset.Succeeded())
		{
			Skill0 = Asset.Object;
		}
	}
	
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_Skill1.IA_Skill1'") };
		if (Asset.Succeeded())
		{
			Skill1 = Asset.Object;
		}
	}	
	
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_Skill2.IA_Skill2'") };
		if (Asset.Succeeded())
		{
			Skill2 = Asset.Object;
		}
	}
	
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_Skill3.IA_Skill3'") };
		if (Asset.Succeeded())
		{
			Skill3 = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_Detect.IA_Detect'") };
		if (Asset.Succeeded())
		{
			Detect = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_Ghost.IA_Ghost'") };
		if (Asset.Succeeded())
		{
			Ghost = Asset.Object;
		}
	}
	
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_Interaction.IA_Interaction'") };
		if (Asset.Succeeded())
		{
			Interaction = Asset.Object;
		}
	}	

	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Main/Input/IA_Toggle.IA_Toggle'") };
		if (Asset.Succeeded())
		{
			ToggleMenu = Asset.Object;
		}
	}
	
}
