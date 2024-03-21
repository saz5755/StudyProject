// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KDT1 : ModuleRules
{
	public KDT1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject"
			, "Engine"
			, "InputCore"
			, "UMG"
			, "EnhancedInput"
			, "AIModule"
			, "NavigationSystem"
			, "Niagara"
			, "LevelSequence"
			, "MovieScene"
			, "MediaAssets"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.Add("KDT1");
        PublicIncludePaths.Add("KDT1/Actors");
        PublicIncludePaths.Add("KDT1/Components");

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
