///////////////////////////////////////////////////////////
//  NoSecretKeyException.h
//  Implementation of the Class NoSecretKeyException
//  Created on:      06-Aug-2008 7:49:10 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_36251D48_5DD6_4e76_A753_A73D5065ECF5__INCLUDED_)
#define EA_36251D48_5DD6_4e76_A753_A73D5065ECF5__INCLUDED_

#include "SNException.h"

class NoSecretKeyException : public SNException
{

public:
	NoSecretKeyException();
	virtual ~NoSecretKeyException();
	static const long serialVersionUID = 1L;

	NoSecretKeyException(String arg0, Throwable arg1);
	NoSecretKeyException(String arg0);
	NoSecretKeyException(Throwable arg0);

};
#endif // !defined(EA_36251D48_5DD6_4e76_A753_A73D5065ECF5__INCLUDED_)
