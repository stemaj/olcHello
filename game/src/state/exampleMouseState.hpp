#ifndef __EXAMPLEMOUSESTATE_HPP
#define __EXAMPLEMOUSESTATE_HPP

#include <cstdint>
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>

namespace olc {
  class Decal;
  namespace QuickGUI {
    class Manager;
  }
}

namespace stemaj {

class ExampleMouseRender;

class ExampleMouseState : public LevelState
{
public:

  enum Tap : uint8_t
  {
    TAP_NO = 0,
    TAP_BEGIN = 1,
    TAP_HELD = 2,
    TAP_END = 3
  };

  explicit ExampleMouseState();
  virtual ~ExampleMouseState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  sol::state _lua;
  std::unique_ptr<ExampleMouseRender> _render;

  PT<int> _tapPos;
  Tap _tap = Tap::TAP_NO;
  Tap _tapR = Tap::TAP_NO;

  std::unique_ptr<olc::QuickGUI::Manager> _guiManager;

  friend class ExampleMouseRender;
};

} // namespace stemaj

#endif // __EXAMPLEMOUSESTATE_HPP

