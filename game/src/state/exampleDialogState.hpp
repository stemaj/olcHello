#ifndef __EXAMPLEDIALOGSTATE_HPP
#define __EXAMPLEDIALOGSTATE_HPP

#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/tools/dialog.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>

namespace stemaj {

class Render;
class ExampleDialogRender;

class ExampleDialogState : public LevelState
{
public:
  explicit ExampleDialogState();
  virtual ~ExampleDialogState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

  Dialog _dialog;
  void Select(int i) { _dialog._selection = i; }

  PT<int> _mousePos;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<ExampleDialogRender> _render;
};

} // namespace stemaj

#endif // __EXAMPLEDIALOGSTATE_HPP

