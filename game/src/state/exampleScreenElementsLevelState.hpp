#ifndef __EXAMPLESCREENELEMENTSLEVELSTATE_HPP
#define __EXAMPLESCREENELEMENTSLEVELSTATE_HPP

#include "olcTemplate/game/guiElements.hpp"
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>
#include <vector>
#include <olcTemplate/game/geometryWrapper.hpp>

namespace stemaj {

class ExampleScreenElementsLevelRender;
class TextBox;

class ExampleScreenElementsLevelState : public LevelState
{
public:

  explicit ExampleScreenElementsLevelState();
  virtual ~ExampleScreenElementsLevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

  std::vector<TextBox> _textboxes;
  PT<int> _mousePos;
  
  Circle _circle = Circle({100,100}, 25);
  Rect _rect = Rect({150,150}, {20,30});
  MainMenuColor _color;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<ExampleScreenElementsLevelRender> _render;

  friend class ExampleScreenElementsLevelRender;
};

} // namespace stemaj

#endif // __EXAMPLESCREENELEMENTSLEVELSTATE_HPP

