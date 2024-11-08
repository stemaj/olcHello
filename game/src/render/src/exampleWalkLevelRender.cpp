#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include <game/src/render/exampleWalkLevelRender.hpp>
#include <game/src/state/exampleWalkLevelState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>
#include <string>

using namespace stemaj;

void ExampleWalkLevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto walkLevel = static_cast<ExampleWalkLevelState*>(state);

  pge->Clear(olc::YELLOW);

  pge->DrawPartialDecal({(float)walkLevel->_drawPos.x, (float)walkLevel->_drawPos.y},
    walkLevel->_decal,
    {(float)walkLevel->_sourceRectPos.x,(float)walkLevel->_sourceRectPos.y},
    {(float)walkLevel->_sourceRectSize.x,(float)walkLevel->_sourceRectSize.y},
    {walkLevel->_scale.x,walkLevel->_scale.y});

  auto font = FT.Font("CutiePatootie-Rgjv", FontSize::NORMAL);
  auto r = font->RenderStringToDecal(utf8::utf8to32(std::string("Ä Bik ß")), olc::GREEN);
  pge->DrawDecal({ 200,80 }, r,{1.0f,1.0f}, olc::GREEN);
}
