// Fill out your copyright notice in the Description page of Project Settings.


#include "MutiplaySubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UMutiplaySubsystem::UMutiplaySubsystem():
	CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this,&UMutiplaySubsystem::OnCreateSessionComplete)),
	FindSessionCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this,&UMutiplaySubsystem::OnFindSessionComplete)),
	JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this,&UMutiplaySubsystem::JoinSessionComplete)),
	DestroySessionDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this,&UMutiplaySubsystem::OnDestroySessionComplete)),
	StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this,&UMutiplaySubsystem::OnStartSessionComplete))

{
	// 
	// ��ȡ/����һ��������ϵͳ��ָ�����
	// ���ָ���Ƿ���Ч
	// ������ϵͳ����ȥ��ȡһ�����߻Ự�ӿڣ��õ�����һ������ָ�����
	//
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
}

void UMutiplaySubsystem::CreateSession(int32 NumPubilcConnections, FString MatchType)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}

	// �ж�����Ự�Ƿ��Ѿ�����
	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		// ���ھ͵������٣���������ǰҪ����������Ự�Ĳ���������
		// ��Ϊ�Ȼ�������ٻỰ��ί��Ҫ�ص���������Ự������������Ҫ�������
		bCreateSessionDestroy = true;
		LastNumPublicConnections = NumPubilcConnections;
		LastMatchType = MatchType;

		DestroySession();
		// SessionInterface->DestroySession(NAME_GameSession);
	}

	CreateSessionCompleteDelegateHandle=SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
	LastSessionSettings = MakeShareable(new FOnlineSessionSettings);
	// ͨ������������ϵͳ����������ϵͳ���ƣ����Ϊnull��true��ʾ����Ϊ����������������Ϊ����������
	LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	LastSessionSettings->NumPublicConnections = NumPubilcConnections;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->bUseLobbiesIfAvailable = true;
	LastSessionSettings->BuildUniqueId = 1;
	// ���ûỰ��ƥ������ΪFreeForAll��Ҳ����˵�Ȼ��һỰ��ʱ��ֻ�е����MatchTypeֵ����FreeForAllʱ���Ż�����ƥ�䵽һ�𣬲���3ʹ������ҿ���ͨ�����߷����Ping�ҵ�����Ự
	LastSessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	// ��ȡ�������ָ�룬�����Ҫ�ǹ�����ҵ�����ID������
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// �����Ự�������������ID���Ự���ƣ��Ự���ã��������ʧ�ܾ����ί��
	// ���������Ϸ���˵������Ự�����ˣ�Ȼ�����˳���Ϸ��û��ȥ��������Ự�����Ե���������Ϸʱ
	// �Ż�ȥ���õ����ٻỰ��SessionInterface->DestroySession(NAME_GameSession);�������ٻỰ��Ҫʱ��ȥ��Ӧ�����������
	// ����ȥ���������Ϸ�ͻᱨ����Ϊ���ڴ���һ���Ѿ����ڵĻỰ
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

		// �㲥�Զ����ί��,��Ϊ�����Ựʧ�ܣ����Բ�����false
		MutiplayerOnCreateSessionComplete.Broadcast(false);
	}


}

// Ѱ�һỰ
void UMutiplaySubsystem::FindSessions(int32 MaxSearchResults)
{
	// ��ȷ�����߻Ự�ӿ��Ƿ���Ч
	if (!SessionInterface.IsValid())
	{
		return;
	}

	// ��ί�а󶨵��Ự�ӿڴ����¼�<Ѱ�һỰ>��
	FindSessionCompleteDelegateHandle=SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);

	// ����һ��Ѱ�һỰ���ʵ��,new FOnlineSessionSearch�Ǵ���һ����ָͨ���������MakeShareable�ǰ���ָͨ�����ת��������ָ�����
	LastSessionSearch = MakeShareable(new FOnlineSessionSearch);
	LastSessionSearch->MaxSearchResults = MaxSearchResults;
	LastSessionSearch->bIsLanQuery= IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	LastSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// ����1������ҵ�Ψһ����id,����2�Ự����ʵ���������ã�tsharedref��tsharedptr��һ��
	if (!SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef()))
	{
		SessionInterface->ClearOnCancelFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegateHandle);

		MutiplayerOnFindSessionComplete.Broadcast(TArray<FOnlineSessionSearchResult>(), false);

		
	}

	

}

void UMutiplaySubsystem::JoinSession(const FOnlineSessionSearchResult& SesssionResult)
{
	// ���Ự�ӿ�ָ��
	if (!SessionInterface.IsValid())
	{
		MutiplayerOnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
		return;
	}

	// ��ί�а󶨵��Ự�ӿڴ�����ֵ������
	JoinSessionCompleteDelegateHandle=SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// ����Ự�����ʧ�������ί�У����㲥ʧ��ί��
	if (!SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SesssionResult))
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);

		MutiplayerOnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);

		
	}



}

void UMutiplaySubsystem::DestroySession()
{
	// ������߻Ự�ӿ�ʧЧ
	if (!SessionInterface.IsValid())
	{
		MutiplayOnDestroySessionComplete.Broadcast(false);
		return;
	}

	DestroySessionCompleteDelegateHandle =SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegate);

	if (!SessionInterface->DestroySession(NAME_GameSession))
	{
		MutiplayOnDestroySessionComplete.Broadcast(false);
		return;
	}
}

void UMutiplaySubsystem::StartSession()
{
}

// �����Ự�ɹ���ί�е��õĻص�����
void UMutiplaySubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	// ���ί��
	if (SessionInterface)
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}


	// ���ù㲥ί��,˵�����Ự�ɹ�
	MutiplayerOnCreateSessionComplete.Broadcast(bWasSuccessful);
}

void UMutiplaySubsystem::OnFindSessionComplete(bool bWasSuccessful)
{
	if (SessionInterface)
	{
		
		SessionInterface->ClearOnCancelFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegateHandle);
	}

	if (LastSessionSearch->SearchResults.Num() <= 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString(TEXT("SearchResult Num С��0"))
			);
		}

		MutiplayerOnFindSessionComplete.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
		return;
	}

	

	MutiplayerOnFindSessionComplete.Broadcast(LastSessionSearch->SearchResults, bWasSuccessful);
}

void UMutiplaySubsystem::JoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
	}

	

	MutiplayerOnJoinSessionComplete.Broadcast(Result);
}

void UMutiplaySubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
	}

	if (bWasSuccessful && bCreateSessionDestroy)
	{
		bCreateSessionDestroy = false;
		CreateSession(LastNumPublicConnections, LastMatchType);
	}
	
	MutiplayOnDestroySessionComplete.Broadcast(bWasSuccessful);
}

void UMutiplaySubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
}
