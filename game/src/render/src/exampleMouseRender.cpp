#include <game/src/render/exampleMouseRender.hpp>
#include <game/src/state/exampleMouseState.hpp>
#include <olcTemplate/game/gui.hpp>
#include "olcTemplate/game/input.hpp"
#include "olcTemplate/game/src/render/helper/olcHelper.hpp"
#include "sol.hpp"

using namespace stemaj;

ExampleMouseRender::ExampleMouseRender()
{
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

  try
  {
    lua.safe_script_file("scripts/exampleMouse.lua");
  }
  catch (const sol::error& e)
  {
    std::cout << std::string(e.what()) << std::endl;
  }

  _gui->setColNormal(255,255,255,255);

  sol::table buttonsTable = lua["imageButtons"].get_or(sol::table(lua,sol::create));
  for (auto& [key, values] : buttonsTable)
  {
    auto p = ((sol::table)values).get_or<std::array<float, 2>>(2,{});

    _gui->prepareImageButton((ButtonAction)key.as<int>(),
      ((sol::table)values).get_or<std::string>(1,""),
      CO.D({p[0],p[1]}),
      ((sol::table)values).get_or(3,0));
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
