#include "GameScene.h"
#include "ShopScene.h"
#include "MainMenuScene.h"

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

/**
 * Scene manager for determining what scene to render and run physics for.
 *
 * Switching scenes saves data/loads data within the resourceManager,
 * deletes the previous scene, and flushes the image cache.
 */
class SceneManager
{
private:
  /// The current scene that the user is on.
  char activeScene; // todo: Should be enum
  /// Pointer to the MainMenuScene
  std::unique_ptr<MainMenuScene> mainMenuScene;
  /// Pointer to the GameScene
  std::unique_ptr<GameScene> gameScene;
  /// Pointer to the ShopScene
  std::unique_ptr<ShopScene> shopScene;
  /// Pointer to the Renderer that controls the window rendering and camera
  Renderer *renderer;
  /// Pointer to the ResourceManager that controls internally and externally saved resources.
  ResourceManager *resourceManager;

public:
  /**
   * SceneManager constructor.
   *
   * @param activeScene the initial scene
   * @param renderer_ the Renderer that controls the window rendering and camera
   * @param resManager the ResourceManager that controls internally and externally saved resources
   */
  SceneManager(char activeScene, Renderer &renderer_, ResourceManager &resManager);

  /// SceneManager destructor.
  ~SceneManager();

  /**
   * Change the current scene.
   *
   * @param activeScene_ the new scene
   */
  void setScene(char activeScene_);

  /**
   * Render all entities and advance all physics effects for the current scene.
   *
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void render(Renderer &renderer, InputHandler &inputHandler);

  /**
   * Get the current scene.
   *
   * @return the char representing the current scene
   */
  char getActiveScene();
};

#endif // SCENEMANAGER_H