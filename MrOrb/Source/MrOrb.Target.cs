// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MrOrbTarget : TargetRules
{
	public MrOrbTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "MrOrb" } );

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            ExtraModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "OnlineSubsystem" });

            ExtraModuleNames.Add("OnlineSubsystemGooglePlay");
            ExtraModuleNames.Add("OnlineSubsystem");
            ExtraModuleNames.Add("AndroidAdvertising");
        }
    }
}
