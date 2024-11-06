#include <game/src/state/exampleMouseState.hpp>
#include <game/src/render/exampleMouseRender.hpp>
#include <olcTemplate/game/src/render/levelRender.hpp>

using namespace stemaj;

ExampleMouseState::ExampleMouseState() : _render(std::make_unique<ExampleMouseRender>())
{
  _fader.StartFadeIn();
  LoadLevelData();
}

ExampleMouseState::~ExampleMouseState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleMouseState::ExampleMouseState::Update(
  const Input& input, float fElapsedTime)
{
  return ChangeLevel(input, fElapsedTime);
}

Render* ExampleMouseState::GetRender()
{
  return _render.get();
}

void ExampleMouseState::LoadLevelData()
{
  std::cout << "loading" << std::endl;
}

void ExampleMouseState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}
