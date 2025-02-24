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
    pge->DrawLine(x.first.x, x.first.y, x.second.x, x.second.y, olc::Pixel(), s->GetColorX());
  }
  auto ly = s->debugLinesY();
  for (auto& y : ly)
  {
    pge->DrawLine(y.first.x, y.first.y, y.second.x, y.second.y, olc::Pixel(), s->GetColorY());
  }
  auto lz = s->debugLinesZ();
  for (auto& z : lz)
  {
    pge->DrawLine(z.first.x, z.first.y, z.second.x, z.second.y, olc::Pixel(), s->GetColorZ());
  }


// Bewegung des Punktes zum Endpunkt
float dx = endX - posX;
float dy = endY - posY;
float dz = endZ - posZ;
float distance = Distance(posX, posY, posZ, endX, endY, endZ);

if (distance > 1.0f) { // Stoppen, wenn nahe genug
    float norm = sqrtf(dx * dx + dy * dy + dz * dz);
    if (norm > 0.0f) {
        dx /= norm;
        dy /= norm;
        dz /= norm;
    }

    posX += dx * speed * fElapsedTime;
    posY += dy * speed * fElapsedTime;
    posZ += dz * speed * fElapsedTime;
}

  // Kreisgröße anpassen basierend auf der Z-Koordinate (je näher, desto größer)
  float minZ = 20.0f;  // Kleinste Z-Koordinate (nächstgelegene Position)
  float maxZ = 2000.0f; // Größte Z-Koordinate (fernste Position)
  float factor = 1.0f + (1.0f - ((posZ - minZ) / (maxZ - minZ))) * 40.0f;
  if (factor < 1.0f) factor = 1.0f;
	
	
  // Kreis zeichnen
  auto objPos = Project(posX, posY, posZ);
  //pge->FillCircle(objPos, int(1 * factor), olc::RED);
  if (posZ > camZ) 
  OlcHelper::FillCircleDecal(pge, int(1 * factor), PT<int>{objPos.x, objPos.y}, olc::RED);

  // for (auto& ball : s->balls) {
  //   pge->FillCircle(ball.x, ball.y, 10, ball.color); // Ball zeichnen
  // }

  pge->DrawLine((int)s->P1.x, (int)s->P1.y, (int)s->P2.x, (int)s->P2.y, olc::WHITE);
  pge->FillCircle((int)s->P1.x, (int)s->P1.y, 5, olc::RED);
  pge->FillCircle((int)s->P2.x, (int)s->P2.y, 5, olc::BLUE);
}
