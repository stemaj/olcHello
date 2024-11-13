#ifndef __EXAMPLEWALKLEVELRENDER_HPP
#define __EXAMPLEWALKLEVELRENDER_HPP

#include <olcTemplate/game/src/render/levelRender.hpp>

namespace stemaj {

class ExampleWalkLevelRender : public LevelRender
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;

  float cumulativeAngle = 0.0f; // Variable für den stetig zunehmenden Winkel

};

} // namespace stemaj

#endif // __EXAMPLEWALKLEVELRENDER_HPP