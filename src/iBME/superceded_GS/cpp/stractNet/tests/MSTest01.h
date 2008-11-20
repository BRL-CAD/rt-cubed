///////////////////////////////////////////////////////////
//  MSTest01.h
//  Implementation of the Class MSTest01
//  Created on:      06-Aug-2008 8:02:33 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_AD8AA14B_8711_4466_A103_70BE5FBCEE2D__INCLUDED_)
#define EA_AD8AA14B_8711_4466_A103_70BE5FBCEE2D__INCLUDED_

#include "SNRoot.h"

class MSTest01 : public SNRoot
{

public:
	virtual ~MSTest01();
	static MSTest01 test;

	MSTest01();
	static void main(String[] args);

};
#endif // !defined(EA_AD8AA14B_8711_4466_A103_70BE5FBCEE2D__INCLUDED_)
