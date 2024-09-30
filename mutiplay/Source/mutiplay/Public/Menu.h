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

	// ���ػ���ĳ�ʼ�����������ں�����û���ĳ�ʼ������
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	//
	// ����󶨶�����ϵͳ�Ķಥί�� �õ��ĺ���
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
	// ���Ժ꣬����C++ ���������ͼ�ж����ͬ��������
	// ͨ����Ԫ��������ΪBindWidget������ͬ��С������c++��ͼ����
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
	// �����ϵͳģ�����������������߻Ự����
	class UMutiplaySubsystem* MutiplaySubsystem;

	// ʹ�ô����ų�ʼ������ NumPublicConnections ��ʼ��Ϊ 4��
	// ���ֳ�ʼ����ʽ��C++11�����߰汾�б����룬�ṩ��һ�ָ�ͳһ�Ͱ�ȫ�ĳ�ʼ����ʽ��
	int32 NumPubilcConnections{ 4 };
	FString MatchType = TEXT("FreeForAll");
	// FString MatchType{ TEXT("FreeForAll") };
	FString PathToLobby;
};
