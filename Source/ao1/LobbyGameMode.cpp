// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include	"GameFramework/PlayerState.h"

// 重载函数，参数是系统自动分配的，当玩家进入服务器时，虚幻引擎会自动创建一个玩家控制器实例
// 这个实例也会作为参数传递给PostLogin函数，下面注销也是这个参数，只不过是基类的类型
void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	
	if (GameState)
	{
		// 等价的可以替换 GameState->PlayerArray.Num();
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("player in game %d"), NumberOfPlayers)
			);

			// 使用模板参数 APlayerState 是为了指定返回的具体类型，虽然这里GetPlayerState不加模板参数返回的基类也是APlayerState的指针
			APlayerState* PlayState=NewPlayer->GetPlayerState<APlayerState>();
			if (PlayState)
			{
				FString PlayerName=PlayState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(
					2,
					60.f,
					FColor::Cyan,
					FString::Printf(TEXT("%s has 加入  join the game"), *PlayerName)
				);
			}

			
		}
	}
	
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	
	APlayerState* PlayState = Exiting->GetPlayerState<APlayerState>();
	if (PlayState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		GEngine->AddOnScreenDebugMessage(
			1,
			60.f,
			FColor::Yellow,
			FString::Printf(TEXT("player in game :%d"), NumberOfPlayers-1)
		);

		FString PlayerName = PlayState->GetPlayerName();
		GEngine->AddOnScreenDebugMessage(
			2,
			60.f,
			FColor::Cyan,
			FString::Printf(TEXT("%s has Exiting the game"), *PlayerName)
		);
	}
	
}
