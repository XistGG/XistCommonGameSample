// Copyright (c) 2023 xist.gg

using UnrealBuildTool;

public class XistCommonGameSample : ModuleRules
{
	public XistCommonGameSample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

        PublicIncludePaths.AddRange(new string[] {
            "XistCommonGameSample",
        });

        PrivateIncludePaths.AddRange(new string[] {
        });

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"CommonGame",
			"CommonInput",
			"CommonUI",
			"EnhancedInput",
			"GameplayMessageRuntime",
			"GameplayTags",
			"ModularGameplay",
			"ModularGameplayActors",
			"UMG",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
