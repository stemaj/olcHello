#ifndef __EXAMPLECOROUTINESTATE_HPP
#define __EXAMPLECOROUTINESTATE_HPP

#include "b2_types.h"
#include "olcTemplate/game/room3d.hpp"
#include <memory>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>

namespace stemaj {

class ExampleCoroutineRender;
class Room3d;

class ExampleCoroutineState : public LevelState
{
public:

  explicit ExampleCoroutineState();
  virtual ~ExampleCoroutineState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

  PT<float> P1, P2, velocity;
  bool isDragging = false;
  float k = 10.0f;  // Federkonstante
  float damping = 0.9f; // Dämpfungsfaktor

  PT<int> RoomBackgroundPosition() const { return _room3d->GetBackgroundPosition(); }
  float RoomBackgroundScale() const { return _room3d->GetBackgroundScale(); }

  std::vector<std::pair<PT<float>,PT<float>>> debugLinesX() { return _room3d->debugLinesX; }
  std::vector<std::pair<PT<float>,PT<float>>> debugLinesY() { return _room3d->debugLinesY; }
  std::vector<std::pair<PT<float>,PT<float>>> debugLinesZ() { return _room3d->debugLinesZ; }
  uint32_t GetColorXLines() { return _room3d->GetColorXLines(); }
  uint32_t GetColorYLines() { return _room3d->GetColorYLines(); }
  uint32_t GetColorZLines() { return _room3d->GetColorZLines(); }

  float factorCircleSize = 1.0f;
  PT<int> objPos;
  bool objVisible() { return _pos.z > _room3d->GetCamZ(); } ;

  PT<int> ProjectedPos() const;
  
private:

  // Startposition
  float _startX = 6000.0f, _startY = 200.0f, _startZ = 2500.0f;
  // Endposition
  float _endX = 150.0f, _endY = -150.0f, _endZ = 50.0f;
  // Aktuelle Position
  WorldPosition _pos = {_startX, _startY, _startZ};
  // Geschwindigkeit
  float _speed = 800.0f;

  std::unique_ptr<Room3d> _room3d;

  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<ExampleCoroutineRender> _render;
};

} // namespace stemaj

#endif // __EXAMPLECOROUTINESTATE_HPP

