// Copyright ubyte digital. All rights reserved. https://ubyte.dev

using UnrealBuildTool;

public class SoftTagBodyExample : ModuleRules
{
	public SoftTagBodyExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
				
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"GameplayTags",
				"SoftTagBody",
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
