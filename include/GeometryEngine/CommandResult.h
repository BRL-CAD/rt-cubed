///////////////////////////////////////////////////////////
//  CommandResult.h
//  Implementation of the Class CommandResult
//  Created on:      04-Dec-2008 8:26:37 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__COMMANDRESULT_H__)
#define __COMMANDRESULT_H__

class CommandResult {

public:
	virtual ~CommandResult();

	CommandResult(int resVal);
	int getCommandResult();

private:
	CommandResult();
	int ResultValue;

};
#endif // !defined(__COMMANDRESULT_H__)
// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
