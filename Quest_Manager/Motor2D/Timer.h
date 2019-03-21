#ifndef TIMER_H
#define TIMER_H

#include "Defs.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Stop();
	void StartFrom(uint32 secs);

	uint32 Read() const;
	float ReadSec() const;

private:

	uint32	started_at;
	uint32  stopped_at;
	bool running;


};

#endif //TIMER_H