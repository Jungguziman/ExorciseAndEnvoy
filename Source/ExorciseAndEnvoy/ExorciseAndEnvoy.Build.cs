// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ExorciseAndEnvoy : ModuleRules
{
	public ExorciseAndEnvoy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivatePCHHeaderFile = "PCH.h";
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG",
			"AIModule",
			"NavigationSystem",
			"GameplayTags",
			"Niagara",
			"AnimGraphRuntime"
		});

		PublicIncludePaths.AddRange(new string[] {
			ModuleDirectory,
			Path.Combine(ModuleDirectory, "Interface"),
			Path.Combine(ModuleDirectory, "UI"),
			Path.Combine(ModuleDirectory, "Subsystem"),
            Path.Combine(ModuleDirectory, "Game"), 
            Path.Combine(ModuleDirectory, "Exorcist"), 
            Path.Combine(ModuleDirectory, "Enemy"), 
            Path.Combine(ModuleDirectory, "Skill"),
			Path.Combine(ModuleDirectory, "Animation")
        });

		PrivateDependencyModuleNames.AddRange(new string[] {
		});

	}
}
