#ifndef NOISE_H
#define NOISE_H

#include <libnoise/noise.h>

class Noise{
    private:
        float _zCoord;
        
    public:
        float GenerateValue(void);
};

#endif //NOISE_H