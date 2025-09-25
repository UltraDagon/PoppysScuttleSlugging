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

void MainMenuScene::renderLegalBoilerplate(Renderer &renderer)
{
  const int charSize = 18;

  TextElement(legalBoilerplate.substr(0, 86), {-renderer.getWindowWidth() / 2, (charSize * 1.25) * -3 - 16 + renderer.getWindowHeight() / 2}, charSize, TextElement::TextAlignment::LEFT).render(renderer), 8;
  TextElement(legalBoilerplate.substr(87, 89), {-renderer.getWindowWidth() / 2, (charSize * 1.25) * -2 - 16 + renderer.getWindowHeight() / 2}, charSize, TextElement::TextAlignment::LEFT).render(renderer), 8;
  TextElement(legalBoilerplate.substr(176, 82), {-renderer.getWindowWidth() / 2, (charSize * 1.25) * -1 - 16 + renderer.getWindowHeight() / 2}, charSize, TextElement::TextAlignment::LEFT).render(renderer), 8;
  TextElement(legalBoilerplate.substr(259, 31), {-renderer.getWindowWidth() / 2, -16 + renderer.getWindowHeight() / 2}, charSize, TextElement::TextAlignment::LEFT).render(renderer), 8;
}

MainMenuScene::MainMenuScene(ResourceManager &resManager)
{
  resourceManager = &resManager;
}

void MainMenuScene::render(Renderer &renderer)
{
  UIElement playButton({440, -150}, {525, 125}, "wooden_sign.bmp");
  playButton.animationData.frameSize = {400, 200}; // todo: Remove once poppy upgrade board image is done

  const std::pair<int, int> playButtonAbsPos = playButton.absolutePosition();
  buttons["g"] = {playButtonAbsPos.first, playButtonAbsPos.second, playButton.size.first, playButton.size.second, buttons["g"].state, UIElement::ButtonType::SCENE_NAVIGATION};

  UIElement({-350, 0}, {700, 700}, "pss_title.bmp").render(renderer);
  playButton.render(renderer);
  TextElement("PLAY GAME", {0, 0}, 60, TextElement::TextAlignment::CENTER, 8, &playButton).render(renderer);
  renderLegalBoilerplate(renderer);
}

void MainMenuScene::physicsStep(InputHandler &input, Renderer &renderer)
{
  handleButtons(input, renderer);
}