#include "olcTemplate/game/src/render/helper/olcHelper.hpp"
#include <game/src/render/exampleMouseRender.hpp>
#include <game/src/state/exampleMouseState.hpp>
#include <memory>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/assets.hpp>
#include "olcTemplate/game/src/engine/olcPGEX_QuickGUI.h"

using namespace stemaj;

void ExampleMouseRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto s = static_cast<ExampleMouseState*>(state);

  if (s->_guiManager == nullptr)
	{
		s->_guiManager = std::make_unique<olc::QuickGUI::Manager>(false);
    s->_guiManager->colNormal = olc::WHITE;

    _backControl =  std::make_unique<olc::QuickGUI::ImageButton>(
				*s->_guiManager, *AS.Renderable("back-button"),
				olc::vf2d{10.0f,10.0f}, olc::vf2d{
          (float)AS.Renderable("back-button")->Sprite()->width + 8,
          (float)AS.Renderable("back-button")->Sprite()->height + 8});
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

  s->_guiManager->Update(pge);
  s->_guiManager->DrawDecal(pge);
}
