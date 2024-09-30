// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"


#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MUTIPLAY_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumOfPublicConnections=4,FString TypeOfMatch=TEXT("FreeForAll"),FString LobbyPath=FString(TEXT("/Game/ThirdPerson/Maps/Lobby")));

protected:

	// 重载基类的初始化函数，并在后面调用基类的初始化函数
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	//
	// 定义绑定多人子系统的多播委托 用到的函数
	//
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionRestults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
private:
	// 属性宏，允许C++ 代码访问蓝图中定义的同名变量。
	// 通过将元属性设置为BindWidget，创建同名小部件的c++蓝图子类
	UPROPERTY(meta = (BindWidget));
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget));
	UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();
	UFUNCTION()
	void MenuTearDown();
	// 这个子系统模块用来处理所有在线会话函数
	class UMutiplaySubsystem* MutiplaySubsystem;

	// 使用大括号初始化器将 NumPublicConnections 初始化为 4。
	// 这种初始化方式在C++11及更高版本中被引入，提供了一种更统一和安全的初始化方式。
	int32 NumPubilcConnections{ 4 };
	FString MatchType = TEXT("FreeForAll");
	// FString MatchType{ TEXT("FreeForAll") };
	FString PathToLobby;
};
