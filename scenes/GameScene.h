#ifndef GAMESCENE_H
#define GAMESCENE_H

// #include "../entities/Entity.h" // Included by ScuttleCrab.h
// #include "../entities/ScuttleCrab.h" // Included by Poppy.h
#include "../entities/Poppy.h"
#include "../entities/Environment.h"

// #include "../ImageCache.h" // Included by Sprite.h included by Renderer.h
#include "../Renderer.h"

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
  /// The ScuttleCrab entity used during the run.
  ScuttleCrab scuttleCrab;
  /// The Poppy entity used during the run.
  Poppy poppy;
  /// The floor/ground of the environment.
  Environment floor;

public:
  /// GameScene constructor.
  GameScene();

  /// GameScene destructor.
  ~GameScene(); // Currently Empty

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
   * @param camera the Camera used to render the world
   */
  void physicsStep(float deltaTime, Camera &camera);
};

#endif
