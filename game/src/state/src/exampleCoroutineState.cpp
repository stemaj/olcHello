#include <game/src/render/exampleCoroutineRender.hpp>
#include <game/src/state/exampleCoroutineState.hpp>

using namespace stemaj;

ExampleCoroutineState::ExampleCoroutineState() : _render(std::make_unique<ExampleCoroutineRender>())
{
  LoadLevelData();
}

ExampleCoroutineState::~ExampleCoroutineState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleCoroutineState::Update(
  const Input& input, float fElapsedTime)
{
  return RequestForMainMenu(input.escapePressed, fElapsedTime);
}

Render* ExampleCoroutineState::GetRender()
{
  return _render.get();
}

void ExampleCoroutineState::LoadLevelData()
{
}

void ExampleCoroutineState::SaveLevelData()
{
}
