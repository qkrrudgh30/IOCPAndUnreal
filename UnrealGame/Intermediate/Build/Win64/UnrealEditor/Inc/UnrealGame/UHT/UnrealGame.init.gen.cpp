// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealGame_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_UnrealGame;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_UnrealGame()
	{
		if (!Z_Registration_Info_UPackage__Script_UnrealGame.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/UnrealGame",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x08636BF7,
				0xBCC911CA,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_UnrealGame.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_UnrealGame.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_UnrealGame(Z_Construct_UPackage__Script_UnrealGame, TEXT("/Script/UnrealGame"), Z_Registration_Info_UPackage__Script_UnrealGame, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x08636BF7, 0xBCC911CA));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
