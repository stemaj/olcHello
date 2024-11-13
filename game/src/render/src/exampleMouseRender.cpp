#include <game/src/render/exampleMouseRender.hpp>
#include <game/src/state/exampleMouseState.hpp>
#include <olcTemplate/game/gui.hpp>
#include "olcTemplate/game/src/render/helper/olcHelper.hpp"

using namespace stemaj;

void ExampleMouseRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto s = static_cast<ExampleMouseState*>(state);

  if (!_gui->created())
  {
    _gui->setColNormal(255,255,255,255);
    _gui->createImageButton("back-button", 10.0f, 10.0f, 8);

    _gui->setCreated();
  }
 
  pge->Clear(olc::VERY_DARK_MAGENTA);

  if (s->_tapR != ExampleMouseState::TAP_NO)
  {
    OlcHelper::FillCircleDecal(pge, 25, s->_tapPos, olc::YELLOW);
  }
  else if (s->_tap != ExampleMouseState::TAP_NO)
  {
    OlcHelper::FillCircleDecal(pge, 20, s->_tapPos, olc::WHITE);
  }

  s->_tapBack = _gui->backButtonPressed() ? ExampleMouseState::TAP_BEGIN : ExampleMouseState::TAP_NO;

  _gui->Update(pge);
}
