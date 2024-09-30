// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "MutiplaySubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include <OnlineSubsystem.h>

void UMenu::MenuSetup(int32 NumOfPublicConnections, FString TypeOfMatch,FString LobbyPath)
{
	PathToLobby = FString::Printf(TEXT("%s?listen"), *LobbyPath);
	NumPubilcConnections = NumOfPublicConnections;
	MatchType = TypeOfMatch;
	// AddToViewport() �� UUserWidget ���һ����Ա���������ڽ��û����棨UI��С������ӵ���Ϸ���ӿ��С�
	AddToViewport();	
	// ����ui�����Ƿ�ɼ���������ö������
	SetVisibility(ESlateVisibility::Visible);
	// ���뽹�㣨��������¼��ȣ�
	bIsFocusable = true;

	// ��ȡ��ǰ�����ʵ�������ָ��
	UWorld* World = GetWorld();
	if (World)
	{
		// ��ȡ������ҵĿ�����
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			//
			// FInputModeUIOnly ��һ���ṹ�壬������������ģʽ��ʹ������������û����棨UI����
			// ������ģʽ�£���ҵ����뽫ֻӰ�� UI Ԫ�أ�������Ӱ����Ϸ�����е�����Ԫ�ء�
			//

			FInputModeUIOnly InputModeData;
			// �����л��������
			InputModeData.SetWidgetToFocus(TakeWidget());
			// ��������������ӿڵ���Ϊ��DoNotLock ��ʾ��겻�����������������ƶ����ӿ��⡣
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			// ��Ϊ�� C++ �У�������Ķ�����Ա����ݸ����ܻ������ĺ�����
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	// ��ȡһ��ָ����Ϸʵ����ָ��
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		// ��ȡģ����ϵͳʵ����ָ��
		MutiplaySubsystem=GameInstance->GetSubsystem<UMutiplaySubsystem>();
	}

	if (MutiplaySubsystem)
	{
		// ָ�������ϵͳ�Ķಥί�б���������AddDynamic����ȥ��һ���ص�������
		// ��ʵί�а󶨺���������Ҫָ������ʵ�����Լ�ָ����ĺ�������Ϊһ���಻һ��ֻ��һ������������Ҫָ��this��ǰ���󣬶��ຯ���ǹ����ģ�
		MutiplaySubsystem->MutiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MutiplaySubsystem->MutiplayerOnFindSessionComplete.AddUObject(this, &UMenu::OnFindSessions);
		MutiplaySubsystem->MutiplayerOnJoinSessionComplete.AddUObject(this, &UMenu::OnJoinSession);
		MutiplaySubsystem->MutiplayOnDestroySessionComplete.AddDynamic(this, &UMenu::OnDestroySession);
		MutiplaySubsystem->MutiplayOnStartSessionComplete.AddDynamic(this, &UMenu::OnStartSession);

	}
}


bool UMenu::Initialize()
{
	// ��ʼ����������Ҫ�ֶ����á������� Unreal Engine ���ض�������Զ����õģ�
	// �ر������û�С������UUserWidget���������ͳ�ʼ��ʱ��
	// ���� Super::Initialize() ��Ϊ��ȷ������ĳ�ʼ���߼���ִ�С���������� Super::Initialize()������ĳ�ʼ���߼�������ִ��
	if (!Super::Initialize())
	{
		return false;
	}

	// �����ǳ�ʼ���߼�
	// ��鰴ťָ���Ƿ���Ч������Ϊ nullptr��
	if (HostButton)
	{
		// �� HostButton �ĵ���¼��󶨵� UMenu ��� HostButtonClicked ����
		// AddDynamic(this, &UMenu::HostButtonClicked)��AddDynamic ��һ��ģ�庯�������ڽ���Ա�����󶨵�ί���ϡ�
		HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMenu::JoinButtonClicked);
	}
	return true;
}

// ��Ϸ������ؿ��л�ʱ������С����������ʱ,�Զ�����
void UMenu::NativeDestruct()
{
	// ɾ���϶���ɾ������ģ��ٵ��ø����ɾ��
	// ����ʼ���϶����ȳ�ʼ������ģ��ڳ�ʼ�������
	MenuTearDown();

	Super::NativeDestruct();
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString(TEXT("Session create successful"))
			);

			UWorld* World = GetWorld();
			if (World)
			{
				// ���Ǳ���������Ϸ����ҽ������������������ServerTravel�������������ͣ���Ϊ�����Լ���������
				World->ServerTravel(PathToLobby);
			}
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Session create failed"))
			);

			// �������ʧ�ܾ�������ʾ��ť
			HostButton->SetIsEnabled(true);
		}
	}
}

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionRestults, bool bWasSuccessful)
{
	if (MutiplaySubsystem == nullptr)
	{
		return;
	}

	

	for (auto Result : SessionRestults)
	{
		FString SettingValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingValue);
		if (SettingValue == MatchType)
		{
			MutiplaySubsystem->JoinSession(Result);
			return; 
		}
		
	}
	
	// ���Ѱ�һỰʧ�ܣ����������Ự���Ϊ0���ٴ���ʾ��ť
	if (!bWasSuccessful || SessionRestults.Num() == 0)
	{
		JoinButton->SetIsEnabled(true);
	}
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{

			FString Address;
			// ��ȡָ���Ự��ip��ַ�Ͷ˿ڣ���Ϊ�����Ự��ʱ�����˻Ự���ƺ�Ψһ����id�����Լ����ʱ���ȡ���ǶԷ���ip
			// �������ͬʱ�����ˣ��ǻ���ô���������أ������ûʵ��
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
		
	} 

	// �������Ựʧ��(�����Ƕ˿�ip��Ч��ԭ��)�����ٴ���ʾ��ť��
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		JoinButton->SetIsEnabled(true);
	}
	
}

void UMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMenu::OnStartSession(bool bWasSuccessful)
{
}



void UMenu::HostButtonClicked()
{
	
	// ��������ð�ť���ɼ�
	HostButton->SetIsEnabled(false);

	if (MutiplaySubsystem)
	{
		MutiplaySubsystem->CreateSession(NumPubilcConnections, MatchType);
		
	}
}

void UMenu::JoinButtonClicked()
{
	JoinButton->SetIsEnabled(false);

	if (MutiplaySubsystem)
	{
		MutiplaySubsystem->FindSessions(10000);
	}
}

void UMenu::MenuTearDown()
{
	// RemoveFromViewport�Ǵ��������Ƴ�����С�ؼ�
	// RemoveFromParent();�Ǵ���Ϸ�Ƴ�Viewport���ڽ���
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		FInputModeGameOnly InputModeData;
		PlayerController->SetInputMode(InputModeData);
		PlayerController->SetShowMouseCursor(false);
	}
}
