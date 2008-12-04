///////////////////////////////////////////////////////////
//  CommandResult.h
//  Implementation of the Class CommandResult
//  Created on:      04-Dec-2008 8:26:37 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_11EF8B7D_0248_4a1d_BA28_8F91C178F2E5__INCLUDED_)
#define EA_11EF8B7D_0248_4a1d_BA28_8F91C178F2E5__INCLUDED_

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
#endif // !defined(EA_11EF8B7D_0248_4a1d_BA28_8F91C178F2E5__INCLUDED_)
