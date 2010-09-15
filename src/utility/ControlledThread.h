/*              C O N T R O L L E D T H R E A D . H
 * BRLCAD
 *
 * Copyright (c) 2010 United States Government as represented by
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
/** @file ControlledThread.h
 *
 */

#ifndef __CONTROLLEDTHREAD_H__
#define __CONTROLLEDTHREAD_H__

class ControlledThread
{
public:
  ControlledThread(QString threadname = "");
  virtual ~ControlledThread();

  bool startup();
  bool shutdown();

protected:
  virtual boolean preStartupHook() = 0;
  virtual boolean postStartupHook() = 0;

  virtual boolean preShutdownHook() = 0;
  virtual boolean postShutdownHook() = 0;

private:
  /* fields */
  QString threadName;
  bool runCmd;
  bool runStatus;

};

#endif /* __CONTROLLEDTHREAD_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
