#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PingPongPlayerController.generated.h"

class UScoreWidget;

UCLASS()
class PINGPONG_API APingPongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APingPongPlayerController();

protected:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

private:
	void MovePaddle(float Value);
};