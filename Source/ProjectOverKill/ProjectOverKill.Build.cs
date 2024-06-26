// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectOverKill : ModuleRules
{
	public ProjectOverKill(ReadOnlyTargetRules Target) : base(Target)
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
			, "Slate"
			, "SlateCore"
			, "GeometryCollectionEngine"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.Add("ProjectOverKill");
        /*PublicIncludePaths.Add("ProjectOverKill/Actors");
        PublicIncludePaths.Add("ProjectOverKill/Components");*/

		// Uncomment if you are using Slate UI
		//PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
