/*                    O B S E R V E R . H
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

/** @file Observer.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Observer pattern interfaces.
 */

#ifndef __G3D_OBSERVER_H__
#define __G3D_OBSERVER_H__


#include <string>
#include <vector>


class ObserverEvent;
class Observer;
class ObserverSubject;


/**
 * @brief Event for Observer pattern.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Interface of an Event for the Observer pattern.  The intent of this
 * class is to be subclassed and then identified by RTTI, see
 * "Contract Programming and RTTI" at http://www.ddj.com/cpp/184401608
 */
class ObserverEvent
{
public:
  /** Name of the class */
  const std::string _className;

protected:
  /** Default constructor */
  ObserverEvent(const std::string& className) : _className(className) { }

  /** Virtual destructor
   *
   * \note Virtual methods cause RTTI/dynamic_cast to be enabled/work
   * for this class */
  virtual ~ObserverEvent() { }
};


/**
 * @brief Observer pattern.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Interface of a Observer pattern, to get notifications when a
 * Subject observed has any event of interest to communicate.
 */
class Observer
{
public:
  /** Virtual destructor */
  virtual ~Observer();

  /** Called when an event occurs */
  virtual void update(const ObserverEvent& event) = 0;

  /** Attached to a subject */
  void attached(ObserverSubject* subject);
  /** Detached from a subject */
  void detached(ObserverSubject* subject);

protected:
  /** Set of subjects */
  std::vector<ObserverSubject*> _subjects;
};


/**
 * @brief Subject abstract class, for observers to attach to
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Interface of Subject for the Observer pattern, to allow observers
 * to attach and detach and so receive notifications of interesting
 * events.
 */
class ObserverSubject
{
public:
  /** Virtual destructor */
  virtual ~ObserverSubject();

  /** Attach an observer */
  void attach(Observer* observer);
  /** Detach an observer */
  void detach(Observer* observer);
  /** Implementation of the notification */
  virtual void notify(const ObserverEvent& event);

protected:
  /** Set of observers */
  std::vector<Observer*> _observers;
};


#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
