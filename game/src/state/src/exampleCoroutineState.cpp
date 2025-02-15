#include <game/src/render/exampleCoroutineRender.hpp>
#include <game/src/state/exampleCoroutineState.hpp>
#include <random>

using namespace stemaj;

ExampleCoroutineState::ExampleCoroutineState() : _render(std::make_unique<ExampleCoroutineRender>())
{
  LoadLevelData();
}

ExampleCoroutineState::~ExampleCoroutineState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleCoroutineState::Update(
  const Input& input, float fElapsedTime)
{
  if (input.leftMouseHeld) {
    P2 = { input.mouseX, input.mouseY };
    velocity = {0.0f, 0.0f};
    isDragging = true;
  } else if (isDragging) {
    isDragging = false;
  }

  if (!isDragging) {
    PT<float> force = P1 - P2; // Hookesches Gesetz: F = -k * x
    force.x *= k;
    force.y *= k;
    velocity.x += force.x * fElapsedTime; // Bewegungsgleichung
    velocity.y += force.y * fElapsedTime; // Bewegungsgleichung
    velocity.x *= damping; // Dämpfung
    velocity.y *= damping; // Dämpfung
    P2.x += velocity.x * fElapsedTime; // Position aktualisieren
    P2.y += velocity.y * fElapsedTime; // Position aktualisieren
  }

  return RequestForMainMenu(input.escapePressed, fElapsedTime);
}

Render* ExampleCoroutineState::GetRender()
{
  return _render.get();
}

void ExampleCoroutineState::LoadLevelData()
{
  P1 = {CO.W / 2.0f, CO.H * 19.0f / 20.0f};
  P2 = P1;
  velocity = {0.0f, 0.0f};
}

void ExampleCoroutineState::SaveLevelData()
{
}
