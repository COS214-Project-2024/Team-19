#include "HighSatisfactionHandler.h"
#include <random>

HighSatisfactionHandler::HighSatisfactionHandler(SatisfactionHandler *nextHandler){
    this->nextHandler = nextHandler;
    chanceOfPopulationChange = 0.1;
    incomeAffectionRate = 1;
}

void HighSatisfactionHandler::handle(int curSatisfaction, CityHall* cityHall){
    // Pass the request down the chain if satisfaction is lower than 80
    if (curSatisfaction < 80){
        if (nextHandler == NULL){
            SatisfactionHandler::handle(curSatisfaction, cityHall);
            return;
        }
        nextHandler->handle(curSatisfaction, cityHall);
    }
    
    // Random functions
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> random1(1, 100);
    std::uniform_int_distribution<> random2(1, 10);
    std::uniform_int_distribution<> random3(-10, 10);
    std::uniform_int_distribution<> random4(0, 1);

    float changePopulation = random1(gen)/100; // Random number

    // If random number is below chanceOfPopulationChange then population should change
    if (changePopulation <= chanceOfPopulationChange){
        int numNewCitizenMultiplier = random2(gen)/100;
        int numNewCitizens = cityHall->getCurrNumCitizens() * numNewCitizenMultiplier;

        for (int i = 0; i < numNewCitizens; ){
            bool doBirth = random4(gen);

            if (doBirth){
                cityHall->birth();
            }else{
                cityHall->immigrate();
            }
        }
    }

    incomeAffectionRate += random3(gen)/100; // Money can be multiplied with 90% - 110%
    // Get CityHall to calculate next income and then multiply that by above value.
    // Then add that to popeCoin total.
}