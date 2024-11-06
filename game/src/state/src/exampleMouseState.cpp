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
  _tapPos = { input.mouseX, input.mouseY };

  if (input.leftMouseClicked) _tap = TAP_BEGIN;
  else if (input.leftMouseHeld) _tap = TAP_HELD;
  else if (input.leftMouseReleased) _tap = TAP_END;
  else _tap = TAP_NO;

  if (input.rightMouseClicked) _tapR = TAP_BEGIN;
  else if (input.rightMouseHeld) _tapR = TAP_HELD;
  else if (input.rightMouseReleased) _tapR = TAP_END;
  else _tapR = TAP_NO;

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
