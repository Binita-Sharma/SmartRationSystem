#ifndef RATION_H
#define RATION_H

struct Ration {
    int rice;
    int wheat;
    int sugar;
    int oil;
    
};

Ration calculateRation(int income, int familySize);

#endif
