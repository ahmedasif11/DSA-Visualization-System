

#include "State.h"
#include "StateContext.h"

namespace DSA {

State::State(StateContext& context)
    : m_context(context)
{
}

void State::pause() {
    m_isPaused = true;
}

void State::resume() {
    m_isPaused = false;
}

} 
