#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include <game/src/render/exampleDialogRender.hpp>
#include <game/src/state/exampleDialogState.hpp>
#include <olcTemplate/game/geometryWrapper.hpp>
#include <olcTemplate/game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>

using namespace stemaj;

void ExampleDialogRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto dialogLevel = static_cast<ExampleDialogState*>(state);

  pge->Clear(olc::VERY_DARK_CYAN);

  auto dia = dialogLevel->_dialog;
  if (dia.currentNode == -1) return;

  auto font = FT.Font("CutiePatootie-Rgjv", FontSize::NORMAL);

  Dialog::DialogNode &node = dia.dialogNodes[dia.currentNode];
  if (dia.displayingOptions)
  {
    float y = 10;
    for (size_t i = 0; i < node.options.size(); ++i)
    {

      auto r = font->RenderStringToDecal(utf8::utf8to32(
        std::to_string(i + 1) + ". " + node.options[i].first), olc::WHITE);

      auto rect = Rect({10,(int)y}, {r->sprite->width,r->sprite->height});
      olc::Pixel color = olc::WHITE;
      Point p;
      p.x = dialogLevel->_mousePos.x;
      p.y = dialogLevel->_mousePos.y;
      if (contains(rect,p))
//          { dialogLevel->_mousePos.x, dialogLevel->_mousePos.y }))
      {
        dialogLevel->Select(int(i));
        color = olc::YELLOW;        
      }
      pge->DrawDecal({10, y}, r, {1,1}, color);
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
