#ifndef ATOMIC_MODEL_HPP
#define ATOMIC_MODEL_HPP
#include "cadmium/modeling/devs/atomic.hpp"
#include "stm32h7xx_hal_dma.h"
#include "stm32h7xx_hal_i2c.h"
#include "stm32h7xx_hal_i2c_ex.h"
extern "C" {
 #include "TSL2561_STM32_Library/TSL2561.h"
  I2C_HandleTypeDef hi2c1;
}



#define TSL2561_ADD 0x39
using namespace cadmium;

struct Temp_modelState {
    TSL2561 tslsensor;
    float luxvalue;
    double sigma; // nouveau
  
    Temp_modelState() : sigma(0.0),luxvalue(0.0){}
};

std::ostream& operator<<(std::ostream& out, const Temp_modelState& state) {
   
    return out;
}

class Temp_model : public Atomic<Temp_modelState> {
public:
    Port<double>out ;
    Port<bool> in;
    // Constructeur : initialiser la LED sur la broche LED1
    Temp_model(const std::string& id) :
        Atomic<Temp_modelState>(id, Temp_modelState())
    {
        
        out = addOutPort<double>("out");
        in= addInPort<bool>("in");
        TSL2561_Init(&state.tslsensor, &hi2c1, TSL2561_ADD);

            // Set a value for sigma (so it is not 0), this determines how often the
       
    }

    void internalTransition(Temp_modelState& state) const override {
        TSL2561_GetLux(&state.tslsensor, &state.luxvalue);
        state.sigma = 5.0;
    }

    void externalTransition(Temp_modelState& state, double e) const override {

    }

    void output(const Temp_modelState& state) const override {
          bool toggle;
        if(state.luxvalue>10){
            toggle=true;
        }
        else{
            toggle=false;
            }

        out->addMessage(toggle);// Pas besoin d’output explicite ici, car l’action se fait dans internalTransition
         
    }

    [[nodiscard]] double timeAdvance(const Temp_modelState& state) const override {
        return state.sigma;
    }
};
#endif
