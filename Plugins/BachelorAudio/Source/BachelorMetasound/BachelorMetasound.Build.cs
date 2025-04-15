using UnrealBuildTool;

public class BachelorMetasound : ModuleRules
{
    public BachelorMetasound(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "MetasoundEngine",
                "MetasoundGraphCore",
                "MetasoundFrontend",
                "MetasoundEditor",
                "AudioExtensions",
                "Serialization",
                "SignalProcessing",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
            }
        );
    }
}