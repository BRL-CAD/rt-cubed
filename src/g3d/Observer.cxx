/*                    O B S E R V E R . C X X
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by
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

/** @file Observer.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Observer pattern implementation.
 */

#include "Logger.h"

#include "Observer.h"


/*******************************************************************************
 * Observer
 ******************************************************************************/
Observer::~Observer()
{
  Logger::logDEBUG("Observer::~Observer()");
  for (std::vector<ObserverSubject*>::iterator it = _subjects.begin(); it != _subjects.end(); ++it) {
    (*it)->detach(this);
  }
}

void Observer::attached(ObserverSubject* subject)
{
  _subjects.push_back(subject);
}

void Observer::detached(ObserverSubject* subject)
{
  for (std::vector<ObserverSubject*>::iterator it = _subjects.begin(); it != _subjects.end(); ++it) {
    if (*it == subject) {
      _subjects.erase(it);
      return;
    }
  }
}


/*******************************************************************************
 * ObserverSubject
 ******************************************************************************/
ObserverSubject::~ObserverSubject()
{
  Logger::logDEBUG("ObserverSubject::~ObserverSubject()");
  for (std::vector<Observer*>::iterator it = _observers.begin(); it != _observers.end(); ++it) {
    (*it)->detached(this);
  }
}

void ObserverSubject::attach(Observer* observer)
{
  _observers.push_back(observer);
  observer->attached(this);
}

void ObserverSubject::detach(Observer* observer)
{
  for (std::vector<Observer*>::iterator it = _observers.begin(); it != _observers.end(); ++it) {
    if (*it == observer) {
      _observers.erase(it);
      observer->detached(this);
      return;
    }
  }
}

void ObserverSubject::notify(const ObserverEvent& event)
{
  for (std::vector<Observer*>::iterator it = _observers.begin(); it != _observers.end(); ++it) {
    (*it)->update(event);
  }
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
