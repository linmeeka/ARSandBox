// Fill out your copyright notice in the Description page of Project Settings.
using System.IO;
using UnrealBuildTool;

public class ARSandBox : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/")); }
    }

    public ARSandBox(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "RealSensePlugin" });

        PublicIncludePaths.AddRange(new string[] { "RealSensePlugin/Public" });

        PrivateDependencyModuleNames.AddRange(new string[] { "RealSensePlugin" });

        PrivateIncludePaths.AddRange(new string[] {"RealSensePlugin/Private" });

        PublicDependencyModuleNames.AddRange(new string[] { "ShaderCore", "RenderCore", "RHI", "RuntimeMeshComponent" });

        LoadKinect(Target);
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
    public bool LoadKinect(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        // Create kinect Path 
        string kinectPath = Path.Combine(ThirdPartyPath, "kinect");

        // Get Library Path 
        string LibPath = "";
        bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug && BuildConfiguration.bDebugBuildsActuallyUseDebugCRT;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LibPath = Path.Combine(kinectPath, "Lib", "x64");
            isLibrarySupported = true;
        }
        //         else if (Target.Platform == UnrealTargetPlatform.Win32)
        //         {
        //             LibPath = Path.Combine(kinectPath, "Lib", "x86");
        //             isLibrarySupported = true;
        //         }
        else
        {
            string Err = string.Format("{0} dedicated server is made to depend on {1}. We want to avoid this, please correct module dependencies.", Target.Platform.ToString(), this.ToString()); System.Console.WriteLine(Err);
        }

        if (isLibrarySupported)
        {
            //Add Include path 
            PublicIncludePaths.AddRange(new string[] { Path.Combine(kinectPath, "inc") });

            // Add Library Path 
            PublicLibraryPaths.Add(LibPath);

            // Add Dependencies 

            //Add Static Libraries
            //                 PublicAdditionalLibraries.Add("Kinect20.Face.lib");
            //                 PublicAdditionalLibraries.Add("Kinect20.Fusion.lib");
            PublicAdditionalLibraries.Add("Kinect20.lib");
            /*                PublicAdditionalLibraries.Add("Kinect20.VisualGestureBuilder.lib");*/
            //Add Dynamic Libraries
            //                 PublicDelayLoadDLLs.Add("Kinect20.Face.dll");
            //                 PublicDelayLoadDLLs.Add("Kinect20.Fusion.dll");
            PublicDelayLoadDLLs.Add("Kinect20.dll");
            /*                PublicDelayLoadDLLs.Add("Kinect20.VisualGestureBuilder.dll");*/

        }

        Definitions.Add(string.Format("WITH_KINECT_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }
}
