#pragma once

enum				eState
{
	S0,
	S1,
	S2,
	S3,
	S4,
	S5,
	S6,
	S7,
	STATE_ERROR
};

enum				eAction
{
	MA,
	HR,
	ACTION_ERROR
};

#define STATE_MAX	STATE_ERROR + 1
#define EDGE_MAX	sizeof("mechant")	

extern eState		gStateTable[STATE_MAX][EDGE_MAX];
extern eAction		gActionTable[STATE_MAX][EDGE_MAX];