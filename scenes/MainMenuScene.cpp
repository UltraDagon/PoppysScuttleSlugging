#include "MainMenuScene.h"

void MainMenuScene::handleButtons(InputHandler &input, Renderer &renderer)
{
  for (auto &b : buttons)
  {
    b.second.updateState(input.mouseX - renderer.getWindowWidth() / 2, input.mouseY - renderer.getWindowHeight() / 2, input.mouseState & SDL_BUTTON_LMASK);
    if (b.second.state != 'c') // If button isn't clicked
      continue;

    // Handle the button being clicked
    switch (b.second.type)
    {
    case UIElement::ButtonType::SCENE_NAVIGATION:
      resourceManager->changeScene(b.first.at(0)); // Change scene to first char in scene name
      break;
    default:
      break;
    }
  }
}

MainMenuScene::MainMenuScene(ResourceManager &resManager)
{
  resourceManager = &resManager;
}

void MainMenuScene::render(Renderer &renderer)
{
  UIElement gameTitle({0, -200}, {1000, 450}, "poppy.bmp");
  UIElement playButton({0, 150}, {525, 125}, "upgrade_button.bmp");
  TextElement playText("PLAY GAME", {0, 0}, 60, TextElement::TextAlignment::CENTER, 8, &playButton);

  const std::pair<int, int> playButtonAbsPos = playButton.absolutePosition();
  buttons["g"] = {playButtonAbsPos.first, playButtonAbsPos.second, playButton.size.first, playButton.size.second, buttons["g"].state, UIElement::ButtonType::SCENE_NAVIGATION};

  gameTitle.render(renderer);
  playButton.render(renderer);
  playText.render(renderer);
}

void MainMenuScene::physicsStep(InputHandler &input, Renderer &renderer)
{
  handleButtons(input, renderer);
}