#pragma once

namespace Poly {
    template<AnalogInputs, DigitalInputs>
    class InputDevice {
    public:
        InputDevice() = default;
        GetAnalogValue(AnalogInputs input) = 0;
        GetDigitalValue(AnalogInputs input) = 0;
    }
}