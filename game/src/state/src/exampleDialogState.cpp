#include <game/src/state/exampleDialogState.hpp>
#include <game/src/render/exampleDialogRender.hpp>
#include <olcTemplate/game/videoFrame.hpp>
#include <olcTemplate/game/src/tools/dialog.hpp>
#include <memory>

using namespace stemaj;

ExampleDialogState::ExampleDialogState() : _videoFrame(std::make_unique<VideoFrame>("assets/mp4/watch.mp4")), _render(std::make_unique<ExampleDialogRender>())
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

  return ChangeLevel(input, fElapsedTime);
}

Render* ExampleDialogState::GetRender()
{
  return _render.get();
}

void ExampleDialogState::LoadLevelData()
{
  _dialog.Load("exampleDialog");

  //_videoFrame = std::make_unique<VideoFrame>("assets/mp4/watch.mp4");
}

void ExampleDialogState::SaveLevelData()
{
}
