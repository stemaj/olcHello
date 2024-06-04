#include <game/src/state/exampleDialogState.hpp>
#include <game/src/render/exampleDialogRender.hpp>
#include <memory>

using namespace stemaj;

ExampleDialogState::ExampleDialogState() : _render(std::make_unique<ExampleDialogRender>())
{
  _fader.StartFadeIn();
  LoadLevelData();
}

ExampleDialogState::~ExampleDialogState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleDialogState::Update(
  const Input& input, float fElapsedTime)
{
  if (currentNode < dialogNodes.size())
  {
    elapsedTime += fElapsedTime;

    DialogNode &node = dialogNodes[currentNode];

    if (!displayingOptions && elapsedTime > node.duration) {
        if (!node.options.empty()) {
            displayingOptions = true;
        } else {
            currentNode = node.next;
            elapsedTime = 0.0f;
        }
    }

    if (displayingOptions && input.leftMouseClicked) {
        currentNode = node.options[0].second;
        displayingOptions = false;
        elapsedTime = 0.0f;
    }
    if (displayingOptions && input.spacePressed) {
        currentNode = node.options[1].second;
        displayingOptions = false;
        elapsedTime = 0.0f;
    }
  }

  return ChangeLevel(input, fElapsedTime);
}

Render* ExampleDialogState::GetRender()
{
  return _render.get();
}

void ExampleDialogState::LoadLevelData()
{
  std::cout << "loading" << std::endl;

  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		lua.safe_script_file("scripts/exampleDialog.lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  sol::table dialog = lua["dialog"];
  for (size_t i = 1; i <= dialog.size(); ++i) {
      sol::table node = dialog[i];
      DialogNode dialogNode;
      dialogNode.speaker = node["speaker"];
      dialogNode.text = node["text"];
      dialogNode.duration = node["duration"];
      if (node["next"].valid()) {
          dialogNode.next = node["next"];
      }

      if (node["options"].valid()) {
          sol::table options = node["options"];
          for (size_t j = 1; j <= options.size(); ++j) {
              sol::table option = options[j];
              dialogNode.options.emplace_back(option["text"], option["next"]);
          }
      }
      dialogNodes.push_back(dialogNode);
  }
}

void ExampleDialogState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}
