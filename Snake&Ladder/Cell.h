#pragma once
#include "Jump.h"

class Cell
{
private:
	Jump *jump;
public:
	Cell()
	{
		jump = new Jump();
	}
	void setJump(Jump *jump)
	{
		this->jump = jump;
	}

	Jump* getJump()
	{
		return jump;
	}


	~Cell()
	{
		delete jump;
	}

};