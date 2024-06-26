#ifndef __EXAMPLECOLLISIONRENDER_HPP
#define __EXAMPLECOLLISIONRENDER_HPP

#include <olcTemplate/game/src/render/levelRender.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <memory>

namespace stemaj {

class ExampleCollisionRender : public LevelRender
{
public:
  explicit ExampleCollisionRender();
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;

private:
  std::unique_ptr<olc::Renderable> _rGround;
  std::unique_ptr<olc::Renderable> _rRect;
  std::unique_ptr<olc::Renderable> _rTri;
};

} // namespace stemaj

#endif // __EXAMPLECOLLISIONRENDER_HPP
