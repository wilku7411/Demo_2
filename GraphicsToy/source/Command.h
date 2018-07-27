#pragma once

class ICommand
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};