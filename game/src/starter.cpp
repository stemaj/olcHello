#include <game/starter.hpp>
#include <game/src/state/exampleCollisionState.hpp>
#include <game/src/state/examplePathLevelState.hpp>
#include <game/src/state/exampleWalkLevelState.hpp>
#include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <game/src/state/exampleDialogState.hpp>
#include <optional>

using namespace stemaj;

std::optional<std::unique_ptr<State>> Starter::Update(const Input& input, float fElapsedTime)
{
  if (input.k1Pressed) return std::make_unique<ExampleCollisionState>();
  if (input.k2Pressed) return std::make_unique<ExamplePathLevelState>();
  if (input.k3Pressed) return std::make_unique<ExampleWalkLevelState>();
  if (input.k4Pressed) return std::make_unique<ExampleScreenElementsLevelState>();
  if (input.k5Pressed) return std::make_unique<ExampleDialogState>();
  return std::nullopt;
}
