#include "event.h"

// Type 1 is Exit

event::event (int xIn, int yIn, int t){
    type = t;
    loc.x = xIn;
    loc.y = yIn;
}

point event::getCoord(){
    point coord;
    coord.x = loc.x;
    coord.y = loc.y;

    return(coord);
}

int event::getType(){
    return type;
}
