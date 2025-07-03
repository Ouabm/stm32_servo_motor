#ifndef RT_PWMOUTPUT_HPP
#define RT_PWMOUTPUT_HPP

#include <cadmium/modeling/devs/atomic.hpp>
#include <limits>
#include <iostream>
#include <algorithm>
#include "stm32h7xx_hal.h"

using namespace std;

namespace cadmium
{

    struct PWMOutputState
    {
        double output;
        double sigma;

        explicit PWMOutputState() : output(0.0), sigma(std::numeric_limits<double>::infinity()) {}
    };

    std::ostream &operator<<(std::ostream &out, const PWMOutputState &state)
    {
        out << "PWM Output Duty Cycle: " << state.output;
        return out;
    }

    class PWMOutput : public Atomic<PWMOutputState>
    {
    public:
        Port<double> in;
        TIM_HandleTypeDef *timer;
        uint32_t channel;
        uint32_t period_ticks;

        PWMOutput(const std::string &id, TIM_HandleTypeDef *t, uint32_t ch, uint32_t period)
            : Atomic<PWMOutputState>(id, PWMOutputState()), timer(t), channel(ch), period_ticks(period)
        {
            in = addInPort<double>("in");

            setPWMDutyCycle(0.0);
        }

        void internalTransition(PWMOutputState &state) const override
        {
        }

        void externalTransition(PWMOutputState &state, double e) const override
        {
            if (!in->empty())
            {
                for (const auto &x : in->getBag())
                {
                    state.output = std::clamp(x, 0.0, 1.0);
                }
                setPWMDutyCycle(state.output);
            }
        }

        void output(const PWMOutputState &state) const override
        {
        }

        [[nodiscard]] double timeAdvance(const PWMOutputState &state) const override
        {
            return std::numeric_limits<double>::infinity();
        }

    private:
        void setPWMDutyCycle(double duty) const
        {
            uint32_t compare = static_cast<uint32_t>(duty * period_ticks);
            __HAL_TIM_SET_COMPARE(timer, channel, compare); // mettre compare dans dutycycle dans le bon registre
        }
    };
}

#endif // RT_PWMOUTPUT_HPP
