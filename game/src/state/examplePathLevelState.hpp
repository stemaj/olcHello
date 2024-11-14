#ifndef __EXAMPLEPATHLEVELSTATE_HPP
#define __EXAMPLEPATHLEVELSTATE_HPP

#include "olcTemplate/game/guiElements.hpp"
#include <olcTemplate/game/coordinates.hpp>
#include <olcTemplate/game/src/state/levelState.hpp>
#include <olcTemplate/game/src/tools/pathfollower.hpp>

namespace stemaj {

class ExamplePathLevelRender;

class ExamplePathLevelState : public LevelState
{
 const int _speed = 300;

public:
  explicit ExamplePathLevelState();
  virtual ~ExamplePathLevelState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;
private:

  // dynamic values
  std::vector<PT<int>> _path;
  PT<int> _obj;
  PT<int> _end;

  // values to init
  std::vector<std::pair<PT<int>, bool>> _grid;

  // input
  PT<int> _gridDimension;
  PT<float> _objSource;
  std::vector<PT<float>> _polygonSource;


  MainMenuColor _colorBackground;
  MainMenuColor _colorObject;
  MainMenuColor _colorStart;
  MainMenuColor _colorEnd;
  MainMenuColor _colorPath;
  MainMenuColor _colorPolygon;

  Pathfollower _pathFollower;

  void InitValues();
  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<ExamplePathLevelRender> _render;

  friend class ExamplePathLevelRender;
};

} // namespace stemaj

#endif // __EXAMPLEPATHLEVELSTATE_HPP