// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MutiplaySubsystem.generated.h"

//
// 这个宏的作用是声明一个多播委托类型（是一个类class,类似int一样的基础类型），并指定这个委托类型的参数列表
// 这个参数的意义是定义了委托类型的签名，也就是这个委托类型可以绑定和调用的函数的参数类型。
// 声明一个动态多播委托 （委托的名称，委托的参数类型，参数的名称）
// 静态多播委托，动态可以在蓝图中使用，静态只能在c++中使用。
// 多播是一种特殊类型的委托，允许一个委托对象包含多个方法函数
// const TArray<FOnlineSessionSearchResult>& SearchResults常量结构体动态数组的引用作为参数
// 加入会话的委托需要个会话结果作为参数
// 动态多播委托绑定的函数，需要用UFUNCTION宏标记
//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMutiplayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMutiplayerOnFindSessionComplete, const TArray<FOnlineSessionSearchResult>& SearchResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMutiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMutiplayOnDestroySessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMutiplayOnStartSessionComplete, bool, bWasSuccessful);







/**
 * 
 */
UCLASS()
class MUTIPLAY_API UMutiplaySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UMutiplaySubsystem();
	// 
	// 处理会话的函数，主程序将调用公共访问的这些函数
	// 
	void CreateSession(int32 NumPubilcConnections, FString MatchType);
	void FindSessions(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SesssionResult);
	void DestroySession();
	void StartSession();

	//
	// 创建一个多播委托实例对象，用于Menu类去调用
	//
	FMutiplayerOnCreateSessionComplete MutiplayerOnCreateSessionComplete;
	FMutiplayerOnFindSessionComplete MutiplayerOnFindSessionComplete;
	FMutiplayerOnJoinSessionComplete MutiplayerOnJoinSessionComplete;
	FMutiplayOnDestroySessionComplete MutiplayOnDestroySessionComplete;
	FMutiplayOnStartSessionComplete MutiplayOnStartSessionComplete;
protected:
	//
	// 会话委托绑定的回调函数,不需要在类外去调用或者访问
	//
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
	// 定义一个枚举变量用来存储结果值
	void JoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
private:
	// 声明了一个指向在线会话接口的智能指针变量，还没有指向任何对象
	// 声明了一个指向在线会话设置的智能指针变量
	// 声明了一个指向在线会话寻找的智能指针变量
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
	// 
	// 在线会话接口委托列表
	// 并创建FDelegateHandle 是 Unreal Engine 中用于管理和操作委托（Delegate）的句柄。
	// 它的主要作用是提供一种方式来引用和操作已经绑定的委托，特别是在需要解绑或检查委托状态时。
	// 当你绑定一个委托时，通常会返回一个 FDelegateHandle，用于以后操作该委托。
	//
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FOnFindSessionsCompleteDelegate FindSessionCompleteDelegate;
	FDelegateHandle FindSessionCompleteDelegateHandle;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	FOnDestroySessionCompleteDelegate DestroySessionDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	// 设置一个布尔变量，当玩家退出游戏，又想立即创建游戏时，就把这个值设置为true,然后调用
	// 销毁刚才加入的会话
	// 这样就确保if (ExistingSession != nullptr)这个会话是空的。
	// 而当玩家第一次创建会话时，这个肯定是空的，所有if (ExistingSession != nullptr)里面的不会执行，bCreateSessionDestroy也是false
	bool bCreateSessionDestroy{ false };
	int32 LastNumPublicConnections;
	FString LastMatchType;
};
