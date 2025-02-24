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
  uint32_t GetColorX() { return _room3d->GetColorX(); }
  uint32_t GetColorY() { return _room3d->GetColorY(); }
  uint32_t GetColorZ() { return _room3d->GetColorZ(); }
  
private:

  std::unique_ptr<Room3d> _room3d;

  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<ExampleCoroutineRender> _render;
};

} // namespace stemaj

#endif // __EXAMPLECOROUTINESTATE_HPP

