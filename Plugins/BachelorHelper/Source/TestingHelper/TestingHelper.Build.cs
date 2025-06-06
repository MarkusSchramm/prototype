﻿using UnrealBuildTool;

public class TestingHelper : ModuleRules {
    public TestingHelper(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.AddRange(new string[] {});
        PrivateIncludePaths.AddRange(new string[] {});
        PublicDependencyModuleNames.AddRange(new string[] {
                "Core",
            });
        PrivateDependencyModuleNames.AddRange(new string[] {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd",
            });
        DynamicallyLoadedModuleNames.AddRange(new string[] {});
    }
}