#include <olcTemplate/game/src/render/helper/olcHelper.hpp>
#include <game/src/render/exampleCoroutineRender.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <game/src/state/exampleCoroutineState.hpp>
#include <olcTemplate/game/assets.hpp>

using namespace stemaj;

void ExampleCoroutineRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto s = static_cast<ExampleCoroutineState*>(state);
  pge->Clear(olc::VERY_DARK_BLUE);

  auto pos = s->RoomBackgroundPosition();
  auto scale = s->RoomBackgroundScale();
  pge->DrawDecal({(float)pos.x,(float)pos.y}, AS.Decal("japan_1"), { scale, scale });

  auto lx = s->debugLinesX();
  for (auto& x : lx)
  {
    pge->DrawLine(x.first.x, x.first.y, x.second.x, x.second.y, olc::Pixel(s->GetColorXLines()));
  }
  auto ly = s->debugLinesY();
  for (auto& y : ly)
  {
    pge->DrawLine(y.first.x, y.first.y, y.second.x, y.second.y, olc::Pixel(s->GetColorYLines()));
  }
  auto lz = s->debugLinesZ();
  for (auto& z : lz)
  {
    pge->DrawLine(z.first.x, z.first.y, z.second.x, z.second.y, olc::Pixel(s->GetColorZLines()));
  }
  
  if (s->objVisible())
  {
    OlcHelper::FillCircleDecal(pge, int(s->factorCircleSize),
      PT<int>{s->objPos.x, s->objPos.y}, olc::RED);
  }

  pge->DrawLine((int)s->P1.x, (int)s->P1.y, (int)s->P2.x, (int)s->P2.y, olc::WHITE);
  pge->FillCircle((int)s->P1.x, (int)s->P1.y, 5, olc::RED);
  pge->FillCircle((int)s->P2.x, (int)s->P2.y, 5, olc::BLUE);
}
