#include "olcTemplate/game/src/render/helper/olcHelper.hpp"
#include <game/src/render/exampleMouseRender.hpp>
#include <game/src/state/exampleMouseState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

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
}
