#pragma once
class Controller
{
protected:

	// add
	virtual void insertToDb() = 0;
	virtual void promptAddInput() = 0;
	virtual bool validateAddInput() const = 0;
};

