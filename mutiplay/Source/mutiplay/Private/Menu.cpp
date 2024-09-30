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
	// AddToViewport() 是 UUserWidget 类的一个成员函数，用于将用户界面（UI）小部件添加到游戏的视口中。
	AddToViewport();	
	// 设置ui窗口是否可见，参数是枚举类型
	SetVisibility(ESlateVisibility::Visible);
	// 输入焦点（键盘鼠标事件等）
	bIsFocusable = true;

	// 获取当前世界的实例对象的指针
	UWorld* World = GetWorld();
	if (World)
	{
		// 获取本地玩家的控制器
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			//
			// FInputModeUIOnly 是一个结构体，用于设置输入模式，使得输入仅限于用户界面（UI）。
			// 在这种模式下，玩家的输入将只影响 UI 元素，而不会影响游戏世界中的其他元素。
			//

			FInputModeUIOnly InputModeData;
			// 焦点切换到输入框
			InputModeData.SetWidgetToFocus(TakeWidget());
			// 设置鼠标锁定到视口的行为。DoNotLock 表示鼠标不被锁定，可以自由移动到视口外。
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			// 因为在 C++ 中，派生类的对象可以被传递给接受基类对象的函数。
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	// 获取一个指向游戏实例的指针
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		// 获取模块子系统实例的指针
		MutiplaySubsystem=GameInstance->GetSubsystem<UMutiplaySubsystem>();
	}

	if (MutiplaySubsystem)
	{
		// 指针访问子系统的多播委托变量，调用AddDynamic函数去绑定一个回调函数，
		// 其实委托绑定函数就是需要指定对象实例，以及指定类的函数（因为一个类不一定只有一个对象，所以需要指定this当前对象，而类函数是公共的）
		MutiplaySubsystem->MutiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MutiplaySubsystem->MutiplayerOnFindSessionComplete.AddUObject(this, &UMenu::OnFindSessions);
		MutiplaySubsystem->MutiplayerOnJoinSessionComplete.AddUObject(this, &UMenu::OnJoinSession);
		MutiplaySubsystem->MutiplayOnDestroySessionComplete.AddDynamic(this, &UMenu::OnDestroySession);
		MutiplaySubsystem->MutiplayOnStartSessionComplete.AddDynamic(this, &UMenu::OnStartSession);

	}
}


bool UMenu::Initialize()
{
	// 初始化函数不需要手动调用。它是由 Unreal Engine 在特定情况下自动调用的，
	// 特别是在用户小部件（UUserWidget）被构建和初始化时。
	// 调用 Super::Initialize() 是为了确保基类的初始化逻辑被执行。如果不调用 Super::Initialize()，基类的初始化逻辑将不会执行
	if (!Super::Initialize())
	{
		return false;
	}

	// 下面是初始化逻辑
	// 检查按钮指针是否有效（即不为 nullptr）
	if (HostButton)
	{
		// 将 HostButton 的点击事件绑定到 UMenu 类的 HostButtonClicked 函数
		// AddDynamic(this, &UMenu::HostButtonClicked)：AddDynamic 是一个模板函数，用于将成员函数绑定到委托上。
		HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMenu::JoinButtonClicked);
	}
	return true;
}

// 游戏结束或关卡切换时，所有小部件被销毁时,自动调用
void UMenu::NativeDestruct()
{
	// 删除肯定先删除子类的，再调用父类的删除
	// 而初始化肯定是先初始化父类的，在初始化子类的
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
				// 这是本地主持游戏的玩家进入大厅场景，所以用ServerTravel，即服务器传送，因为这是自己当服务器
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

			// 如果创建失败就设置显示按钮
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
	
	// 如果寻找会话失败，或者找完后会话结果为0就再次显示按钮
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
			// 获取指定会话的ip地址和端口，因为创建会话的时候填了会话名称和唯一网络id，所以加入的时候获取的是对方的ip
			// 如果多人同时创建了，那会怎么触发加入呢，这个还没实现
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
		
	} 

	// 如果加入会话失败(可能是端口ip无效等原因)，就再次显示按钮，
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
	
	// 点击后设置按钮不可见
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
	// RemoveFromViewport是从主界面移除其他小控件
	// RemoveFromParent();是从游戏移除Viewport窗口界面
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
