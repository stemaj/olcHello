#include <array>
#include <game/src/render/exampleCollisionRender.hpp>
#include <game/src/state/exampleCollisionState.hpp>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/loadsave.hpp>
#include <memory>
#include <olcTemplate/sdk/box2d/include/box2d.h>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

ExampleCollisionState::ExampleCollisionState() : _render(std::make_unique<ExampleCollisionRender>())
{
  _fader.StartFadeIn();
  LoadLevelData();
  InitValues();
}

ExampleCollisionState::~ExampleCollisionState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleCollisionState::Update(
  const Input& input, float fElapsedTime)
{
  if (input.aHold) _force.x -= _triForce;
  else if (input.dHold) _force.x += _triForce;
  else _force.x = 0;

  if (input.wHold) _force.y -= _triForce;
  else if (input.sHold) _force.y += _triForce;
  else _force.y = 0;

  b2Body* bodyListPtr = _world->GetBodyList();
  while (bodyListPtr != nullptr)
  {
    auto fixtureList = bodyListPtr->GetFixtureList();
    b2PolygonShape* shape = (b2PolygonShape*)fixtureList->GetShape();
    uintptr_t pointer = fixtureList->GetUserData().pointer;
    Identifier* id = reinterpret_cast<Identifier*>(pointer);
    if (id == nullptr)
    {
      std::cout << "Fehler beim Holen der Id\n";
      std::exit(1);
    }
    if (id->id == 2)
    {
      b2Vec2 circlePos = bodyListPtr->GetPosition();
      _circleCenter = { circlePos.x, circlePos.y };
    }
    else
    {
      if (id->id == 1)
      {
        for (int i = 0; i < shape->m_count; i++)
        {
          auto vertex = bodyListPtr->GetWorldPoint(shape->m_vertices[i]);
          _groundShape[i] = { vertex.x, vertex.y };
        }
        _groundCenter = { bodyListPtr->GetPosition().x, bodyListPtr->GetPosition().y };
        _groundAngle = bodyListPtr->GetAngle();
      }
      else if (id->id == 3)
      {
        for (int i = 0; i < shape->m_count; i++)
        {
          auto vertex = bodyListPtr->GetWorldPoint(shape->m_vertices[i]);
          _rectShape[i] = { vertex.x, vertex.y };
        }
        _rectCenter = { bodyListPtr->GetPosition().x, bodyListPtr->GetPosition().y };
        _rectAngle = bodyListPtr->GetAngle();
      }
      else if (id->id == 4)
      {
        for (int i = 0; i < shape->m_count; i++)
        {
          auto vertex = bodyListPtr->GetWorldPoint(shape->m_vertices[i]);
          _triShape[i] = { vertex.x, vertex.y };
        }
        b2Vec2 force = {_force.x * fElapsedTime,_force.y * fElapsedTime};
        _triBodyPtr->ApplyForceToCenter(force, true);
      }
    }
    bodyListPtr = bodyListPtr->GetNext();
  }

  _world->Step(fElapsedTime, _velocityIterations, _positionIterations);

#if defined(STEMAJ_DEBUG)
  ImGui::Begin("Collision Debug");
  if (ImGui::BeginListBox("Shape", ImVec2(0, (float)_triShape.size() * 25.0f)))
  {
    for (const auto& point : _triShape)
      ImGui::Text("(%f, %f)", point.x*SCALE, point.y*SCALE);
    ImGui::EndListBox();
  }
  ImGui::End();
#endif

  return RequestForMainMenu(input.escapePressed, fElapsedTime);
}

Render* ExampleCollisionState::GetRender()
{
  return _render.get();
}

void ExampleCollisionState::LoadLevelData()
{
  std::cout << "loading" << std::endl;
  
  LS.Init("scripts/exampleCollision.lua", true);
  
  SCALE = LS.Float("scale");
  
  _velocityIterations = LS.Int("velocity_iterations");
  _positionIterations = LS.Int("position_iterations");
  
  _gravityY = LS.Float("gravity_y");
  
  _groundCenter = LS.PTFloat("ground_center");
  _groundSize = LS.PTFloat("ground_size");
  _groundAngle = LS.Float("ground_angle");
  _groundType = LS.Int("ground_type");
  _groundDensity = LS.Float("ground_density");
  
  _circleCenter = LS.PTFloat("circle_center");
  _circleRadius = LS.Float("circle_radius");
  _circleType = LS.Int("circle_type");
  _circleDensity = LS.Float("circle_density");
  
  _rectCenter = LS.PTFloat("rect_center");
  _rectSize = LS.PTFloat("rect_size");
  _rectAngle = LS.Float("rect_angle");
  _rectType = LS.Int("rect_type");
  _rectDensity = LS.Float("rect_density");

  _triShape = LS.PTFloat4("tri_polygon");
  _triType = LS.Int("tri_type");
  _triDensity = LS.Float("tri_density");
  _triForce = LS.Float("tri_force");
}

void ExampleCollisionState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
  
  LS.SaveStart("exampleCollision");

  LS.SavePTFloat4("tri_polygon", _triShape);
  
  LS.SaveEnd();
}

void ExampleCollisionState::InitValues()
{
  // Box2D World setup
  b2Vec2 gravity(0.0f, _gravityY);
  _world = std::make_unique<b2World>(gravity);

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(_groundCenter.x, _groundCenter.y);
  groundBodyDef.type = (b2BodyType)_groundType;
  groundBodyDef.angle = _groundAngle;
  groundBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(&_idGround);
  b2Body* groundBody = _world->CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(_groundSize.x, _groundSize.y);
  b2FixtureDef groundFixtureDef;
  groundFixtureDef.density = _groundDensity;
  groundFixtureDef.friction = 0.3f; // Beispiel-Reibung je hoeher desto groessere Haftung 
  groundFixtureDef.restitution = 0.5f; // Bounciness, je hoeher desto staerker Bounce
  groundFixtureDef.shape = &groundBox;
  groundFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&_idGround);
  groundBody->CreateFixture(&groundFixtureDef);

  b2BodyDef circleBodyDef;
  circleBodyDef.type = (b2BodyType)_circleType;
  circleBodyDef.position.Set(_circleCenter.x, _circleCenter.y);
  b2Body* circleBody = _world->CreateBody(&circleBodyDef);
  b2CircleShape circleShape;
  circleShape.m_radius = _circleRadius;
  b2FixtureDef circleFixtureDef;
  circleFixtureDef.density = _circleDensity;
  circleFixtureDef.shape = &circleShape;
  circleFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&_idCircle);
  circleBody->CreateFixture(&circleFixtureDef);

  b2BodyDef rectBodyDef;
  rectBodyDef.type = (b2BodyType)_rectType;
  rectBodyDef.position.Set(_rectCenter.x, _rectCenter.y);
  rectBodyDef.angle = _rectAngle;
  b2Body* rectBody = _world->CreateBody(&rectBodyDef);
  b2PolygonShape rectShape;
  rectShape.SetAsBox(_rectSize.x, _rectSize.y);
  b2FixtureDef rectFixtureDef;
  rectFixtureDef.density = _rectDensity;
  rectFixtureDef.shape = &rectShape;
  rectFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&_idRect);
  rectBody->CreateFixture(&rectFixtureDef);

  b2BodyDef triBodyDef;
  triBodyDef.type = (b2BodyType)_triType;
  triBodyDef.linearDamping = 100.0f; // Keine Daempfung
  _triBodyPtr = _world->CreateBody(&triBodyDef);
  b2PolygonShape triShape;
  const size_t triSize = _triShape.size();
  b2Vec2* triVec = new b2Vec2[triSize]();
  for (int i = 0; i < _triShape.size(); i++)
  {
    triVec[i].Set(_triShape[i].x, _triShape[i].y);
  }
  triShape.Set(triVec, _triShape.size());
  delete[] triVec;
  b2FixtureDef triFixtureDef;
  triFixtureDef.density = _triDensity;
  triFixtureDef.shape = &triShape;
  triFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&_idTri);
  _triBodyPtr->SetGravityScale(0);
  _triBodyPtr->CreateFixture(&triFixtureDef);
}
