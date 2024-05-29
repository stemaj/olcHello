#ifndef __EXAMPLEPATHLEVELRENDER_HPP
#define __EXAMPLEPATHLEVELRENDER_HPP

#include <olcTemplate/game/src/render/levelRender.hpp>

namespace stemaj {

class ExamplePathLevelRender : public LevelRender
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
};

} // namespace stemaj

#endif // __EXAMPLEPATHLEVELRENDER_HPP