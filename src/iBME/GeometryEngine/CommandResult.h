///////////////////////////////////////////////////////////
//  CommandResult.h
//  Implementation of the Class CommandResult
//  Created on:      20-Nov-2008 12:36:10 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_46F3C252_C918_452b_9425_07C587C5B4A3__INCLUDED_)
#define EA_46F3C252_C918_452b_9425_07C587C5B4A3__INCLUDED_

class CommandResult
{

public:
	CommandResult();
	virtual ~CommandResult();

	void CommandResult(int resVal);
	int getCommandResult();

private:
	int ResultValue;

};
#endif // !defined(EA_46F3C252_C918_452b_9425_07C587C5B4A3__INCLUDED_)
