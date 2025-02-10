#ifndef __EXAMPLECOROUTINERENDER_HPP
#define __EXAMPLECOROUTINERENDER_HPP

#include <olcTemplate/game/src/render/levelRender.hpp>

namespace stemaj {

class ExampleCoroutineRender : public LevelRender
{
public:
  explicit ExampleCoroutineRender() {}
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;

 
};

} // namespace stemaj

#endif // __EXAMPLECOROUTINERENDER_HPP
