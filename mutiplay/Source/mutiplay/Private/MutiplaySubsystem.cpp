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
	// 获取/创建一个在线子系统的指针变量
	// 检查指针是否有效
	// 调用子系统函数去获取一个在线会话接口，得到的是一个智能指针对象
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

	// 判断这个会话是否已经存在
	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		// 存在就调用销毁，但是销毁前要把这个创建会话的参数存下来
		// 因为等会这个销毁会话的委托要回调这个创建会话函数，所以需要保存参数
		bCreateSessionDestroy = true;
		LastNumPublicConnections = NumPubilcConnections;
		LastMatchType = MatchType;

		DestroySession();
		// SessionInterface->DestroySession(NAME_GameSession);
	}

	CreateSessionCompleteDelegateHandle=SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
	LastSessionSettings = MakeShareable(new FOnlineSessionSettings);
	// 通过调用在线子系统函数查找子系统名称，如果为null就true表示仅置为局域网。否则设置为不仅局域网
	LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	LastSessionSettings->NumPublicConnections = NumPubilcConnections;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->bUseLobbiesIfAvailable = true;
	LastSessionSettings->BuildUniqueId = 1;
	// 设置会话的匹配类型为FreeForAll，也就是说等会找会话的时候，只有当这个MatchType值等于FreeForAll时，才会把玩家匹配到一起，参数3使其他玩家可以通过在线服务和Ping找到这个会话
	LastSessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	// 获取本地玩家指针，这个主要是管理玩家的网络ID和设置
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// 创建会话，本地玩家网络ID，会话名称，会话设置，如果创建失败就清楚委托
	// 当你加入游戏后就说明这个会话存在了，然后你退出游戏并没有去销毁这个会话，所以当你主持游戏时
	// 才会去调用到销毁会话，SessionInterface->DestroySession(NAME_GameSession);，而销毁会话需要时间去响应，所以如果你
	// 立即去点击创建游戏就会报错，因为你在创建一个已经存在的会话
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

		// 广播自定义的委托,因为创建会话失败，所以参数是false
		MutiplayerOnCreateSessionComplete.Broadcast(false);
	}


}

// 寻找会话
void UMutiplaySubsystem::FindSessions(int32 MaxSearchResults)
{
	// 先确定在线会话接口是否有效
	if (!SessionInterface.IsValid())
	{
		return;
	}

	// 将委托绑定到会话接口触发事件<寻找会话>上
	FindSessionCompleteDelegateHandle=SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);

	// 创建一个寻找会话类的实例,new FOnlineSessionSearch是创建一个普通指针变量，而MakeShareable是把普通指针变量转换成智能指针变量
	LastSessionSearch = MakeShareable(new FOnlineSessionSearch);
	LastSessionSearch->MaxSearchResults = MaxSearchResults;
	LastSessionSearch->bIsLanQuery= IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	LastSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// 参数1本地玩家的唯一网络id,参数2会话设置实例智能引用，tsharedref和tsharedptr不一样
	if (!SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef()))
	{
		SessionInterface->ClearOnCancelFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegateHandle);

		MutiplayerOnFindSessionComplete.Broadcast(TArray<FOnlineSessionSearchResult>(), false);

		
	}

	

}

void UMutiplaySubsystem::JoinSession(const FOnlineSessionSearchResult& SesssionResult)
{
	// 检查会话接口指针
	if (!SessionInterface.IsValid())
	{
		MutiplayerOnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
		return;
	}

	// 将委托绑定到会话接口处理并赋值给变量
	JoinSessionCompleteDelegateHandle=SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// 加入会话，如果失败则清除委托，并广播失败委托
	if (!SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SesssionResult))
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);

		MutiplayerOnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);

		
	}



}

void UMutiplaySubsystem::DestroySession()
{
	// 如果在线会话接口失效
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

// 创建会话成功后委托调用的回调函数
void UMutiplaySubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	// 清除委托
	if (SessionInterface)
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}


	// 调用广播委托,说创建会话成功
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
				FString(TEXT("SearchResult Num 小于0"))
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
