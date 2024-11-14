#ifndef __EXAMPLEMOUSESTATE_HPP
#define __EXAMPLEMOUSESTATE_HPP

#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>

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
  std::unique_ptr<ExampleMouseRender> _render;

  PT<int> _tapPos;
  Tap _tap = Tap::TAP_NO;
  Tap _tapR = Tap::TAP_NO;

  Tap _tapBack = TAP_NO;

  friend class ExampleMouseRender;
};

} // namespace stemaj

#endif // __EXAMPLEMOUSESTATE_HPP

