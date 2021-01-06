#include "libraryCPP.h"

#include <iostream>

void accentCPP(unsigned char * bgr ,int h, int range, int  v, int i){

    char rangeP = (char)((h + range / 2) % 360);
    char rangeM = (char)((h - range / 2 + 360) % 360);
    if (( rangeM <= rangeP && rangeM <= v && rangeP >= v) || ( rangeM > rangeP && ( rangeM <= v || rangeP >= v )))
    {}
    else{
     bgr[4*i] =  bgr[4*i+1] = bgr[4*i+2] = (int) (0.299 * bgr[4*i+2] + 0.587 * bgr[4*i+1] + 0.114 * bgr[4*i]);
    }

}





