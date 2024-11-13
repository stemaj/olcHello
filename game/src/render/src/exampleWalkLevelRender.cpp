#include <cmath>
#include <game/src/render/exampleWalkLevelRender.hpp>
#include <game/src/state/exampleWalkLevelState.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include <olcTemplate/game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/quaternion.hpp>

using namespace stemaj;

// Umrechnung 3D -> 2D (isometrische Projektion)
    olc::vi2d ProjectTo2D(float x, float y, float z, float angle = 10.0f) {
        float isoX = x * cosf(angle * 3.14159f / 180.0f) - z * cosf(angle * 3.14159f / 180.0f);
        float isoY = y - x * sinf(angle * 3.14159f / 180.0f) - z * sinf(angle * 3.14159f / 180.0f);
        int screenX = (int)(CO.W / 2 + isoX);
        int screenY = (int)(CO.H / 2 - isoY);
        return {screenX, screenY};
    }
    
void DrawAxis(olc::PixelGameEngine* pge, int len = 240) {
        olc::vi2d origin = ProjectTo2D(0, 0, 0);
        olc::vi2d xAxisEnd = ProjectTo2D(len, 0, 0);
        pge->DrawLine(origin, xAxisEnd, olc::GREEN);
        olc::vi2d yAxisEnd = ProjectTo2D(0, len, 0);
	pge->DrawLine(origin, yAxisEnd, olc::BLUE);
        olc::vi2d zAxisEnd = ProjectTo2D(0, 0, len);
	pge->DrawLine(origin, zAxisEnd, olc::YELLOW);
    }

    void DrawGridXZ(olc::PixelGameEngine* pge) {
        int gridSize = 200;
        int gridSpacing = 50;
        for (int x = -gridSize; x <= gridSize; x += gridSpacing) {
            olc::vi2d start = ProjectTo2D(x, 0, -gridSize);
            olc::vi2d end = ProjectTo2D(x, 0, gridSize);
            pge->DrawLine(start, end, olc::DARK_GREY);
        }
        for (int z = -gridSize; z <= gridSize; z += gridSpacing) {
            olc::vi2d start = ProjectTo2D(-gridSize, 0, z);
            olc::vi2d end = ProjectTo2D(gridSize, 0, z);
					pge->DrawLine(start, end, olc::DARK_GREY);
        }
    }

    void DrawPoint3D(olc::PixelGameEngine* pge, float x, float y, float z, olc::Pixel color) {
        olc::vi2d point2D = ProjectTo2D(x, y, z);
			pge->FillCircle(point2D, 8, color);
    }

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

  // Koordinatensystem und Gitter zeichnen
        DrawGridXZ(pge);
        DrawAxis(pge);

        // Ausgangspunkt bei (10, 0, 10) definieren
        std::array<float, 3> point = {150, 0, 150};

        // Winkel kumulativ erhöhen
        cumulativeAngle += fElapsedTime * 45.0f; // 45 Grad pro Sekunde

        // Quaternion für die Rotation um die Y-Achse erstellen
        Quaternion<float> rotation(cosf(cumulativeAngle / 2.0f * 3.14159f / 180.0f),
                                   0, sinf(cumulativeAngle / 2.0f * 3.14159f / 180.0f), 0);

        // Punkt rotieren
        std::array<float, 3> rotatedPoint = rotation.rotate(point);
        DrawPoint3D(pge, rotatedPoint[0], rotatedPoint[1], rotatedPoint[2], olc::RED);

}

