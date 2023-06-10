#include <memory>
#include <cassert>

#include "GameManager.hpp"
#include "GameWorld.hpp"
#include "ObjectBase.hpp"




int main(int argc, char** argv) {
  std::shared_ptr<WorldBase> world = std::make_shared<GameWorld>();

  assert(world->GetSun() == 50);
  assert(world->GetWave() == 0);
  assert(ObjectBase::GetObjects(LAYER_BACKGROUND).size() >= 1);
  assert(ObjectBase::GetObjects(LAYER_UI).size() >= 45);


  GameManager::Instance().Play(argc, argv, world);
}