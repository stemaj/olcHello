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
  for (auto& ball : balls) {
    SimulateBall(ball);// Coroutine aufrufen, um die Bewegung zu steuern
  }

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
  // Zufällige Bälle erzeugen
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> distX(20, CO.W - 20);
  std::uniform_real_distribution<float> distVel(1.0f, 3.0f);
  std::vector<olc::Pixel> colors = {olc::RED, olc::GREEN, olc::BLUE, olc::YELLOW, olc::CYAN, olc::MAGENTA};

  for (int i = 0; i < 105; i++) { // 5 Bälle erzeugen
    balls.emplace_back(distX(gen), 20.0f, distVel(gen), colors[i % colors.size()]);
  }

  P1 = {CO.W / 2.0f, CO.H * 19.0f / 20.0f};
  P2 = P1;
  velocity = {0.0f, 0.0f};
}

void ExampleCoroutineState::SaveLevelData()
{
}

ExampleCoroutineState::Coroutine ExampleCoroutineState::SimulateBall(Ball& ball)
{
  while (ball.isFalling) {
    ball.velocity += 0.1f; // Schwerkraft
    ball.y += ball.velocity;

    // Aufprall auf den Boden
    if (ball.y > CO.H - 10) {
        ball.velocity = -ball.velocity * 0.7f; // Rückprall mit Dämpfung
        if (std::abs(ball.velocity) < 0.5f) {
            ball.isFalling = false; // Stoppen, wenn zu langsam
        }
    }

    //std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Verzögerung simulieren
    co_await std::suspend_always{};
  }
}
