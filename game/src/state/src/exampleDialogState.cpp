#include <game/src/state/exampleDialogState.hpp>
#include <game/src/render/exampleDialogRender.hpp>
#include <olcTemplate/game/src/tools/dialog.hpp>
#include <memory>

using namespace stemaj;

ExampleDialogState::ExampleDialogState() : _render(std::make_unique<ExampleDialogRender>())
{
  _fader.StartFadeIn();
  LoadLevelData();
}

ExampleDialogState::~ExampleDialogState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleDialogState::Update(
  const Input& input, float fElapsedTime)
{
  _dialog.Update(input, fElapsedTime);

  _mousePos = { input.mouseX, input.mouseY };

  return RequestForMainMenu(input.escapePressed, fElapsedTime);
}

Render* ExampleDialogState::GetRender()
{
  return _render.get();
}

void ExampleDialogState::LoadLevelData()
{
  _dialog.Load("scripts/exampleDialog.lua");
}

void ExampleDialogState::SaveLevelData()
{
}
