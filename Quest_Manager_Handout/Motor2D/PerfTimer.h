#ifndef PERFTIMER_H
#define PERFTIMER_H

#include "Defs.h"

class PerfTimer
{
public:

	// Constructor
	PerfTimer();

	void Start();
	double ReadMs() const;
	uint64 ReadTicks() const;

private:
	uint64	started_at;
	static uint64 frequency;
};

#endif //PERFTIMER_H