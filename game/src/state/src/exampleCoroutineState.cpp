#include <game/src/render/exampleCoroutineRender.hpp>
#include <game/src/state/exampleCoroutineState.hpp>
#include <olcTemplate/game/room3d.hpp>

using namespace stemaj;

ExampleCoroutineState::ExampleCoroutineState() : _render(std::make_unique<ExampleCoroutineRender>())
{
  _room3d = std::make_unique<Room3d>();
  LoadLevelData();
}

ExampleCoroutineState::~ExampleCoroutineState()
{
  SaveLevelData();
}

PT<int> ExampleCoroutineState::ProjectedPos() const
{
  return _room3d->Projected(_pos[0], _pos[1], _pos[2]);
}

std::optional<std::unique_ptr<State>> ExampleCoroutineState::Update(
  const Input& input, float fElapsedTime)
{
  // Kamera-Steuerung
  if (input.aHold) _room3d->MoveCamX(-fElapsedTime);
  if (input.dHold) _room3d->MoveCamX(+fElapsedTime);
  if (input.sHold) _room3d->MoveCamY(-fElapsedTime);
  if (input.wHold) _room3d->MoveCamY(+fElapsedTime);
  if (input.pgDownHold) _room3d->MoveCamZ(-fElapsedTime);
  if (input.pgUpHold) _room3d->MoveCamZ(+fElapsedTime);

  // "Bump"-Effekt starten
  if (input.leftMouseReleased && !_room3d->isBumping)
  {
    _room3d->StartBumpEffect( PT<float>{input.mouseX - P1.x, input.mouseY - P1.y} );
  }

  _room3d->UpdateBumpEffect(fElapsedTime);

  _room3d->Debug();


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

  if (input.leftMouseReleased)
  {
    _endX = 100.0f;
    _endY = 2000.0f;
    _endZ = 5000.0f;
    _speed = 5000.0f;
  }

  _pos = _room3d->MoveObject(_pos, {_endX,_endY,_endZ}, _speed, fElapsedTime);
  objPos = _room3d->Projected(_pos[0], _pos[1], _pos[2]);

  factorCircleSize = _room3d->ObjectSizeFactor(_pos[2]);

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
