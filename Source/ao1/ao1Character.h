// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "ao1Character.generated.h"


UCLASS(config=Game)
class Aao1Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	Aao1Character();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	// 智能指针变量，TSharedPtr是智能指针类型，参数1指定管理的对象类型，参数2线程安全模式，最后是名称
	// TSharedPtr 是一个模板类，允许你为不同类型的对象创建智能指针。且因为没有包含对应的头文件，所以需要指定关键字class,安全模式可选项
	// TSharedPtr<class IOnlineSession, ESPMode::ThreadSafe>onlinesessioninterface;
	// 指向会话接口实例对象的智能指针变量，这边只是定义了，没有初始化
	IOnlineSessionPtr onlinesessioninterface;

protected:
	UFUNCTION(BlueprintCallable)
	void CreateGameSession();	// 创建会话函数

	UFUNCTION(BlueprintCallable)
	void JoinGameSession();

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);	// 创建会话完成后的委托回调函数
	void OnFindSessionsComplete(bool bWasSuccessful);
	// 枚举类型的变量Result,存储结果值
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	// FOnCreateSessionCompleteDelegate是委托类，用于处理创建会话（Session）完成后的回调函数。
	// 可以被用于处理创建会话完成后的回调函数，比如在创建一个新的游戏会话后，
	// 可以使FOnCreateSessionCompleteDelegate类来通知游戏玩家会话已经创建完毕并且可以加入游戏了。
	// 创建了一个创建会话委托类的变量，用于处理会话创建完成时的回调。
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	TSharedPtr<FOnlineSessionSearch> onlinesessionsearch;
};

