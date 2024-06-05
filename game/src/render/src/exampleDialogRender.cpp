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

  if (dialogLevel->currentNode == -1) return;

  auto font = FT.Font("CutiePatootie-Rgjv", FontSize::NORMAL);

  ExampleDialogState::DialogNode &node = 
    dialogLevel->dialogNodes[dialogLevel->currentNode];
  if (dialogLevel->displayingOptions)
  {
    float y = 10;
    for (size_t i = 0; i < node.options.size(); ++i)
    {
      auto r = font->RenderStringToDecal(utf8::utf8to32(
        std::to_string(i + 1) + ". " + node.options[i].first), olc::YELLOW);
      pge->DrawDecal({10, y}, r);
      y += (r->sprite->height+10);
    }
  }
  else
  {
    auto r = font->RenderStringToDecal(utf8::utf8to32(
      node.speaker + ": " + node.text), olc::WHITE);
    pge->DrawDecal({10, 10}, r);
  }
}
