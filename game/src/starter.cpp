#include <game/starter.hpp>
#include <game/src/state/exampleCoroutineState.hpp>
#include <game/src/state/exampleCollisionState.hpp>
#include <game/src/state/examplePathLevelState.hpp>
#include <game/src/state/exampleWalkLevelState.hpp>
#include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <game/src/state/exampleDialogState.hpp>
#include <game/src/state/exampleMouseState.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/sound.hpp>

using namespace stemaj;

std::optional<std::unique_ptr<State>> Starter::SwitchState(const ButtonAction& action)
{
	switch (action) {
		case OPTION_1:
			SO.StopMusic();
			return std::make_unique<ExampleCollisionState>();
		case OPTION_2:
			SO.StopMusic();
			return std::make_unique<ExamplePathLevelState>();
		case OPTION_3:
			SO.StopMusic();
			return std::make_unique<ExampleWalkLevelState>();
		case OPTION_4:
			SO.StopMusic();
			return std::make_unique<ExampleScreenElementsLevelState>();
		case OPTION_5:
			SO.StopMusic();
			return std::make_unique<ExampleDialogState>();
		case OPTION_6:
			SO.StopMusic();
			return std::make_unique<ExampleMouseState>();
		case OPTION_7:
			SO.StopMusic();
			return std::make_unique<ExampleCoroutineState>();
		case BACK:
			SO.StopMusic();
			return std::make_unique<MainMenuState>();
		default:
			return std::nullopt;
	}
}
