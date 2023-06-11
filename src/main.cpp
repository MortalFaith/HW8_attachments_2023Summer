#include <memory>
#include <cassert>

#include "GameManager.hpp"
#include "GameWorld.hpp"
#include "ObjectBase.hpp"




int main(int argc, char** argv) {
  std::shared_ptr<WorldBase> world = std::make_shared<GameWorld>();


  GameManager::Instance().Play(argc, argv, world);
}