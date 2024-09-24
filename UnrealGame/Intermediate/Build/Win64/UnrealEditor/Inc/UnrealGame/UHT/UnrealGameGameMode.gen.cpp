// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealGame/UnrealGameGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealGameGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UNREALGAME_API UClass* Z_Construct_UClass_AUnrealGameGameMode();
	UNREALGAME_API UClass* Z_Construct_UClass_AUnrealGameGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UnrealGame();
// End Cross Module References
	void AUnrealGameGameMode::StaticRegisterNativesAUnrealGameGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AUnrealGameGameMode);
	UClass* Z_Construct_UClass_AUnrealGameGameMode_NoRegister()
	{
		return AUnrealGameGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AUnrealGameGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUnrealGameGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealGame,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUnrealGameGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "UnrealGameGameMode.h" },
		{ "ModuleRelativePath", "UnrealGameGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUnrealGameGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUnrealGameGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AUnrealGameGameMode_Statics::ClassParams = {
		&AUnrealGameGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AUnrealGameGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUnrealGameGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUnrealGameGameMode()
	{
		if (!Z_Registration_Info_UClass_AUnrealGameGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AUnrealGameGameMode.OuterSingleton, Z_Construct_UClass_AUnrealGameGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AUnrealGameGameMode.OuterSingleton;
	}
	template<> UNREALGAME_API UClass* StaticClass<AUnrealGameGameMode>()
	{
		return AUnrealGameGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUnrealGameGameMode);
	AUnrealGameGameMode::~AUnrealGameGameMode() {}
	struct Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_UnrealGameGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_UnrealGameGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AUnrealGameGameMode, AUnrealGameGameMode::StaticClass, TEXT("AUnrealGameGameMode"), &Z_Registration_Info_UClass_AUnrealGameGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AUnrealGameGameMode), 3794512480U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_UnrealGameGameMode_h_2502543869(TEXT("/Script/UnrealGame"),
		Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_UnrealGameGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_UnrealGameGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
