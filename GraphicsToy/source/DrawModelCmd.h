#pragma once

#include "Command.h"
#include "graphics/Model.h"

class CDrawModelCmd : public ICommand
{
public:
	CDrawModelCmd(CModel* toDraw)
	{
		m_toDraw = toDraw;
	}

	void execute() override
	{
		//m_toDraw->Draw(*(m_toDraw->GetShader()));
	}

	void undo() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

private:
	CModel* m_toDraw;
};