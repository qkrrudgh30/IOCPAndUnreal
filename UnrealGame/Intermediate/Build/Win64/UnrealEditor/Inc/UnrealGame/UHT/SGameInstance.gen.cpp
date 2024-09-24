// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealGame/Game/SGameInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSGameInstance() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UNREALGAME_API UClass* Z_Construct_UClass_ASCharacterBase_NoRegister();
	UNREALGAME_API UClass* Z_Construct_UClass_ASPlayerCharacter_NoRegister();
	UNREALGAME_API UClass* Z_Construct_UClass_USGameInstance();
	UNREALGAME_API UClass* Z_Construct_UClass_USGameInstance_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UnrealGame();
// End Cross Module References
	void USGameInstance::StaticRegisterNativesUSGameInstance()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USGameInstance);
	UClass* Z_Construct_UClass_USGameInstance_NoRegister()
	{
		return USGameInstance::StaticClass();
	}
	struct Z_Construct_UClass_USGameInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OwnerPlayerCharacter_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_OwnerPlayerCharacter;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OtherCharacterClass_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_OtherCharacterClass;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USGameInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealGame,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USGameInstance_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Game/SGameInstance.h" },
		{ "ModuleRelativePath", "Game/SGameInstance.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USGameInstance_Statics::NewProp_OwnerPlayerCharacter_MetaData[] = {
		{ "ModuleRelativePath", "Game/SGameInstance.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_USGameInstance_Statics::NewProp_OwnerPlayerCharacter = { "OwnerPlayerCharacter", nullptr, (EPropertyFlags)0x0014000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(USGameInstance, OwnerPlayerCharacter), Z_Construct_UClass_ASPlayerCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USGameInstance_Statics::NewProp_OwnerPlayerCharacter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USGameInstance_Statics::NewProp_OwnerPlayerCharacter_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USGameInstance_Statics::NewProp_OtherCharacterClass_MetaData[] = {
		{ "Category", "SGameInstance" },
		{ "ModuleRelativePath", "Game/SGameInstance.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_USGameInstance_Statics::NewProp_OtherCharacterClass = { "OtherCharacterClass", nullptr, (EPropertyFlags)0x0014000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(USGameInstance, OtherCharacterClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ASCharacterBase_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USGameInstance_Statics::NewProp_OtherCharacterClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USGameInstance_Statics::NewProp_OtherCharacterClass_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USGameInstance_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USGameInstance_Statics::NewProp_OwnerPlayerCharacter,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USGameInstance_Statics::NewProp_OtherCharacterClass,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USGameInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USGameInstance>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USGameInstance_Statics::ClassParams = {
		&USGameInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_USGameInstance_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_USGameInstance_Statics::PropPointers),
		0,
		0x009000A8u,
		METADATA_PARAMS(Z_Construct_UClass_USGameInstance_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USGameInstance_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USGameInstance()
	{
		if (!Z_Registration_Info_UClass_USGameInstance.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USGameInstance.OuterSingleton, Z_Construct_UClass_USGameInstance_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USGameInstance.OuterSingleton;
	}
	template<> UNREALGAME_API UClass* StaticClass<USGameInstance>()
	{
		return USGameInstance::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USGameInstance);
	USGameInstance::~USGameInstance() {}
	struct Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameInstance_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameInstance_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USGameInstance, USGameInstance::StaticClass, TEXT("USGameInstance"), &Z_Registration_Info_UClass_USGameInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USGameInstance), 2955384082U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameInstance_h_3418848108(TEXT("/Script/UnrealGame"),
		Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameInstance_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
