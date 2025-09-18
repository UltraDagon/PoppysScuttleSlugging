#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../entities/TextElement.h"
#include "../entities/Poppy.h"
#include "../entities/Environment.h"
#include "../entities/Krug.h"

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
 * This scene is preceded by the ShopScene or MainMenuScene, and is followed by the ShopScene.
 */
class GameScene
{
private:
  /// Pointer to the ResourceManager that controls internally and externally saved resources.
  ResourceManager *resourceManager;
  /// Map of all buttons that allow for clickable actions on the screen.
  std::unordered_map<std::string, UIElement::ButtonData> buttons;
  /// The total gold acquired during the run.
  int goldAcquired = 0;
  /// The state of the key used for the Q ability from the last frame.
  bool prevQState = false;
  /// The ScuttleCrab entity used during the run.
  ScuttleCrab scuttleCrab;
  /// The Poppy entity used during the run.
  Poppy poppy;
  /// The floor/ground of the environment.
  Environment floor;
  /// The multiple n layers of background of the environment. 0 is furthest back, n-1 is the closest
  Environment background[1];
  /// Data for the end of run popup.
  struct
  {
    /// The speed at which the end popup moves towards the center of the camera.
    const int travelDistancePerSecond = 800; // Maybe in the future make this come in from a random position
    /// The remaining time, in seconds, until the end popup reaches the center of the screen.
    float moveInDelayRemaining = 1;
  } endPopupData;

  /// Types of monsters.
  enum class monsterTypes
  {
    KRUG
  };

  /// The cooldowns remaining before the next spawn of that monster.
  std::unordered_map<monsterTypes, float> monsterSpawnCooldowns =
      {{monsterTypes::KRUG, 1}};

  /// The vector of all living krugs.
  std::vector<Krug *> krugs;

  /**
   * Render the end screen that pops up at the end of a run.
   *
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void renderEndPopup(Renderer &renderer);

  /**
   * Render the charges available and max charges for Poppy's Q ability.
   *
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void renderQCharges(Renderer &renderer);

  /**
   * Handle any button presses that occur.
   *
   * @param input the InputHandler used to handle keyboard and mouse input from the player
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void handleButtons(InputHandler &input, Renderer &renderer);

  /**
   * Advance monster spawn cooldowns and spawn monsters once their respective cooldown is over.
   *
   * @param deltaTime the time that has elapsed since the previous frame
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void spawnMonsters(float deltaTime, Renderer &renderer);

  /**
   * Progress the physics effects of the monsters.
   *
   * @param deltaTime the time that has elapsed since the previous frame
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void monsterPhysicsStep(float &deltaTime, Renderer &renderer);

public:
  /**
   * GameScene constructor with required resourceManager reference.
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
