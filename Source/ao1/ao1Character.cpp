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

// ���캯������ӣ���������ʼ�������ģ���ʼ���б��еĳ�Ա�������ڹ��캯����ִ��֮ǰ����ʼ����
Aao1Character::Aao1Character() :
	// ί�б�����ʼ�������캯�����Գ�ʼ�������Ա����
	// ���þ�̬�෽��createubject������1�����ʵ����������ָ��ί�к��������Ķ���ʵ����
	// ������˵��CreateUObject ������Ҫ֪���ĸ�����ĳ�Ա�����������á�this��ʾ��ǰ����ʵ����ָ��
	// ����2ָ���Ա������ָ�룬���ص�������ָ��
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

	// IOnlineSubsystem::Get()��̬�෽����ȡ������ϵͳ��ʵ��������һ��ָ��IOnlineSubsystem��ָ��
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		// ����������ϵͳ�� GetSessionInterface() �����Ի�ȡ�Ự����ӿ�
		// onlinesessioninterface: ����������ڹ���ͷ�����Ϸ�Ự���紴��������͹���������Ϸ�Ự����
		onlinesessioninterface = OnlineSubsystem->GetSessionInterface();

		/*
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,	// ��ʾ��������Ϣ��ID���������ģ�Ҳ����ָ��ID
				15.f,	// .f ��ʾ���������һ�������ȸ�������float��д�� 15.0 �� 15.f ����ʾ�����������߸���ȷ�ر�������һ�� float ���ͣ������� double��
				FColor::Blue,
				// GetSubsystemName() ���ص���һ�� FName ���ͣ��� Printf ��������һ�� const TCHAR* ���͵��ַ�����Ϊ %s �Ĳ�����
				// ToString()�� FName ����ת����FString���ͣ�* ��������ڻ�ȡ FString ���ַ�ָ�룬���Ǳ�Ҫ�ģ���Ϊ Printf ��Ҫһ���ַ���ָ����Ϊ������
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

// �����Ự
void Aao1Character::CreateGameSession()
{
	// ���Ự�ӿ�ָ���Ƿ���Ч
	if (!onlinesessioninterface.IsValid())
	{
		return;
	}

	// �����߻Ự�ӿ��в�����Ϊ NAME_GameSession �ĻỰ������ҵ�������洢�� ExistingSession �У�������ʹ�á�
	auto ExistingSession=onlinesessioninterface->GetNamedSession(NAME_GameSession);

	if (ExistingSession != nullptr)
	{
		onlinesessioninterface->DestroySession(NAME_GameSession);
	}

	// ��ί�а󶨵��Ự�ӿڣ����÷����������Ự��ί�а�
	onlinesessioninterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	// ��ʾָ��FOnlineSessionSettings�������ָ�룬��Ϊ������ͷ�ļ������Բ���Ҫָ��class�ؼ���
	// FOnlineSessionSettings() ��ʾ���� FOnlineSessionSettings ���Ĭ�Ϲ��캯�������캯�����ڳ�ʼ����Ķ���
	// new���������һ����Ķ���ʱ������˵��A�Ķ���new���ȷ������Ա�֤�����һ����������Ҫ���ڴ棬Ȼ���Զ�����
	// ���캯������ʼ������ڴ棬�ٷ����������ĵ�ַ��new�����������ڶ��ϴ�����������
	// MakeShareable��������ָ��: ��ԭʼָ�루����ͨ�� new �����Ķ���ָ�룩ת��Ϊ TSharedPtr��ʹ�øö�����Ա��������ָ�빲��
	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());

	SessionSettings->bIsLANMatch = false;	// ��������Ϸ
	SessionSettings->NumPublicConnections = 4;	// ��Ϸ������
	SessionSettings->bAllowJoinInProgress = true;	// ���������Ϸ�����м���
	SessionSettings->bAllowJoinViaPresence = true;	// ����ͨ�����ѻ�����״̬����
	SessionSettings->bShouldAdvertise = true;	// �Ƿ���������ҹ����Ự
	SessionSettings->bUsesPresence = true;	// �Ự�Ƿ�ʹ������״̬ϵͳ
	SessionSettings->bUseLobbiesIfAvailable = true;
	SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	// �ӵ�ǰ��Ϸ�����л�ȡ��һ��������ҵ�ָ��,const��ζ���㲻��ͨ�� LocalPlayer �޸���ָ��Ķ������ݡ�
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// ���ûỰ�ӿڴ����Ự������1��Ψһ����ID������2�ǻỰ���ƣ�����3�ǻỰ���ö��󣨱���������ָ�룬�����þ��������ʵ����
	onlinesessioninterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
}

// ����Ự
void Aao1Character::JoinGameSession()
{
	if (!onlinesessioninterface.IsValid())
	{
		return;
	}

	// ��Ѱ�һỰί�У�����Ự��������ʧ���ˣ��󶨵�ί����Ȼ�ᱻ����
	// ���ﺯ����Ҫһ�������ǳ����������͡�ֻ��Ҫ����һ���������߳�������
	onlinesessioninterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);


	// Ѱ�һỰ
	// ������һ��ָ��FOnlineSessionSearch��Ķ��������ָ�����
	// TSharedPtr<FOnlineSessionSearch> onlinesessionsearch = MakeShareable(new FOnlineSessionSearch);
	// ��������д����Ϊ�������������д����������������Ļص��������޷���ȡ��Ϣ�����԰�����д����ͷ�ļ���
	onlinesessionsearch = MakeShareable(new FOnlineSessionSearch);
	
	

	onlinesessionsearch->MaxSearchResults = 10000;	// ��������������������
	onlinesessionsearch->bIsLanQuery = false;	// ����������Χ�������ھ�����
	// ���ûỰ�����Ĳ�ѯ����������12�Ǽ�ֵ�ԣ�������������״̬�ĻỰ��ֵΪtrue,����3�ǱȽϲ���������ָ����αȽϲ�ѯ������ֵ������ EOnlineComparisonOp::Equals��
	onlinesessionsearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// ���ûỰ�ӿ�Ѱ�һỰ������1��������id,�������ò���������2�������ò��������԰ѹ���ָ������˷���ת�����˹�������
	// ��ʼ�����Ự��������ɺ���ûص�����
	onlinesessioninterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), onlinesessionsearch.ToSharedRef());
}

// �����Ựί����ɺ�Ļص�����
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
				// *SessionName.ToString() ���ڻ�ȡ FString ����ĵײ� TCHAR �ַ���ָ�룬���� FString::Printf ������ȷ�ظ�ʽ���ַ�����
				// printf��Ҫ��ȡtchar���͵��ַ���ָ��
				FString::Printf(TEXT("create session %s successful!"), *SessionName.ToString())
			);
		}
		// ��ȡ��ǰ�����ָ�룬������ʺͲ�����Ϸ�и��ֶ���ͻ���
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
				// ���������fstring�Ĺ��캯�����������ַ���������text�Ǻ궨�彫��ͨ���ַ�������ת��Ϊ���ַ���wchar_t���ַ���
				FString(TEXT("failed to create session!"))
			);
		}
	}
}

// ����Ự�Ļص�����
void Aao1Character::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (!onlinesessioninterface.IsValid())
	{
		return;
	}
	// SearchResults��Ա������һ����̬���飬�洢�������ҵ��ĻỰ���
	// auto �Զ�ƥ������
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

			// �󶨼���Ự���ί��
			onlinesessioninterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

			// ��ȡ�������ָ��
			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			// ����2�ǻỰ���ƣ��ڶ�����Ϸ�У����ܴ��ڶ����ͬ���͵ĻỰ�����磬����ƥ�䡢��λ����˽�˷���ȣ���
			// ͨ�� SessionName���������ȷָ��Ҫ����ĻỰ���͡�����3��Ҫ����Ự��id���õ���Ϣ���
			onlinesessioninterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
		}
	}
}

// ����Ự����õĻص���������Ϊ����Ự����ζ�ż�����Ϸ��
void Aao1Character::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!onlinesessioninterface.IsValid())
	{
		return;
	}
	FString Address;
	// ���������ʾ�����߻Ự�ӿ��л�ȡָ���Ự����Ϣ��IP�Ͷ˿ڵȣ�������1ָ���ĻỰ���ƣ�����2�洢ip�Ͷ˿ڵı���
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
		// ��ȡ������ҿ������������Ҫ���ڴ����������Ϳ��ƽ�ɫ����ULocalPlayer����ʾ������ң�������ҵ�����ID�����õ���Ϣ
		// UGameInstance��Ϸʵ��������Ϸ��ȫ��״̬������
		APlayerController* PlayContorller = GetGameInstance()->GetFirstLocalPlayerController();
		// ����1Ŀ��������ĵ�ַ��ͨ������IP��ַ�Ͷ˿ڣ�����2�������͡������TRAVEL_Absolute ��ʾ����·������
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




