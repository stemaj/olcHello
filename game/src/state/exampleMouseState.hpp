#ifndef __EXAMPLEMOUSESTATE_HPP
#define __EXAMPLEMOUSESTATE_HPP

#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>

namespace olc {
  class Decal;
}

namespace stemaj {

class ExampleMouseRender;

class ExampleMouseState : public LevelState
{
public:
  explicit ExampleMouseState();
  virtual ~ExampleMouseState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  sol::state _lua;
  std::unique_ptr<ExampleMouseRender> _render;

  friend class ExampleMouseRender;
};

} // namespace stemaj

#endif // __EXAMPLEMOUSESTATE_HPP

