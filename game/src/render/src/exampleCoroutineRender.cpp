#include <olcTemplate/game/src/render/helper/olcHelper.hpp>
#include <game/src/render/exampleCoroutineRender.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <game/src/state/exampleCoroutineState.hpp>
#include <olcTemplate/game/assets.hpp>

using namespace stemaj;



float fov = 100.0f;   // Brennweite
    float depth = 500.0f; // Maximale Tiefe des Gitters
    float gridSize = 100.0f;  // Abstand der Gitterlinien
    float gridWidth = 2000.0f; // Breite des Gitters (x-Richtung)
    float gridHeight = 500.0f; // Höhe des Gitters (y-Richtung)
    float startZ = -20.0f;  // Starttiefe des Gitters

    // Steuerung der Gitterlinien
    bool drawXLines = true; // Linien in x-Richtung (vertikal)
    bool drawYLines = true; // Linien in y-Richtung (horizontal)
    bool drawZLines = true; // Linien in z-Richtung (Tiefe)

    // Kamera-Position
    float camX = 0.0f, camY = 0.0f, camZ = 0.0f; // Startet leicht nach hinten versetzt
    float baseCamX = camX; // Basis-Kamerahöhe (zum Zurücksetzen)
    float baseCamY = camY; // Basis-Kamerahöhe (zum Zurücksetzen)

    float currentCamX;
    float currentCamY;

 // "Bump"-Effekt
 bool isBumping = false;
 float bumpTime = 0.0f;
 float bumpDuration = 0.3f; // Gesamtdauer des Bumps
 
 olc::vf2d vfBumpDir; // Richtung des Bumps
 float bumpBaseAmplitude = 5.0f; // Maximale Stärke
 

    // Startposition
    float startX = 6000.0f, startY = 200.0f, startZPos = 2500.0f;
    // Endposition
    float endX = 150.0f, endY = -150.0f, endZ = 50.0f;
    // Aktuelle Position
    float posX = startX, posY = startY, posZ = startZPos;
    // Geschwindigkeit
    float speed = 800.0f;

    // Decal-Position im 3D-Raum
    float decalX = -50.0f;
    float decalY = -10.0f;
    float decalZ = 200.0f;

    // Perspektivische Projektion mit Kameraverschiebung
    olc::vi2d Project(float x, float y, float z) {
        // Relativ zur Kamera berechnen
        float relX = x - camX;
        float relY = y - camY;
        float relZ = z - camZ;

        // Mindest-Z-Wert setzen (verhindert starke Verzögerungen bei z ≈ 0)
        float minZ = 10.0f;  // Setze die Mindesttiefe auf 10
        if (relZ < minZ) relZ = minZ;

        // Projektion auf 2D-Bildschirm
        float scale = fov / (relZ + fov);
        int screenX = int(CO.W / 2.f + relX * scale);
        int screenY = int(CO.H / 2.f - relY * scale);
        return { screenX, screenY };
    }

    // Abstand zwischen zwei 3D-Punkten berechnen
    float Distance(float x1, float y1, float z1, float x2, float y2, float z2) {
        return sqrtf((x2 - x1) * (x2 - x1) + 
                     (y2 - y1) * (y2 - y1) + 
                     (z2 - z1) * (z2 - z1));
    }

void ExampleCoroutineRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto s = static_cast<ExampleCoroutineState*>(state);
  pge->Clear(olc::VERY_DARK_BLUE);

  // Kamera-Steuerung
  if (pge->GetKey(olc::Key::A).bHeld) camX -= 50.0f * fElapsedTime;
  if (pge->GetKey(olc::Key::D).bHeld) camX += 50.0f * fElapsedTime;
  if (pge->GetKey(olc::Key::PGUP).bHeld) camZ += 50.0f * fElapsedTime;
  if (pge->GetKey(olc::Key::PGDN).bHeld) camZ -= 50.0f * fElapsedTime;
  if (pge->GetKey(olc::Key::W).bHeld) camY += 50.0f * fElapsedTime;
  if (pge->GetKey(olc::Key::S).bHeld) camY -= 50.0f * fElapsedTime;

// "Bump"-Effekt starten
if (pge->GetMouse(0).bReleased && !isBumping) {

    currentCamX = camX; // Speichere aktuelle Position
    currentCamY = camY;

    vfBumpDir = pge->GetMousePos() - olc::vf2d(s->P1.x,-s->P1.y);

    // vfBumpDir.x = camX + richt.x;
    // vfBumpDir.y = camY + richt.y;
    // // vfBumpDir = {1,0}; // ok
    // // vfBumpDir = {-1,0}; // ok
    // // vfBumpDir = {0,1}; // ok
    // // vfBumpDir = {0,-1}; // ok
    // // vfBumpDir = {1,1}; // ok
    // // vfBumpDir = {-1,-1}; // ok
    // // vfBumpDir = {-1,1}; // ok
    // // vfBumpDir = {1,-1}; // ok


    isBumping = true;
    bumpTime = 0.0f;
}

// "Bump"-Animation
if (isBumping) {
    bumpTime += fElapsedTime;
    if (bumpTime < bumpDuration) {
        // Sinusförmige Bewegung für sanftes Hoch- und Runtergehen

        olc::vf2d bumpDirection = vfBumpDir.norm() * -1.0f; // Umkehren der Richtung

        // Begrenzung der Bump-Stärke auf einen sinnvollen Bereich
        float bumpFactor = 1.0f + vfBumpDir.mag();
        float bumpStrength = bumpBaseAmplitude / std::clamp(bumpFactor, 0.1f, 0.2f); // Werte zwischen 1.5 und 5

        camX = currentCamX + bumpDirection.x * bumpStrength * sinf((bumpTime / bumpDuration) * 3.14159f);
        camY = currentCamY + bumpDirection.y * bumpStrength * sinf((bumpTime / bumpDuration) * 3.14159f);

    } else {
        camX = currentCamX;
        camY = currentCamY;
        isBumping = false;
    }
}


    olc::vf2d decalPos = Project(decalX, decalY, decalZ);
    float scaleFactor = fov / (decalZ - camZ + fov); // Skalierung mit Tiefe
    pge->DrawDecal(decalPos, AS.Decal("japan_1"), { scaleFactor, scaleFactor });


  // *** Gitter zeichnen mit steuerbaren Linien ***
  for (float z = startZ; z < depth; z += gridSize) {
    if (drawXLines) { // Vertikale Linien in x-Richtung
        for (float x = -gridWidth / 2; x <= gridWidth / 2; x += gridSize) {
            auto p1 = Project(x, -gridHeight / 2, z);
            auto p2 = Project(x, gridHeight / 2, z);
            pge->DrawLine(p1, p2, olc::VERY_DARK_GREY);
        }
    }
    if (drawYLines) { // Horizontale Linien in y-Richtung
        for (float y = -gridHeight / 2; y <= gridHeight / 2; y += gridSize) {
            auto p1 = Project(-gridWidth / 2, y, z);
            auto p2 = Project(gridWidth / 2, y, z);
            pge->DrawLine(p1, p2, olc::DARK_GREY);
        }
    }
}

if (drawZLines) { // Tiefenlinien in z-Richtung
    for (float x = -gridWidth / 2; x <= gridWidth / 2; x += gridSize) {
        for (float y = -gridHeight / 2; y <= gridHeight / 2; y += gridSize) {
            auto p1 = Project(x, y, startZ);
            auto p2 = Project(x, y, depth);
            pge->DrawLine(p1, p2, olc::GREY);
        }
    }

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
  pge->FillCircle(objPos, int(1 * factor), olc::RED);
  OlcHelper::FillCircleDecal(pge, int(1 * factor), PT<int>{objPos.x, objPos.y}, olc::RED);

  // for (auto& ball : s->balls) {
  //   pge->FillCircle(ball.x, ball.y, 10, ball.color); // Ball zeichnen
  // }

  pge->DrawLine((int)s->P1.x, (int)s->P1.y, (int)s->P2.x, (int)s->P2.y, olc::WHITE);
  pge->FillCircle((int)s->P1.x, (int)s->P1.y, 5, olc::RED);
  pge->FillCircle((int)s->P2.x, (int)s->P2.y, 5, olc::BLUE);
}
