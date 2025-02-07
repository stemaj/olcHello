#include <game/src/render/exampleCoroutineRender.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <game/src/state/exampleCoroutineState.hpp>

using namespace stemaj;

void ExampleCoroutineRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto s = static_cast<ExampleCoroutineState*>(state);
  pge->Clear(olc::VERY_DARK_BLUE);

  // for (auto& ball : s->balls) {
  //   pge->FillCircle(ball.x, ball.y, 10, ball.color); // Ball zeichnen
  // }

  pge->DrawLine((int)s->P1.x, (int)s->P1.y, (int)s->P2.x, (int)s->P2.y, olc::WHITE);
  pge->FillCircle((int)s->P1.x, (int)s->P1.y, 5, olc::RED);
  pge->FillCircle((int)s->P2.x, (int)s->P2.y, 5, olc::BLUE);
}
