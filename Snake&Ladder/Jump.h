#pragma once
#include "JumpType.h"
class Jump
{
private:
	int start;
	int end;
	JumpType jumpType;
public:
	Jump()
	{
		start = end = -1;
		jumpType = Empty;
	}

	void setJump(int start, int end, JumpType jumpType)
	{
		this->start = start;
		this->end = end;
		this->jumpType = jumpType;
	}

	int getEndJump()
	{
		return end;
	}
	int getStartJump()
	{
		return start;
	}
	JumpType getJumpType()
	{
		return jumpType;
	}
};