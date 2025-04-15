using UnrealBuildTool;

public class AudioPlayerPawn : ModuleRules
{
    public AudioPlayerPawn(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "Engine",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Slate",
                "SlateCore",
                "EnhancedInput", 
                "AudioProfiler",
            }
        );
    }
}