#ifndef __EXAMPLEMOUSERENDER_HPP
#define __EXAMPLEMOUSERENDER_HPP

#include <memory>
#include <olcTemplate/game/src/render/levelRender.hpp>

namespace olc {
  class Renderable;
  namespace QuickGUI {
    class BaseControl;
  }
}

namespace stemaj {

using RenderedControl = std::unique_ptr<olc::QuickGUI::BaseControl>;

class ExampleMouseRender : public LevelRender
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;

private:
  RenderedControl _backControl;
};

} // namespace stemaj

#endif // __EXAMPLEMOUSERENDER_HPP