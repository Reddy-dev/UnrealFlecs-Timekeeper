using UnrealBuildTool;

public class TimekeeperTests : ModuleRules
{
	public TimekeeperTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp23;
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "CQTest", "SolidMacros", "FlecsLibrary",
			"UnrealFlecs", "UnrealFlecsTests", "Timekeeper"
		});
	}
}
