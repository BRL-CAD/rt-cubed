/*                        M A I N . C X X
 * BRL-CAD
 *
 * Copyright (c) 2008-2009 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */

/** @file main.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Entry point of the 3D Geometry Editor (g3d).
 */

#include <QtGui>
#include <QGLWidget>

#include <OGRE/Ogre.h>

#include "Logger.h"
#include "QtRenderListener.h"

#define OGRE_PLUGIN_FILE        (DATA_DIR "ogreplugins.cfg")
#define OGRE_CFG_FILE           (DATA_DIR "ogre.cfg")
#define OGRE_LOG_FILE           (DATA_DIR "ogre.log")
#define OGRE_RESOURCES_CFG_FILE (DATA_DIR "resources.cfg")

class GraphicsView : public QGraphicsView
{
public:
  GraphicsView(const char* title) 
  {
    setWindowTitle(title);
  }

protected:
  void resizeEvent(QResizeEvent *ev) 
  {
    if(scene()) {
      scene()->setSceneRect(QRect(QPoint(0, 0), ev->size()));
    }
    QGraphicsView::resizeEvent(ev);
  }
};

int main(int argc, char** argv)
{
#if defined(WIN32)
  // HACK!
  // This is required on Windows XP because of a bug that causes
  // timing to be wrong when more than one CPU is available.
  // This issue has been fixed in Vista.

  HANDLE id = GetCurrentThread();
  DWORD pmask;
  DWORD psysmask;
  GetProcessAffinityMask(id, &pmask, &psysmask);
  DWORD res = SetThreadAffinityMask(id, 1);
#endif

  // Set up Ogre
  Ogre::Root ogreRoot(OGRE_PLUGIN_FILE, OGRE_CFG_FILE, OGRE_LOG_FILE);
  // TODO: Explicitly configure
  if (ogreRoot.restoreConfig() || ogreRoot.showConfigDialog()) {
    ogreRoot.initialise(false);
  }

  Ogre::RenderWindow *renderWindow;
  {
    Ogre::NameValuePairList params;
    params["currentGLContext"] = Ogre::String("True");
  
    renderWindow = ogreRoot.createRenderWindow("MainRenderWindow", 640, 480, false, &params);

    if(!renderWindow) {
      // TODO: Real error handling
      throw std::exception();
    }
    renderWindow->setVisible(true);
  }

  // Load resources
  {
    Ogre::ConfigFile config;
    config.load(OGRE_RESOURCES_CFG_FILE);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = config.getSectionIterator();
    while (seci.hasMoreElements()) {
      const Ogre::String& secName = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
      for (Ogre::ConfigFile::SettingsMultiMap::iterator i = settings->begin();
	   i != settings->end(); ++i) {
	const Ogre::String& typeName = i->first;
	const Ogre::String& archName = i->second;

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName,
								       typeName,
								       secName);
      }
    }

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  }

  // Create scene, camera, viewport
  Ogre::SceneManager *scene = ogreRoot.createSceneManager("DefaultSceneManager", "g3d SceneManager");
  Ogre::Camera *camera = scene->createCamera("g3d Camera");
  Ogre::Viewport *viewport = renderWindow->addViewport(camera);
  viewport->setBackgroundColour(Ogre::ColourValue(0.1f, 0.1f, 0.1f, 1.0f));
  scene->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
  Ogre::Light *light = scene->createLight("MainLight");
  light->setPosition(0, 10, 0);
  light->setDiffuseColour(Ogre::ColourValue(1.0, 0.5, 0.0));

  // Basic rendering test
  Ogre::Entity *sphereEnt = scene->createEntity("Sphere", "sphere.mesh");
  Ogre::SceneNode *sphereNode = scene->getRootSceneNode()->createChildSceneNode("SphereNode");
  sphereNode->setVisible(true);
  sphereNode->attachObject(sphereEnt);
  sphereNode->setPosition(50, 0, 0);
  camera->setPosition(0, 0, 0);
  camera->lookAt(sphereNode->getPosition());

  renderWindow->setVisible(true);

  Logger::logDEBUG("Ogre ready to render.");

  // Set up Qt
  QApplication qapp(argc, argv);

  // Configure and install the Qt render listener
  Ogre::ManualObject *guiObj = scene->createManualObject("GUI");
  scene->getRootSceneNode()->createChildSceneNode()->attachObject(guiObj);
  QtRenderListener *listener = new QtRenderListener(&qapp, guiObj, camera, scene);
  scene->addRenderQueueListener(listener);

  GraphicsView view("G3D");
  QGraphicsScene qtScene;
  
  view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
  view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  view.setScene(&qtScene);
  view.show();

  view.resize(1024, 768);

  // Step Qt once to set everything up so Ogre has a context to render into
  qapp.processEvents();

  // Main loop
  // TODO: Clean exit support
  // TODO: Manually step Qt until the OpenGL context is ready, and
  // only then hand things off to Ogre
  while(true) {
    ogreRoot.renderOneFrame();
  }

  scene->removeRenderQueueListener(listener);
  delete listener;

  return 0;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
