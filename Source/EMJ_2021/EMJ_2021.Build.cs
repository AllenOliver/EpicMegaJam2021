// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EMJ_2021 : ModuleRules
{
    public EMJ_2021(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;
    }
}