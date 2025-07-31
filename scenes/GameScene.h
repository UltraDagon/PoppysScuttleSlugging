#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../entities/TextElement.h"
#include "../entities/Poppy.h"
#include "../entities/Environment.h"

// #include "../ImageCache.h" // Included by Sprite.h included by Renderer.h
#include "../Renderer.h"
#include "../ResourceManager.h"
#include "../InputHandler.h"

/**
 * The GameScene is where the main gameplay happens, and is how the player obtains gold.
 *
 * Upgrades from the shop, Poppy's minigames, and encounters made during the
 * Scuttle Crab's flight all affect the final gold gained at the end.
 *
 * This scene is preceded by the ShopScene, and is followed by the ShopScene.
 */
class GameScene
{
private:
  ResourceManager *resourceManager;

  std::unordered_map<std::string, UIElement::ButtonData> buttons;

  /// The ScuttleCrab entity used during the run.
  ScuttleCrab scuttleCrab;
  /// The Poppy entity used during the run.
  Poppy poppy;
  /// The floor/ground of the environment.
  Environment floor;
  /// Data for the end of run popup.
  struct
  {
    const int travelDistancePerSecond = 800; // Maybe in the future make this come in from a random position
    float moveInDelayRemaining = 1;
  } endPopupData;

  void renderEndPopup(Renderer &renderer);

  /**
   * Handle any button presses that occur.
   *
   * @param input the InputHandler used to handle keyboard and mouse input from the player
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void handleButtons(InputHandler &input, Renderer &renderer);

public:
  /**
   * GameScene constructor with required resourceManager reference
   *
   * @param resManager the ResourceManager that controls internally and externally saved resources
   */
  GameScene(ResourceManager &resManager);

  /// GameScene destructor.
  ~GameScene();

  /**
   * Render all entities in the scene.
   *
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void render(Renderer &renderer);

  /**
   * Progress the physics effects of the entities within the GameScene.
   *
   * @param deltaTime the time that has elapsed since the previous frame
   * @param input the InputHandler used to handle keyboard and mouse input from the player
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void physicsStep(float deltaTime, InputHandler &input, Renderer &renderer);
};

#endif // GAMESCENE_H
