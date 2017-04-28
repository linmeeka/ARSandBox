// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ARSandBox : ModuleRules
{
	public ARSandBox(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "RealSensePlugin" });

        PublicIncludePaths.AddRange(new string[] { "RealSensePlugin/Public" });

        PrivateDependencyModuleNames.AddRange(new string[] { "RealSensePlugin" });

        PrivateIncludePaths.AddRange(new string[] {"RealSensePlugin/Private" });

        PublicDependencyModuleNames.AddRange(new string[] { "ShaderCore", "RenderCore", "RHI", "RuntimeMeshComponent" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
