// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealGame/Controller/SPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSPlayerController() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UNREALGAME_API UClass* Z_Construct_UClass_ASPlayerController();
	UNREALGAME_API UClass* Z_Construct_UClass_ASPlayerController_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UnrealGame();
// End Cross Module References
	void ASPlayerController::StaticRegisterNativesASPlayerController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASPlayerController);
	UClass* Z_Construct_UClass_ASPlayerController_NoRegister()
	{
		return ASPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ASPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealGame,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASPlayerController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Controller/SPlayerController.h" },
		{ "ModuleRelativePath", "Controller/SPlayerController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASPlayerController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASPlayerController_Statics::ClassParams = {
		&ASPlayerController::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ASPlayerController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASPlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASPlayerController()
	{
		if (!Z_Registration_Info_UClass_ASPlayerController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASPlayerController.OuterSingleton, Z_Construct_UClass_ASPlayerController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASPlayerController.OuterSingleton;
	}
	template<> UNREALGAME_API UClass* StaticClass<ASPlayerController>()
	{
		return ASPlayerController::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASPlayerController);
	ASPlayerController::~ASPlayerController() {}
	struct Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Controller_SPlayerController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Controller_SPlayerController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASPlayerController, ASPlayerController::StaticClass, TEXT("ASPlayerController"), &Z_Registration_Info_UClass_ASPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASPlayerController), 2348747384U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Controller_SPlayerController_h_868072149(TEXT("/Script/UnrealGame"),
		Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Controller_SPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Controller_SPlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
