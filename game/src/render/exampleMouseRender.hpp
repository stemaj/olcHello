#ifndef __EXAMPLEMOUSERENDER_HPP
#define __EXAMPLEMOUSERENDER_HPP

#include <olcTemplate/game/src/render/levelRender.hpp>

namespace stemaj {

class ExampleMouseRender : public LevelRender
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
};

} // namespace stemaj

#endif // __EXAMPLEMOUSERENDER_HPP