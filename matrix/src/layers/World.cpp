#include "matrix/src/layers/World.h"

namespace MX
{
  World &World::get()
  {
    static World instance;
    return instance;
  }

  void World::initialize()
  {
    m_ActiveScene->initialize();
  }

  void World::update()
  {
    m_ActiveScene->update();
  }

  void World::render()
  {
    m_ActiveScene->render();
  }

  void World::push(Scene *Scene)
  {
    m_ExistingScenes.push_back(Scene);
    MX_INFO("MX: World: Scene: " + Scene->m_Name + ": Added");
  }

  void World::pop(const std::string &name)
  {
    for (unsigned int i = 0; i < m_ExistingScenes.size(); i++)
    {
      if (m_ExistingScenes.at(i)->m_Name == name)
      {
        delete m_ExistingScenes.at(i);
        try 
        {
          m_ExistingScenes.erase(m_ExistingScenes.begin() + i);
        }
        catch (std::exception e)
        {
          MX_FATAL(e.what());
        }

        MX_WARN("MX: World: Scene " + m_ExistingScenes.at(i)->m_Name + ": Deleted");
      }
    }
  }
}