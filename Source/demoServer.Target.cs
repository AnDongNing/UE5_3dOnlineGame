// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using static UnrealBuildTool.ModuleRules;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class demoServerTarget : TargetRules
{
    public demoServerTarget(TargetInfo Target) : base(Target)
    {
        WindowsPlatform.bStrictConformanceMode = true;

        Type = TargetType.Server;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        BuildEnvironment = TargetBuildEnvironment.Shared;
        ExtraModuleNames.Add("demo");
    }
}
