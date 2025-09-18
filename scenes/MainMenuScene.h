#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "../entities/TextElement.h"

#include "../Renderer.h"
#include "../ResourceManager.h"
#include "../InputHandler.h"

/**
 * The MainMenuScene is the scene that can be used to play the game or adjust any settings.
 *
 * This scene is preceded by launching the game or the ShopScene, and is followed by the GameScene.
 */
class MainMenuScene
{
private:
  /// The legal boilerplate needed for a product that uses Riot Game's IP.
  const std::string legalBoilerplate = "Poppy's Scuttle Slugging isn't endorsed by Riot Games and doesn't reflect the views or opinions of Riot Games or anyone officially involved in producing or managing Riot Games properties. Riot Games, and all associated properties are trademarks or registered trademarks of Riot Games, Inc.";
  /// Pointer to the ResourceManager that controls internally and externally saved resources.
  ResourceManager *resourceManager;
  /// Map of all buttons that allow for clickable actions on the screen.
  std::unordered_map<std::string, UIElement::ButtonData> buttons;

  /**
   * Handle any button presses that occur.
   *
   * @param input the InputHandler used to handle keyboard and mouse input from the player
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void handleButtons(InputHandler &input, Renderer &renderer);

  /**
   * Render the legal boilerplate text.
   *
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void renderLegalBoilerplate(Renderer &renderer);

public:
  /**
   * MainMenuScene constructor with required resourceManager reference
   *
   * @param resManager the ResourceManager that controls internally and externally saved resources
   */
  MainMenuScene(ResourceManager &resManager);

  /**
   * Render the MainMenuScene.
   *
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void render(Renderer &renderer);

  /**
   * Progress the animation and input effects of the MainMenuScene
   *
   * @param input the InputHandler used to handle keyboard and mouse input from the player
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void physicsStep(InputHandler &input, Renderer &renderer);
};

#endif // MAINMENUSCENE_H