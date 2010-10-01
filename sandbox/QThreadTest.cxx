/*                 Q T H R E A D T E S T . C X X
 * BRL-CAD
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
/** @file QThreadTest.cxx
 *
 */

#import <QtCore/QThread>
#import <iostream>

class TestThread : public QThread
{
public:
    static void msleep(unsigned long int msec) {
    	QThread::msleep(msec);
    }
protected:
    void run()
    {
    	TestThread::msleep(1500);
    	std::cout << "Burp.\n";
    }
};

class RelayThread : public QThread
{
public:
    RelayThread(QThread* thread) {
    	this->thread = thread;
    }
	static void msleep(unsigned long int msec) {
		QThread::msleep(msec);
    }

protected:
    void run()
    {
    	RelayThread::msleep(153);
    	this->thread->start();
    }
private:
    QThread* thread;
};

/**
 * main application
 */
int main(int argc, char *argv[])
{
    TestThread* t1 = new TestThread();
    TestThread* t2 = new TestThread();
    TestThread* t3 = new TestThread();

    RelayThread r1(t1);
    RelayThread r2(t2);
    RelayThread r3(t3);

    r1.start();
    TestThread::msleep(333);
    r2.start();
    TestThread::msleep(533);
    r3.start();

    TestThread::msleep(5000);

    delete t1;
    delete t2;
    delete t3;
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
