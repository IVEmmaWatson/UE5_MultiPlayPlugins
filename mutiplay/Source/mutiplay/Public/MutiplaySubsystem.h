// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MutiplaySubsystem.generated.h"

//
// ����������������һ���ಥί�����ͣ���һ����class,����intһ���Ļ������ͣ�����ָ�����ί�����͵Ĳ����б�
// ��������������Ƕ�����ί�����͵�ǩ����Ҳ�������ί�����Ϳ��԰󶨺͵��õĺ����Ĳ������͡�
// ����һ����̬�ಥί�� ��ί�е����ƣ�ί�еĲ������ͣ����������ƣ�
// ��̬�ಥί�У���̬��������ͼ��ʹ�ã���ֻ̬����c++��ʹ�á�
// �ಥ��һ���������͵�ί�У�����һ��ί�ж�����������������
// const TArray<FOnlineSessionSearchResult>& SearchResults�����ṹ�嶯̬�����������Ϊ����
// ����Ự��ί����Ҫ���Ự�����Ϊ����
// ��̬�ಥί�а󶨵ĺ�������Ҫ��UFUNCTION����
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
	// ����Ự�ĺ����������򽫵��ù������ʵ���Щ����
	// 
	void CreateSession(int32 NumPubilcConnections, FString MatchType);
	void FindSessions(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SesssionResult);
	void DestroySession();
	void StartSession();

	//
	// ����һ���ಥί��ʵ����������Menu��ȥ����
	//
	FMutiplayerOnCreateSessionComplete MutiplayerOnCreateSessionComplete;
	FMutiplayerOnFindSessionComplete MutiplayerOnFindSessionComplete;
	FMutiplayerOnJoinSessionComplete MutiplayerOnJoinSessionComplete;
	FMutiplayOnDestroySessionComplete MutiplayOnDestroySessionComplete;
	FMutiplayOnStartSessionComplete MutiplayOnStartSessionComplete;
protected:
	//
	// �Ựί�а󶨵Ļص�����,����Ҫ������ȥ���û��߷���
	//
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
	// ����һ��ö�ٱ��������洢���ֵ
	void JoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
private:
	// ������һ��ָ�����߻Ự�ӿڵ�����ָ���������û��ָ���κζ���
	// ������һ��ָ�����߻Ự���õ�����ָ�����
	// ������һ��ָ�����߻ỰѰ�ҵ�����ָ�����
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
	// 
	// ���߻Ự�ӿ�ί���б�
	// ������FDelegateHandle �� Unreal Engine �����ڹ���Ͳ���ί�У�Delegate���ľ����
	// ������Ҫ�������ṩһ�ַ�ʽ�����úͲ����Ѿ��󶨵�ί�У��ر�������Ҫ������ί��״̬ʱ��
	// �����һ��ί��ʱ��ͨ���᷵��һ�� FDelegateHandle�������Ժ������ί�С�
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

	// ����һ������������������˳���Ϸ����������������Ϸʱ���Ͱ����ֵ����Ϊtrue,Ȼ�����
	// ���ٸղż���ĻỰ
	// ������ȷ��if (ExistingSession != nullptr)����Ự�ǿյġ�
	// ������ҵ�һ�δ����Ựʱ������϶��ǿյģ�����if (ExistingSession != nullptr)����Ĳ���ִ�У�bCreateSessionDestroyҲ��false
	bool bCreateSessionDestroy{ false };
	int32 LastNumPublicConnections;
	FString LastMatchType;
};
