// Copyright ubyte digital. All rights reserved. https://ubyte.dev

using UnrealBuildTool;

public class CommonActivityStrategy : ModuleRules
{
	public CommonActivityStrategy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
				
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"GameplayTags",
				"SoftTagBody",
				"WorkerActivityStrategyRuntime",
				"Projects"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
			}
			);
	}
}
