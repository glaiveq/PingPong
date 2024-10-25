#include "PingPongPlayerController.h"
#include "PingPongPaddle.h"

#include "GameFramework/Actor.h"

APingPongPlayerController::APingPongPlayerController()
{
	
}

void APingPongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("MoveRight", this, &APingPongPlayerController::MovePaddle);
}

void APingPongPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void APingPongPlayerController::MovePaddle(float Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		if (APingPongPaddle* Paddle = Cast<APingPongPaddle>(ControlledPawn))
		{
			if (IsLocalController())
			{
				Paddle->MovePaddle(Value);
			}
		}
	}
}