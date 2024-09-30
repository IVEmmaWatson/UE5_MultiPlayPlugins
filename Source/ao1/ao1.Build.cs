// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ao1 : ModuleRules
{
	public ao1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// ���м��ص�ģ������
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","OnlineSubsystemSteam","OnlineSubsystem" });
	}
}
