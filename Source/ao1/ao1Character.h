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
	// ����ָ�������TSharedPtr������ָ�����ͣ�����1ָ������Ķ������ͣ�����2�̰߳�ȫģʽ�����������
	// TSharedPtr ��һ��ģ���࣬������Ϊ��ͬ���͵Ķ��󴴽�����ָ�롣����Ϊû�а�����Ӧ��ͷ�ļ���������Ҫָ���ؼ���class,��ȫģʽ��ѡ��
	// TSharedPtr<class IOnlineSession, ESPMode::ThreadSafe>onlinesessioninterface;
	// ָ��Ự�ӿ�ʵ�����������ָ����������ֻ�Ƕ����ˣ�û�г�ʼ��
	IOnlineSessionPtr onlinesessioninterface;

protected:
	UFUNCTION(BlueprintCallable)
	void CreateGameSession();	// �����Ự����

	UFUNCTION(BlueprintCallable)
	void JoinGameSession();

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);	// �����Ự��ɺ��ί�лص�����
	void OnFindSessionsComplete(bool bWasSuccessful);
	// ö�����͵ı���Result,�洢���ֵ
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	// FOnCreateSessionCompleteDelegate��ί���࣬���ڴ������Ự��Session����ɺ�Ļص�������
	// ���Ա����ڴ������Ự��ɺ�Ļص������������ڴ���һ���µ���Ϸ�Ự��
	// ����ʹFOnCreateSessionCompleteDelegate����֪ͨ��Ϸ��һỰ�Ѿ�������ϲ��ҿ��Լ�����Ϸ�ˡ�
	// ������һ�������Ựί����ı��������ڴ���Ự�������ʱ�Ļص���
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	TSharedPtr<FOnlineSessionSearch> onlinesessionsearch;
};

