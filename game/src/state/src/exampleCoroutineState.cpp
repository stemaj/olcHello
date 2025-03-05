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

  // Bewegung des Punktes zum Endpunkt
  float dx = _endX - _posX;
  float dy = _endY - _posY;
  float dz = _endZ - _posZ;
  float distance = _room3d->Distance(_posX, _posY, _posZ, _endX, _endY, _endZ);
  if (distance > 1.0f)
  {
    // Stoppen, wenn nahe genug
    float norm = sqrtf(dx * dx + dy * dy + dz * dz);
    if (norm > 0.0f)
    {
      dx /= norm;
      dy /= norm;
      dz /= norm;
    }
    _posX += dx * _speed * fElapsedTime;
    _posY += dy * _speed * fElapsedTime;
    _posZ += dz * _speed * fElapsedTime;
  }

  // Kreisgröße anpassen basierend auf der Z-Koordinate (je näher, desto größer)
  factorCircleSize = 1.0f + (1.0f - ((_posZ - _minZ) / (_maxZ - _minZ))) * 40.0f;
  if (factorCircleSize < 1.0f) factorCircleSize = 1.0f;

  objPos = _room3d->Project(_posX, _posY, _posZ);

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
