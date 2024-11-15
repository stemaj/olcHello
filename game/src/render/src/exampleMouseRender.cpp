#include <game/src/render/exampleMouseRender.hpp>
#include <game/src/state/exampleMouseState.hpp>
#include <olcTemplate/game/gui.hpp>
#include "olcTemplate/game/input.hpp"
#include "olcTemplate/game/src/render/helper/olcHelper.hpp"
#include "sol.hpp"
#include <olcTemplate/game/loadsave.hpp>

using namespace stemaj;

ExampleMouseRender::ExampleMouseRender()
{
  _gui->setColNormal(255,255,255,255);

  LS.Init("scripts/exampleMouse.lua", true);
  auto graphBtns = LS.ButtonGraphics();
  for (const auto& [key,value] : graphBtns)
  {
    _gui->prepareImageButton(
      key, value.file, value.pos, value.buttonDelta);
  }
}

void ExampleMouseRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto s = static_cast<ExampleMouseState*>(state);

  pge->Clear(olc::VERY_DARK_MAGENTA);

  if (s->_tapR != ExampleMouseState::TAP_NO)
  {
    OlcHelper::FillCircleDecal(pge, 25, s->_tapPos, olc::YELLOW);
  }
  else if (s->_tap != ExampleMouseState::TAP_NO)
  {
    OlcHelper::FillCircleDecal(pge, 20, s->_tapPos, olc::WHITE);
  }

  _gui->Update(pge);

  s->_tapBack = _gui->pressedOn() == ButtonAction::BACK
    ? ExampleMouseState::TAP_BEGIN : ExampleMouseState::TAP_NO;
}
