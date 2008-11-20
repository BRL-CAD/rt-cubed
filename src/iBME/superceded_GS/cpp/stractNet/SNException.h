///////////////////////////////////////////////////////////
//  SNException.h
//  Implementation of the Class SNException
//  Created on:      06-Aug-2008 7:49:01 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_98CB0C9B_F1E7_4d6d_B6D7_D80B8687BA4D__INCLUDED_)
#define EA_98CB0C9B_F1E7_4d6d_B6D7_D80B8687BA4D__INCLUDED_

class SNException : public Exception
{

public:
	SNException();
	virtual ~SNException();
	static const long serialVersionUID = 1L;

	SNException(String arg0, Throwable arg1);
	SNException(String arg0);
	SNException(Throwable arg0);

};
#endif // !defined(EA_98CB0C9B_F1E7_4d6d_B6D7_D80B8687BA4D__INCLUDED_)
