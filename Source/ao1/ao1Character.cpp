// Copyright Epic Games, Inc. All Rights Reserved.

#include "ao1Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <OnlineSubsystem.h>
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"



//////////////////////////////////////////////////////////////////////////
// Aao1Character

// 构造函数后面加：是用来初始化变量的，初始化列表中的成员变量会在构造函数体执行之前被初始化。
Aao1Character::Aao1Character() :
	// 委托变量初始化，构造函数可以初始化任意成员变量
	// 调用静态类方法createubject，参数1对象的实例，作用是指定委托函数所属的对象实例。
	// 具体来说，CreateUObject 方法需要知道哪个对象的成员函数将被调用。this表示当前对象实例的指针
	// 参数2指向成员函数的指针，即回调函数的指针
	CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &Aao1Character::OnCreateSessionComplete)),
	FindSessionCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this,&Aao1Character::OnFindSessionsComplete)),
	JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this,&Aao1Character::OnJoinSessionComplete))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// IOnlineSubsystem::Get()静态类方法获取在线子系统的实例，返回一个指向IOnlineSubsystem的指针
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		// 调用在线子系统的 GetSessionInterface() 方法以获取会话管理接口
		// onlinesessioninterface: 这个变量用于管理和访问游戏会话（如创建、加入和管理在线游戏会话）。
		onlinesessioninterface = OnlineSubsystem->GetSessionInterface();

		/*
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,	// 表示创建新消息，ID是随机分配的，也可以指定ID
				15.f,	// .f 表示这个数字是一个单精度浮点数（float）写成 15.0 或 15.f 都表示浮点数，后者更明确地表明这是一个 float 类型，而不是 double。
				FColor::Blue,
				// GetSubsystemName() 返回的是一个 FName 类型，而 Printf 期望接收一个 const TCHAR* 类型的字符串作为 %s 的参数。
				// ToString()将 FName 类型转换成FString类型，* 运算符用于获取 FString 的字符指针，这是必要的，因为 Printf 需要一个字符串指针作为参数。
				FString::Printf(TEXT("found subsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString())
			);
		}
		*/
	}
}

void Aao1Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// 创建会话
void Aao1Character::CreateGameSession()
{
	// 检查会话接口指针是否有效
	if (!onlinesessioninterface.IsValid())
	{
		return;
	}

	// 从在线会话接口中查找名为 NAME_GameSession 的会话，如果找到，则将其存储在 ExistingSession 中，供后续使用。
	auto ExistingSession=onlinesessioninterface->GetNamedSession(NAME_GameSession);

	if (ExistingSession != nullptr)
	{
		onlinesessioninterface->DestroySession(NAME_GameSession);
	}

	// 将委托绑定到会话接口，调用方法将创建会话的委托绑定
	onlinesessioninterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	// 表示指向FOnlineSessionSettings类的智能指针，因为包含了头文件，所以不需要指定class关键字
	// FOnlineSessionSettings() 表示调用 FOnlineSessionSettings 类的默认构造函数。构造函数用于初始化类的对象。
	// new运算符建立一个类的对象时，比如说类A的对象，new首先分配足以保证该类的一个对象所需要的内存，然后自动调用
	// 构造函数来初始化这块内存，再返回这个对象的地址。new”可以用来在堆上创建数组或对象
	// MakeShareable创建智能指针: 将原始指针（例如通过 new 创建的对象指针）转换为 TSharedPtr，使得该对象可以被多个智能指针共享。
	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());

	SessionSettings->bIsLANMatch = false;	// 局域网游戏
	SessionSettings->NumPublicConnections = 4;	// 游戏最大玩家
	SessionSettings->bAllowJoinInProgress = true;	// 允许玩家游戏进行中加入
	SessionSettings->bAllowJoinViaPresence = true;	// 允许通过好友或在线状态加入
	SessionSettings->bShouldAdvertise = true;	// 是否向其他玩家公开会话
	SessionSettings->bUsesPresence = true;	// 会话是否使用在线状态系统
	SessionSettings->bUseLobbiesIfAvailable = true;
	SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	// 从当前游戏世界中获取第一个本地玩家的指针,const意味着你不能通过 LocalPlayer 修改其指向的对象内容。
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// 利用会话接口创建会话，参数1是唯一网络ID，参数2是会话名称，参数3是会话设置对象（本来是智能指针，解引用就是类对象实例）
	onlinesessioninterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
}

// 加入会话
void Aao1Character::JoinGameSession()
{
	if (!onlinesessioninterface.IsValid())
	{
		return;
	}

	// 绑定寻找会话委托，如果会话搜索操作失败了，绑定的委托仍然会被触发
	// 这里函数需要一个参数是常量引用类型。只需要传递一个变量或者常量就行
	onlinesessioninterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);


	// 寻找会话
	// 创建了一个指向FOnlineSessionSearch类的对象的智能指针变量
	// TSharedPtr<FOnlineSessionSearch> onlinesessionsearch = MakeShareable(new FOnlineSessionSearch);
	// 这里这样写是因为变量作用域，如果写在这个函数里，那下面的回调函数就无法获取信息，所以把声明写在了头文件里
	onlinesessionsearch = MakeShareable(new FOnlineSessionSearch);
	
	

	onlinesessionsearch->MaxSearchResults = 10000;	// 设置搜索结果的最大数量
	onlinesessionsearch->bIsLanQuery = false;	// 设置搜索范围不局限于局域网
	// 设置会话搜索的查询参数，参数12是键值对，搜索所有在线状态的会话，值为true,参数3是比较操作符用于指定如何比较查询参数的值，例如 EOnlineComparisonOp::Equals。
	onlinesessionsearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// 利用会话接口寻找会话，参数1本地网络id,常量引用参数，参数2共享引用参数，所以把共享指针调用了方法转换成了共享引用
	// 开始搜索会话，搜索完成后调用回调函数
	onlinesessioninterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), onlinesessionsearch.ToSharedRef());
}

// 创建会话委托完成后的回调函数
void Aao1Character::OnCreateSessionComplete(FName SessionName, bool bwaSuccessful)
{
	if (bwaSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Blue,
				// *SessionName.ToString() 用于获取 FString 对象的底层 TCHAR 字符串指针，这样 FString::Printf 才能正确地格式化字符串。
				// printf需要获取tchar类型的字符串指针
				FString::Printf(TEXT("create session %s successful!"), *SessionName.ToString())
			);
		}
		// 获取当前世界的指针，允许访问和操作游戏中各种对象和环境
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(FString("/Game/ThirdPerson/Maps/Lobby?listen"));
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
				// 这里调用了fstring的构造函数，并传了字符串参数，text是宏定义将普通的字符串文字转换为宽字符（wchar_t）字符串
				FString(TEXT("failed to create session!"))
			);
		}
	}
}

// 加入会话的回调函数
void Aao1Character::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (!onlinesessioninterface.IsValid())
	{
		return;
	}
	// SearchResults成员变量是一个动态数组，存储了所有找到的会话结果
	// auto 自动匹配类型
	for (auto Result : onlinesessionsearch->SearchResults)
	{
		FString Id = Result.GetSessionIdStr();
		FString User = Result.Session.OwningUserName;
		FString MatchType;
		Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Cyan,
				FString::Printf(TEXT("Id: %s, User: %s"), *Id, *User)
			);
		}
		if (MatchType == FString("FreeForAll"))
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					15.f,
					FColor::Cyan,
					FString::Printf(TEXT("joining match type: %s"), *MatchType)
				);
			}

			// 绑定加入会话后的委托
			onlinesessioninterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

			// 获取本地玩家指针
			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			// 参数2是会话名称，在多人游戏中，可能存在多个不同类型的会话（例如，快速匹配、排位赛、私人房间等）。
			// 通过 SessionName，你可以明确指定要加入的会话类型。参数3是要加入会话的id配置等信息结果
			onlinesessioninterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
		}
	}
}

// 加入会话后调用的回调函数（因为加入会话不意味着加入游戏）
void Aao1Character::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!onlinesessioninterface.IsValid())
	{
		return;
	}
	FString Address;
	// 这个函数表示从在线会话接口中获取指定会话的信息（IP和端口等），参数1指定的会话名称，参数2存储ip和端口的变量
	if (onlinesessioninterface->GetResolvedConnectString(NAME_GameSession, Address))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString::Printf(TEXT("connect string %s"), *Address)
			);
		}
		// 获取本地玩家控制器，这个主要用于处理玩家输入和控制角色，而ULocalPlayer：表示本地玩家，管理玩家的网络ID和设置等信息
		// UGameInstance游戏实例管理游戏的全局状态和数据
		APlayerController* PlayContorller = GetGameInstance()->GetFirstLocalPlayerController();
		// 参数1目标服务器的地址，通常包含IP地址和端口，参数2旅行类型。在这里，TRAVEL_Absolute 表示绝对路径旅行
		if (PlayContorller)
		{
			PlayContorller->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
		
	}

	
}

//////////////////////////////////////////////////////////////////////////
// Input

void Aao1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &Aao1Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &Aao1Character::Look);

	}

}

void Aao1Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void Aao1Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




