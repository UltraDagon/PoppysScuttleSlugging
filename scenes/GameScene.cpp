#include "GameScene.h"

void GameScene::renderEndPopup(Renderer &renderer)
{
  // TODO: refactor to class().render()
  UIElement endPopup({renderer.getCameraPos().first, endPopupData.travelDistancePerSecond * endPopupData.moveInDelayRemaining}, {1200, 675}, "poppy.bmp");
  TextElement goldEarnedText("GOLD EARNED: " + std::to_string(goldAcquired), {0, 80}, 50, TextElement::TextAlignment::CENTER, 8, &endPopup);
  UIElement shopButton({0, endPopup.size.second / 2 - 102}, {525, 125}, "upgrade_button.bmp", &endPopup);
  TextElement visitShopText("VISIT SHOP", {0, 0}, 60, TextElement::TextAlignment::CENTER, 8, &shopButton);

  const std::pair<int, int> shopButtonAbsPos = shopButton.absolutePosition();
  buttons["s"] = {shopButtonAbsPos.first, shopButtonAbsPos.second, shopButton.size.first, shopButton.size.second, buttons["s"].state, UIElement::ButtonType::SCENE_NAVIGATION};

  endPopup.render(renderer);
  TextElement("RUN OVER", {0, 160 - endPopup.size.second / 2}, 120, TextElement::TextAlignment::CENTER, 8, &endPopup).render(renderer);
  TextElement("DISTANCE TRAVELED: 999M", {0, -20}, 50, TextElement::TextAlignment::CENTER, 8, &endPopup).render(renderer);
  goldEarnedText.render(renderer);
  shopButton.render(renderer);
  visitShopText.render(renderer);
}

void GameScene::renderQCharges(Renderer &renderer)
{
  const int startX = 60 - renderer.getWindowWidth() / 2 + renderer.getCameraPos().first;
  const int startY = 60 * (scuttleCrab.maxChargesQ - 1) / 2 + renderer.getCameraPos().second;
  float partialCharge = scuttleCrab.chargesQ - std::floor(scuttleCrab.chargesQ);
  UIElement charge;

  for (int i = 0; i < scuttleCrab.maxChargesQ; i++)
  {
    // Maybe define charge here and then just change animation for each part.
    if (scuttleCrab.chargesQ >= i + 1) // Charge fully available
      charge = UIElement({startX, startY - i * 60}, {40, 40}, "icon_q.bmp");
    else if (scuttleCrab.chargesQ <= i) // Charge fully unavailable
      charge = UIElement({startX, startY - i * 60}, {40, 40}, "icon_q_gray.bmp");
    else // Partially charged (i < charges < i+1)
    {
      UIElement({startX, startY - i * 60}, {40, 40}, "icon_q_gray.bmp").render(renderer); // Render unavailable charge icon behind partial charge
      charge = UIElement({startX, startY - i * 60 + 20 * (1 - partialCharge)}, {40, 40 * partialCharge}, "icon_q.bmp");
      charge.animationData.frameSize = {120, 120 * partialCharge};
      charge.animationData.animation = 1 / partialCharge - 1;
    }

    charge.render(renderer);
  }
}

void GameScene::handleButtons(InputHandler &input, Renderer &renderer)
{
  for (auto &b : buttons)
  {
    b.second.updateState(renderer.getCameraPos().first + input.mouseX - renderer.getWindowWidth() / 2, input.mouseY - renderer.getWindowHeight() / 2, input.mouseState & SDL_BUTTON_LMASK);
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

void GameScene::spawnMonsters(float deltaTime, Renderer &renderer)
{
  if (!scuttleCrab.active || scuttleCrab.bouncesRemaining <= 0)
    return;

  int spawnX = renderer.getCameraPos().first + renderer.getWindowWidth() / 2 + 200;
  int spawnY = WORLD_FLOOR_Y;

  int monsterLevel;
  for (auto m : monsterSpawnCooldowns)
  {
    monsterSpawnCooldowns[m.first] -= deltaTime;
    if (monsterSpawnCooldowns[m.first] <= 0)
    {
      switch (m.first)
      {
      case monsterTypes::KRUG:
        monsterLevel = resourceManager->getNumberResource("saveData", "krug_level");

        if (monsterLevel <= 0)
        {
          monsterSpawnCooldowns[m.first] = 9999;
        }
        else // Only spawn if krug is higher than level 0
        {
          krugs.insert(krugs.begin(), new Krug({spawnX, spawnY}, monsterLevel));
          monsterSpawnCooldowns[m.first] = krugs[0]->getSpawnDelay();
        }
        break;
      default:
        monsterSpawnCooldowns[m.first] = 5;
        break;
      }
    }
  }
}

void GameScene::monsterPhysicsStep(float &deltaTime)
{
  for (int i = 0; i < krugs.size(); ++i)
  {
    Krug *k = krugs[i];
    k->physicsStep(deltaTime);
    // If crab and krug collide
    if ((scuttleCrab.position.second + scuttleCrab.size.second - scuttleCrab.hitboxThinning > k->position.second + k->size.second) &&
        (abs(k->position.first - scuttleCrab.position.first) < k->size.first / 2 + scuttleCrab.size.first / 2 - scuttleCrab.hitboxThinning))
    {
      k->kill(goldAcquired, scuttleCrab.chargesQ, scuttleCrab.bouncesRemaining);
      delete k;
      krugs.erase(krugs.begin() + i);
      --i;
      scuttleCrab.bounce();
      scuttleCrab.velocity.second = 30 + scuttleCrab.velocity.second * 1.5;
    }

    // todo: If krug is off screen behind (to the left of) the scuttle crab
  }
}

GameScene::GameScene(ResourceManager &resManager)
{
  floor = Environment(std::pair<float, float>{0, WORLD_FLOOR_Y + 15}, std::pair<int, int>{200, 30}, 0);

  resourceManager = &resManager;
  poppy.updateLevels(resourceManager->getNumberResource("saveData", "r_level"));
  poppy.crab = &scuttleCrab;
}

GameScene::~GameScene()
{
  for (auto k : krugs)
  {
    delete k;
  }
}

void GameScene::render(Renderer &renderer)
{
  if (poppy.stage == 'S') // Focus camera on the scuttle crab when it is flying
    renderer.focusCameraLeft(scuttleCrab.position);
  else // Otherwise, focus the camera on Poppy
    renderer.focusCameraLeft(poppy.position);

  floor.render(renderer);
  for (auto k : krugs)
    k->render(renderer);
  scuttleCrab.render(renderer);
  poppy.render(renderer); // Maybe dont render poppy if out of frame? It probably won't effect performance too much
  renderQCharges(renderer);
  renderEndPopup(renderer);
}

void GameScene::physicsStep(float deltaTime, InputHandler &input, Renderer &renderer)
{
  handleButtons(input, renderer);
  poppy.stageStep(deltaTime, renderer.getCamera());

  if (input.keysPressed['q'] && !prevQState)
    scuttleCrab.abilityQ();
  prevQState = input.keysPressed['q'];

  scuttleCrab.physicsStep(deltaTime);
  monsterPhysicsStep(deltaTime);
  spawnMonsters(deltaTime, renderer);

  if (scuttleCrab.bouncesRemaining <= 0 && endPopupData.moveInDelayRemaining > 0)
  {
    endPopupData.moveInDelayRemaining -= deltaTime;
    if (endPopupData.moveInDelayRemaining < 0)
      endPopupData.moveInDelayRemaining = 0;
  }

  if (scuttleCrab.position.second * -1 > maxHeight)
  {
    // Todo: remove this and the maxHeight variable if it is unused
    maxHeight = scuttleCrab.position.second * -1;
  }
}