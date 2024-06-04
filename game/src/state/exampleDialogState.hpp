#ifndef __EXAMPLEDIALOGSTATE_HPP
#define __EXAMPLEDIALOGSTATE_HPP

#include <game/src/state/levelState.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <olcTemplate/sdk/sol2-3.3.0/sol.hpp>

namespace stemaj {

class ExampleDialogRender;

class ExampleDialogState : public LevelState
{
public:
  explicit ExampleDialogState();
  virtual ~ExampleDialogState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  sol::state _lua;
  std::unique_ptr<ExampleDialogRender> _render;

  friend class ExampleDialogRender;
};

} // namespace stemaj

#endif // __EXAMPLEDIALOGSTATE_HPP

