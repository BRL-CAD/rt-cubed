#ifndef __SCENEFACTORY_H__
#define __SCENEFACTORY_H__

// system headers
#include <iostream>
#include <vector>

// interface headers
#include "Scene.h"

namespace Geometry {

  class SceneFactory
  {
  private:
    Scene *_scene;

    static bool noCaseCompare(char c1, char c2) {
      return toupper(c1) == toupper(c2);
    }

  protected:
    std::vector<std::string> _filesLoaded;

  public:
    SceneFactory(std::string filename = "");
    ~SceneFactory();

    bool loadFromFile(std::string filename);

    Scene* getScene() {
      return _scene;
    }
  };

}

#endif  /* __SCENEFACTORY_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
