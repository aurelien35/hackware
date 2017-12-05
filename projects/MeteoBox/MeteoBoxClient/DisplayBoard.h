#ifndef METEOBOX_DISPLAYBOARD_H
#define METEOBOX_DISPLAYBOARD_H

#include "MeteoBoxClient.h"

class DisplayBoard
{
private:
	bool					_isConnected;
	
public:
	DisplayBoard();
	
	bool					startUp();
	void					shutDown();
	
	bool					isConnected() const;
	bool					update();
};

#endif
