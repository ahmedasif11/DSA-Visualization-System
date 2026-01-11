#pragma once

#include <cstdint>

namespace DSA {

enum class EventType : std::uint32_t {
    WindowClosed = 0,
    WindowResized,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    StateChanged,
    StatePushed,
    StatePopped,
    AlgorithmStarted,
    AlgorithmPaused,
    AlgorithmResumed,
    AlgorithmCompleted,
    AlgorithmStepCompleted,
    ButtonClicked,
    SliderChanged,
    CustomEvent
};

}
