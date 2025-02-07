#include <game/src/render/exampleCoroutineRender.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

void ExampleCoroutineRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  pge->Clear(olc::DARK_BLUE);
  pge->DrawString({ 10, 10 }, "ExampleCoroutineRender", olc::WHITE);
}