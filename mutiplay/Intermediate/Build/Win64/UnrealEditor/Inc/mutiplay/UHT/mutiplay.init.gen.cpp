// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodemutiplay_init() {}
	MUTIPLAY_API UFunction* Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature();
	MUTIPLAY_API UFunction* Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature();
	MUTIPLAY_API UFunction* Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_mutiplay;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_mutiplay()
	{
		if (!Z_Registration_Info_UPackage__Script_mutiplay.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_mutiplay_MutiplayerOnCreateSessionComplete__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_mutiplay_MutiplayOnDestroySessionComplete__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_mutiplay_MutiplayOnStartSessionComplete__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/mutiplay",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x3C24984B,
				0x91DBB841,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_mutiplay.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_mutiplay.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_mutiplay(Z_Construct_UPackage__Script_mutiplay, TEXT("/Script/mutiplay"), Z_Registration_Info_UPackage__Script_mutiplay, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x3C24984B, 0x91DBB841));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
