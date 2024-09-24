// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealGame/Character/SCharacterBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSCharacterBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UNREALGAME_API UClass* Z_Construct_UClass_ASCharacterBase();
	UNREALGAME_API UClass* Z_Construct_UClass_ASCharacterBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UnrealGame();
// End Cross Module References
	void ASCharacterBase::StaticRegisterNativesASCharacterBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASCharacterBase);
	UClass* Z_Construct_UClass_ASCharacterBase_NoRegister()
	{
		return ASCharacterBase::StaticClass();
	}
	struct Z_Construct_UClass_ASCharacterBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASCharacterBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealGame,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASCharacterBase_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Character/SCharacterBase.h" },
		{ "ModuleRelativePath", "Character/SCharacterBase.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASCharacterBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASCharacterBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASCharacterBase_Statics::ClassParams = {
		&ASCharacterBase::StaticClass,
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
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ASCharacterBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASCharacterBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASCharacterBase()
	{
		if (!Z_Registration_Info_UClass_ASCharacterBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASCharacterBase.OuterSingleton, Z_Construct_UClass_ASCharacterBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASCharacterBase.OuterSingleton;
	}
	template<> UNREALGAME_API UClass* StaticClass<ASCharacterBase>()
	{
		return ASCharacterBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASCharacterBase);
	struct Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Character_SCharacterBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Character_SCharacterBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASCharacterBase, ASCharacterBase::StaticClass, TEXT("ASCharacterBase"), &Z_Registration_Info_UClass_ASCharacterBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASCharacterBase), 2613440893U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Character_SCharacterBase_h_143538455(TEXT("/Script/UnrealGame"),
		Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Character_SCharacterBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Character_SCharacterBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
