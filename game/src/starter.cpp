#include <game/starter.hpp>
#include <game/src/state/exampleCollisionState.hpp>
#include <game/src/state/examplePathLevelState.hpp>
#include <game/src/state/exampleWalkLevelState.hpp>
#include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <game/src/state/exampleDialogState.hpp>
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
		default:
			return std::nullopt;
	}
}
