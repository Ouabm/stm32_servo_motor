#ifndef SERVO_COMMAND_GENERATOR_HPP
#define SERVO_COMMAND_GENERATOR_HPP

#include <cadmium/modeling/devs/atomic.hpp>
#include <limits>
#include <iostream>
#include <vector>

namespace cadmium {

    struct ServoCommandState {
        double angle;
        double sigma;
        size_t index;
        std::vector<double> commands;

        ServoCommandState() : angle(0.0), sigma(1.0), index(0),
            commands({0.0,10.0,20.0,30.0,40.0,50.0,60.0,70.0,80.0,90.0,100.0,110.0,120.0,130.0,140.0,150.0,160.0,170.0, 180.0}) {}
    };

    std::ostream& operator<<(std::ostream &out, const ServoCommandState& state) {
        out << "Angle: " << state.angle;
        return out;
    }

    class ServoCommandGenerator : public Atomic<ServoCommandState> {
    public:
        Port<double> out;

        ServoCommandGenerator(const std::string& id) : Atomic<ServoCommandState>(id, ServoCommandState()) {
            out = addOutPort<double>("out");
        }

        void internalTransition(ServoCommandState& state) const override {
            state.index++;
            if (state.index < state.commands.size()) {
                state.angle = state.commands[state.index];
                state.sigma = 0.5;
            } else {
                state.sigma = std::numeric_limits<double>::infinity();
            }
        }

        void externalTransition(ServoCommandState& state, double e) const override {}

        void output(const ServoCommandState& state) const override {
            out->addMessage(state.angle);
        }

        [[nodiscard]] double timeAdvance(const ServoCommandState& state) const override {
            return state.sigma;
        }
    };
}

#endif // SERVO_COMMAND_GENERATOR_HPP
