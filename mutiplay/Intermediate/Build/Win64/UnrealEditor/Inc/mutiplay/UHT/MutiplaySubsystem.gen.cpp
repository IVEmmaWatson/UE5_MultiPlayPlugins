// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "mutiplay/Public/MutiplaySubsystem.h"
#include "../../Source/Runtime/Engine/Classes/Engine/GameInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMutiplaySubsystem() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
	MUTIPLAY_API UClass* Z_Construct_UClass_UMutiplaySubsystem();
	MUTIPLAY_API UClass* Z_Construct_UClass_UMutiplaySubsystem_NoRegister();
	MUTIPLAY_API UFunction* Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature();
	MUTIPLAY_API UFunction* Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature();
	MUTIPLAY_API UFunction* Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_mutiplay();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics
	{
		struct _Script_mutiplay_eventMutiplayerOnCreateSessionComplete_Parms
		{
			bool bWasSuccessful;
		};
		static void NewProp_bWasSuccessful_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bWasSuccessful;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful_SetBit(void* Obj)
	{
		((_Script_mutiplay_eventMutiplayerOnCreateSessionComplete_Parms*)Obj)->bWasSuccessful = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful = { "bWasSuccessful", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(_Script_mutiplay_eventMutiplayerOnCreateSessionComplete_Parms), &Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "Comment", "//\n// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe0\xb2\xa5\xce\xaf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd""class,\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdint\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc4\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd6\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb5\xc4\xb2\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd0\xb1\xef\xbf\xbd\n// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc7\xb6\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb5\xef\xbf\xbd\xc7\xa9\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xb2\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xbf\xef\xbf\xbd\xef\xbf\xbd\xd4\xb0\xf3\xb6\xa8\xba\xcd\xb5\xef\xbf\xbd\xef\xbf\xbd\xc3\xb5\xc4\xba\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc4\xb2\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xa1\xef\xbf\xbd\n// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xac\xef\xbf\xbd\xe0\xb2\xa5\xce\xaf\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xd0\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xa3\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xd0\xb5\xc4\xb2\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xa3\xef\xbf\xbd\n// \xef\xbf\xbd\xef\xbf\xbd\xcc\xac\xef\xbf\xbd\xe0\xb2\xa5\xce\xaf\xef\xbf\xbd\xd0\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xbc\xef\xbf\xbd\xef\xbf\xbd\xca\xb9\xef\xbf\xbd\xc3\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xac\xd6\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd""c++\xef\xbf\xbd\xef\xbf\xbd\xca\xb9\xef\xbf\xbd\xc3\xa1\xef\xbf\xbd\n// \xef\xbf\xbd\xe0\xb2\xa5\xef\xbf\xbd\xef\xbf\xbd\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb5\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xd0\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xd0\xb6\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n// const TArray<FOnlineSessionSearchResult>& SearchResults\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe1\xb9\xb9\xef\xbf\xbd\xe5\xb6\xaf\xcc\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xaa\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe1\xbb\xb0\xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xaa\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe1\xbb\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xaa\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n// \xef\xbf\xbd\xef\xbf\xbd\xcc\xac\xef\xbf\xbd\xe0\xb2\xa5\xce\xaf\xef\xbf\xbd\xd0\xb0\xf3\xb6\xa8\xb5\xc4\xba\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xaa\xef\xbf\xbd\xef\xbf\xbdUFUNCTION\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n//\n" },
		{ "ModuleRelativePath", "Public/MutiplaySubsystem.h" },
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe0\xb2\xa5\xce\xaf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd""class,\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdint\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc4\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd6\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb5\xc4\xb2\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd0\xb1\xef\xbf\xbd\n\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc7\xb6\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb5\xef\xbf\xbd\xc7\xa9\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xb2\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xbf\xef\xbf\xbd\xef\xbf\xbd\xd4\xb0\xf3\xb6\xa8\xba\xcd\xb5\xef\xbf\xbd\xef\xbf\xbd\xc3\xb5\xc4\xba\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc4\xb2\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xa1\xef\xbf\xbd\n\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xac\xef\xbf\xbd\xe0\xb2\xa5\xce\xaf\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xd0\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xa3\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xd0\xb5\xc4\xb2\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xa3\xef\xbf\xbd\n\xef\xbf\xbd\xef\xbf\xbd\xcc\xac\xef\xbf\xbd\xe0\xb2\xa5\xce\xaf\xef\xbf\xbd\xd0\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xbc\xef\xbf\xbd\xef\xbf\xbd\xca\xb9\xef\xbf\xbd\xc3\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xac\xd6\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd""c++\xef\xbf\xbd\xef\xbf\xbd\xca\xb9\xef\xbf\xbd\xc3\xa1\xef\xbf\xbd\n\xef\xbf\xbd\xe0\xb2\xa5\xef\xbf\xbd\xef\xbf\xbd\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb5\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xd0\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xbb\xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xd0\xb6\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\nconst TArray<FOnlineSessionSearchResult>& SearchResults\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe1\xb9\xb9\xef\xbf\xbd\xe5\xb6\xaf\xcc\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xaa\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe1\xbb\xb0\xef\xbf\xbd\xef\xbf\xbd\xce\xaf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xaa\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe1\xbb\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xaa\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n\xef\xbf\xbd\xef\xbf\xbd\xcc\xac\xef\xbf\xbd\xe0\xb2\xa5\xce\xaf\xef\xbf\xbd\xd0\xb0\xf3\xb6\xa8\xb5\xc4\xba\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd2\xaa\xef\xbf\xbd\xef\xbf\xbdUFUNCTION\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_mutiplay, nullptr, "MutiplayerOnCreateSessionComplete__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::_Script_mutiplay_eventMutiplayerOnCreateSessionComplete_Parms), Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FMutiplayerOnCreateSessionComplete_DelegateWrapper(const FMulticastScriptDelegate& MutiplayerOnCreateSessionComplete, bool bWasSuccessful)
{
	struct _Script_mutiplay_eventMutiplayerOnCreateSessionComplete_Parms
	{
		bool bWasSuccessful;
	};
	_Script_mutiplay_eventMutiplayerOnCreateSessionComplete_Parms Parms;
	Parms.bWasSuccessful=bWasSuccessful ? true : false;
	MutiplayerOnCreateSessionComplete.ProcessMulticastDelegate<UObject>(&Parms);
}
	struct Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics
	{
		struct _Script_mutiplay_eventMutiplayOnDestroySessionComplete_Parms
		{
			bool bWasSuccessful;
		};
		static void NewProp_bWasSuccessful_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bWasSuccessful;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful_SetBit(void* Obj)
	{
		((_Script_mutiplay_eventMutiplayOnDestroySessionComplete_Parms*)Obj)->bWasSuccessful = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful = { "bWasSuccessful", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(_Script_mutiplay_eventMutiplayOnDestroySessionComplete_Parms), &Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MutiplaySubsystem.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_mutiplay, nullptr, "MutiplayOnDestroySessionComplete__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::_Script_mutiplay_eventMutiplayOnDestroySessionComplete_Parms), Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FMutiplayOnDestroySessionComplete_DelegateWrapper(const FMulticastScriptDelegate& MutiplayOnDestroySessionComplete, bool bWasSuccessful)
{
	struct _Script_mutiplay_eventMutiplayOnDestroySessionComplete_Parms
	{
		bool bWasSuccessful;
	};
	_Script_mutiplay_eventMutiplayOnDestroySessionComplete_Parms Parms;
	Parms.bWasSuccessful=bWasSuccessful ? true : false;
	MutiplayOnDestroySessionComplete.ProcessMulticastDelegate<UObject>(&Parms);
}
	struct Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics
	{
		struct _Script_mutiplay_eventMutiplayOnStartSessionComplete_Parms
		{
			bool bWasSuccessful;
		};
		static void NewProp_bWasSuccessful_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bWasSuccessful;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful_SetBit(void* Obj)
	{
		((_Script_mutiplay_eventMutiplayOnStartSessionComplete_Parms*)Obj)->bWasSuccessful = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful = { "bWasSuccessful", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(_Script_mutiplay_eventMutiplayOnStartSessionComplete_Parms), &Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::NewProp_bWasSuccessful,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MutiplaySubsystem.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_mutiplay, nullptr, "MutiplayOnStartSessionComplete__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::_Script_mutiplay_eventMutiplayOnStartSessionComplete_Parms), Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FMutiplayOnStartSessionComplete_DelegateWrapper(const FMulticastScriptDelegate& MutiplayOnStartSessionComplete, bool bWasSuccessful)
{
	struct _Script_mutiplay_eventMutiplayOnStartSessionComplete_Parms
	{
		bool bWasSuccessful;
	};
	_Script_mutiplay_eventMutiplayOnStartSessionComplete_Parms Parms;
	Parms.bWasSuccessful=bWasSuccessful ? true : false;
	MutiplayOnStartSessionComplete.ProcessMulticastDelegate<UObject>(&Parms);
}
	void UMutiplaySubsystem::StaticRegisterNativesUMutiplaySubsystem()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMutiplaySubsystem);
	UClass* Z_Construct_UClass_UMutiplaySubsystem_NoRegister()
	{
		return UMutiplaySubsystem::StaticClass();
	}
	struct Z_Construct_UClass_UMutiplaySubsystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMutiplaySubsystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
		(UObject* (*)())Z_Construct_UPackage__Script_mutiplay,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMutiplaySubsystem_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "MutiplaySubsystem.h" },
		{ "ModuleRelativePath", "Public/MutiplaySubsystem.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMutiplaySubsystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMutiplaySubsystem>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UMutiplaySubsystem_Statics::ClassParams = {
		&UMutiplaySubsystem::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UMutiplaySubsystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMutiplaySubsystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMutiplaySubsystem()
	{
		if (!Z_Registration_Info_UClass_UMutiplaySubsystem.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMutiplaySubsystem.OuterSingleton, Z_Construct_UClass_UMutiplaySubsystem_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UMutiplaySubsystem.OuterSingleton;
	}
	template<> MUTIPLAY_API UClass* StaticClass<UMutiplaySubsystem>()
	{
		return UMutiplaySubsystem::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMutiplaySubsystem);
	UMutiplaySubsystem::~UMutiplaySubsystem() {}
	struct Z_CompiledInDeferFile_FID_ao_ao1_Plugins_mutiplay_Source_mutiplay_Public_MutiplaySubsystem_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ao_ao1_Plugins_mutiplay_Source_mutiplay_Public_MutiplaySubsystem_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UMutiplaySubsystem, UMutiplaySubsystem::StaticClass, TEXT("UMutiplaySubsystem"), &Z_Registration_Info_UClass_UMutiplaySubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMutiplaySubsystem), 4117947363U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ao_ao1_Plugins_mutiplay_Source_mutiplay_Public_MutiplaySubsystem_h_515635246(TEXT("/Script/mutiplay"),
		Z_CompiledInDeferFile_FID_ao_ao1_Plugins_mutiplay_Source_mutiplay_Public_MutiplaySubsystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ao_ao1_Plugins_mutiplay_Source_mutiplay_Public_MutiplaySubsystem_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
