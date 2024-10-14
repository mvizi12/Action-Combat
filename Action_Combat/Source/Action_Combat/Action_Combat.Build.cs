// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Action_Combat : ModuleRules
{
	public Action_Combat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//"AIModule" added by me
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule" });
	}
}
