#ifndef SAMPLE_TOP_HPP
#define SAMPLE_TOP_HPP
#include "cadmium/modeling/devs/coupled.hpp"
#include "generator.hpp"
#include "controller.hpp"
#include "pwmoutput.hpp"
#include "stm32h7xx_hal_rcc.h"
#include "stm32h7xx_hal_dma.h"
#include "stm32h7xx_hal_uart.h"
#ifdef __cplusplus
extern "C"
{
#endif
    extern TIM_HandleTypeDef htim5;
#ifdef __cplusplus
}
#endif

using namespace cadmium;

struct top_coupled : public Coupled
{
    top_coupled(const std::string &id) : Coupled(id)
    {
      

        auto generator = addComponent<ServoCommandGenerator>("ServocommandState");
        auto controller = addComponent<ServoController>("ServoCOntroller");
        auto pwm = addComponent<PWMOutput>("servoPWM", &htim5, TIM_CHANNEL_1, __HAL_TIM_GET_AUTORELOAD(&htim5));
        addCoupling(generator->out, controller->in);
        addCoupling(controller->out, pwm->in);
    }
};

#endif // SAMPLE_TOP_HPP
