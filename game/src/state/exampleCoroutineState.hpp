#ifndef __EXAMPLECOROUTINESTATE_HPP
#define __EXAMPLECOROUTINESTATE_HPP

#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>

namespace stemaj {

class ExampleCoroutineRender;

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

  
private:

  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<ExampleCoroutineRender> _render;
};

} // namespace stemaj

#endif // __EXAMPLECOROUTINESTATE_HPP

