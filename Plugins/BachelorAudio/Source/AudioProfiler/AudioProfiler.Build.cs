using UnrealBuildTool;

public class AudioProfiler : ModuleRules
{
    public AudioProfiler(ReadOnlyTargetRules Target) : base(Target)  {
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
                "TestingHelper",
                "DeveloperSettings",
                "AudioMixer"
            });
        DynamicallyLoadedModuleNames.AddRange(new string[] {});
    }
}