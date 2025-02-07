#ifndef __EXAMPLECOROUTINESTATE_HPP
#define __EXAMPLECOROUTINESTATE_HPP

#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>
#include <coroutine>

namespace stemaj {

class ExampleCoroutineRender;

class ExampleCoroutineState : public LevelState
{
public:

  explicit ExampleCoroutineState();
  virtual ~ExampleCoroutineState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

  // Struktur für einen Ball
  struct Ball {
    float x, y;       // Position
    float velocity;   // Geschwindigkeit
    olc::Pixel color; // Farbe
    bool isFalling;   // Status (fällt noch?)

    Ball(float startX, float startY, float startVelocity, olc::Pixel c)
        : x(startX), y(startY), velocity(startVelocity), color(c), isFalling(true) {}
  };

  std::vector<Ball> balls; // Liste aller Bälle

  // Definieren einer Coroutine-Struktur
  struct Coroutine {
    struct promise_type {
      Coroutine get_return_object() { return {}; } // Rückgabe eines leeren Coroutine-Objekts
      std::suspend_never initial_suspend() { return {}; } // Keine Anfangspause
      std::suspend_always final_suspend() noexcept { return {}; } // Coroutine am Ende pausieren
      void return_void() {} // Keine Rückgabe
      void unhandled_exception() { std::terminate(); } // Fehlerbehandlung
    };
  };
  Coroutine SimulateBall(Ball& ball);

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

