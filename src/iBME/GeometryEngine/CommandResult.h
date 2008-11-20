///////////////////////////////////////////////////////////
//  CommandResult.h
//  Implementation of the Class CommandResult
//  Created on:      20-Nov-2008 8:00:09 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_98450CF2_B0D7_49a0_A71F_C652F6FEB3AB__INCLUDED_)
#define EA_98450CF2_B0D7_49a0_A71F_C652F6FEB3AB__INCLUDED_

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
#endif // !defined(EA_98450CF2_B0D7_49a0_A71F_C652F6FEB3AB__INCLUDED_)
