#include "point.h"
#include <SFML/Graphics.hpp>

#ifndef EVENT_H
#define	EVENT_H

// Type 1 is Exit

class event{
public:
    event (int xIn, int yIn, int t);
    point getCoord();
    int getType();

private:
    int type;
    point loc;
};

#endif	/* EVENT_H */
