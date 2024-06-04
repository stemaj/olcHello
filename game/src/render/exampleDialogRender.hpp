#ifndef __EXAMPLEWALKLEVELRENDER_HPP
#define __EXAMPLEWALKLEVELRENDER_HPP

#include <olcTemplate/game/src/render/levelRender.hpp>

namespace stemaj {

class ExampleDialogRender : public LevelRender
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
};

} // namespace stemaj

#endif // __EXAMPLEWALKLEVELRENDER_HPP