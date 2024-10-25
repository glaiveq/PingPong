#include "PingPongGameMode.h"
#include "PingPongPaddle.h"
#include "PingPongPlayerController.h"

#include "Engine/Engine.h"

APingPongGameMode::APingPongGameMode()
{
	DefaultPawnClass = APingPongPaddle::StaticClass();
	PlayerControllerClass = APingPongPlayerController::StaticClass();
	
	bMatchStarted = false;
}

void APingPongGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Waiting for the match to start..."));
		UE_LOG(LogTemp, Warning, TEXT("Waiting for the match to start..."));
	}

}

void APingPongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if (!bMatchStarted)
	{
		StartMatch();
		bMatchStarted = true;
	}
}

void APingPongGameMode::StartMatch()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Match Started!"));
		UE_LOG(LogTemp, Warning, TEXT("Match Started!"));
	}
}
