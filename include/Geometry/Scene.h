#ifndef __SCENE_H__
#define __SCENE_H__

#include <iostream>
#include <vector>

#include "Geometry/Triangle.h"
#include "Geometry/View.h"


namespace Geometry {

  class Scene
  {
  private:
  protected:
    std::vector<Triangle*> _geometry;
    std::vector<View*> _views;
  public:
    Scene();
    ~Scene();

    void add(Scene& scene);
    void add(std::vector<Triangle*> geometry);
    void add(std::vector<View*> views);
    std::vector<Triangle*> getGeometry() const;
    std::vector<View*> getViews() const;
  };

}

#endif  /* __SCENE_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
