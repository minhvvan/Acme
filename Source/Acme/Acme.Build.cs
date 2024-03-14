// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Acme : ModuleRules
{
	public Acme(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "NavigationSystem", "AIModule", "GameplayTasks", "Niagara" });
	}
}
