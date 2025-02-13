#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "SpartaState.h"
#include "SpartaInstance.h"
ASpartaGameMode::ASpartaGameMode()
{
	// BP를 쓰면 안해도 상관없는 작업이긴 하다.
	DefaultPawnClass = ASpartaCharacter::StaticClass(); // 객체 생성안하고 반환할 수 있도록 붙는것.
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
	PlayerStateClass = ASpartaState::StaticClass();
}
