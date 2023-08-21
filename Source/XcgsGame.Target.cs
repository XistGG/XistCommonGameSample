// Copyright (c) 2023 xist.gg

using UnrealBuildTool;
using System.Collections.Generic;

public class XcgsGameTarget : TargetRules
{
	public XcgsGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "XistCommonGameSample" } );
	}
}
