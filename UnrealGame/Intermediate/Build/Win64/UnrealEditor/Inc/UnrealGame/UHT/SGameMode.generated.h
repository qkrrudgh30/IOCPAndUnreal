// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Game/SGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UNREALGAME_SGameMode_generated_h
#error "SGameMode.generated.h already included, missing '#pragma once' in SGameMode.h"
#endif
#define UNREALGAME_SGameMode_generated_h

#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_SPARSE_DATA
#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_RPC_WRAPPERS
#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_ACCESSORS
#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASGameMode(); \
	friend struct Z_Construct_UClass_ASGameMode_Statics; \
public: \
	DECLARE_CLASS(ASGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/UnrealGame"), NO_API) \
	DECLARE_SERIALIZER(ASGameMode)


#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_INCLASS \
private: \
	static void StaticRegisterNativesASGameMode(); \
	friend struct Z_Construct_UClass_ASGameMode_Statics; \
public: \
	DECLARE_CLASS(ASGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/UnrealGame"), NO_API) \
	DECLARE_SERIALIZER(ASGameMode)


#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASGameMode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASGameMode); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASGameMode(ASGameMode&&); \
	NO_API ASGameMode(const ASGameMode&); \
public: \
	NO_API virtual ~ASGameMode();


#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASGameMode(ASGameMode&&); \
	NO_API ASGameMode(const ASGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASGameMode); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASGameMode) \
	NO_API virtual ~ASGameMode();


#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_12_PROLOG
#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_SPARSE_DATA \
	FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_RPC_WRAPPERS \
	FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_ACCESSORS \
	FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_INCLASS \
	FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_SPARSE_DATA \
	FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_ACCESSORS \
	FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> UNREALGAME_API UClass* StaticClass<class ASGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_qkrru_Desktop_Server_UnrealGame_Source_UnrealGame_Game_SGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
