#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/textbox.hpp>
#include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <game/src/render/exampleScreenElementsLevelRender.hpp>
#include <olcTemplate/game/src/render/levelRender.hpp>
#include <olcTemplate/game/sound.hpp>
using namespace stemaj;

ExampleScreenElementsLevelState::ExampleScreenElementsLevelState() : 
  _render(std::make_unique<ExampleScreenElementsLevelRender>())
{
  _fader.StartFadeIn();
  playMusic("assets/wav/1.wav");
  LoadLevelData();
}

ExampleScreenElementsLevelState::~ExampleScreenElementsLevelState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> 
  ExampleScreenElementsLevelState::ExampleScreenElementsLevelState::Update(
    const Input& input, float fElapsedTime)
{
  _textboxes.clear();
  _mousePos = PT<int>{input.mouseX, input.mouseY};

  _rect.pos = { _mousePos.x, _mousePos.y };

  if (overlaps(_rect, _circle))
  {
    _color.r = 130;
    _color.g = 130;
    _color.b = 130;
  }
  else
  {
    _color.r = 200;
    _color.g = 200;
    _color.b = 200;
  }

  std::string fontName = "CutiePatootie-Rgjv";

	// TextBox t("normal center", {input.mouseX,input.mouseY },
  //   TextBoxLocation::NORMAL, fontName, FontSize::NORMAL);
  // _textboxes.push_back(t);
	TextBox t2("big upper left", {input.mouseX,input.mouseY },
    TextBoxLocation::UPPERLEFT, fontName, FontSize::BIG );
	_textboxes.push_back(t2);
	TextBox t3("small lower right", {input.mouseX,input.mouseY },
    TextBoxLocation::LOWERRIGHT, fontName, FontSize::SMALL);
	_textboxes.push_back(t3);

  return ChangeLevel(input, fElapsedTime);
}

Render* ExampleScreenElementsLevelState::GetRender()
{
  return _render.get();
}

void ExampleScreenElementsLevelState::LoadLevelData()
{
  std::cout << "loading" << std::endl;
}

void ExampleScreenElementsLevelState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}
