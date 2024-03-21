// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectOverKill : ModuleRules
{
	public ProjectOverKill(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "ProjectOverKill" });

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

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.Add("ProjectOverKill");

        /*// Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        PrivateDependencyModuleNames.Add("OnlineSubsystem");*/
    }
}
