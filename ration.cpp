#include "ration.h" // Header file for ration functions

Ration calculateRation(int income, int familySize) {
    Ration ration;
    // Basic ration calculation logic
    ration.rice = familySize * 5; // 5 kg of rice per family member
    ration.wheat = familySize * 3; // 3 kg of wheat per family member

    // Additional ration based on income
    if (income < 10000) {
        ration.sugar = familySize * 1; // 1 kg of sugar per family member for low income
        ration.oil = familySize * 2;   // 2 liters of oil per family member for low income
    } else {
        ration.sugar = 0; // No sugar for higher income
        ration.oil = 0;   // No oil for higher income
    }

    return ration;
}