#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include <game/src/render/exampleDialogRender.hpp>
#include <game/src/state/exampleDialogState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>

using namespace stemaj;

void ExampleDialogRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto dialogLevel = static_cast<ExampleDialogState*>(state);

  pge->Clear(olc::VERY_DARK_CYAN);

  // auto font = FT.Font("CutiePatootie-Rgjv", FontSize::NORMAL);
  // auto r = font->RenderStringToDecal(utf8::utf8to32(std::string("Ä Bik ß")), olc::GREEN);
  // pge->DrawDecal({ 200,80 }, r,{1.0f,1.0f}, olc::GREEN);
}
