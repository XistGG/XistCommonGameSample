// Copyright (c) 2023 xist.gg

using UnrealBuildTool;
using System.Collections.Generic;

public class XcgsEditorTarget : TargetRules
{
	public XcgsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "XistCommonGameSample" } );
	}
}
