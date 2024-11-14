#include "olcTemplate/game/guiElements.hpp"
#include <game/src/render/examplePathLevelRender.hpp>
#include <game/src/state/examplePathLevelState.hpp>

using namespace stemaj;

void ExamplePathLevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto pathLevel = static_cast<ExamplePathLevelState*>(state);

  auto toPixelColor = [](const MainMenuColor& c){
    return olc::Pixel{ c[0], c[1], c[2], c[3] };
  };

  pge->Clear(toPixelColor(pathLevel->_colorBackground));

  for (auto g : pathLevel->_grid)
  {
    pge->DrawCircle({g.first.x,g.first.y},1,toPixelColor(g.second ? pathLevel->_colorPath : pathLevel->_colorPolygon));
  }

  for (auto p : pathLevel->_path)
  {
    pge->DrawCircle({p.x,p.y}, 6, toPixelColor(pathLevel->_colorPath));
  }

  pge->DrawCircle({pathLevel->_end.x, pathLevel->_end.y},
    3, toPixelColor(pathLevel->_colorEnd));

  pge->FillCircle({pathLevel->_obj.x, pathLevel->_obj.y},
    4, toPixelColor(pathLevel->_colorObject));

  for (const auto& pp : pathLevel->_polygonSource)
  {
    pge->DrawCircle(pp.x, pp.y, 2, toPixelColor(pathLevel->_colorPolygon));
  }
}
