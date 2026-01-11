

#include "AlgorithmExecutor.h"
#include "../../App/Config.h"

namespace DSA {

AlgorithmExecutor::AlgorithmExecutor()
    : m_sorter(nullptr)
    , m_array()
    , m_steps()
    , m_currentStepIndex(0)
    , m_state(State::Idle)
    , m_speed(Config::ANIMATION_DEFAULT_SPEED)
    , m_timeSinceLastStep(0.0f)
    , m_stepDelay(0.5f)
{
}

void AlgorithmExecutor::setSorter(std::unique_ptr<SorterBase> sorter) {
    m_sorter = std::move(sorter);
    reset();
}

void AlgorithmExecutor::setArray(const Array& array) {
    m_array = array;
    reset();
}

bool AlgorithmExecutor::start() {
    if (m_state == State::Running) {
        return false;
    }
    
    if (m_state == State::Paused) {

        resume();
        return true;
    }

    if (!m_sorter) {
        return false;
    }
    
    if (m_array.isEmpty()) {
        return false;
    }

    if (m_steps.empty()) {
        m_steps = m_sorter->sort(m_array);
        if (m_steps.empty()) {
            return false;
        }
    }

    m_currentStepIndex = 0;
    m_state = State::Running;
    m_timeSinceLastStep = 0.0f;

    if (!m_steps.empty()) {
        m_stepDelay = calculateStepDelay(m_steps[0]);
    }
    
    return true;
}

void AlgorithmExecutor::pause() {
    if (m_state == State::Running) {
        m_state = State::Paused;
    }
}

void AlgorithmExecutor::resume() {
    if (m_state == State::Paused) {
        m_state = State::Running;
    }
}

void AlgorithmExecutor::reset() {
    m_steps.clear();
    m_currentStepIndex = 0;
    m_state = State::Idle;
    m_timeSinceLastStep = 0.0f;
}

void AlgorithmExecutor::stepForward() {
    if (m_steps.empty()) {
        return;
    }
    
    if (m_currentStepIndex < m_steps.size() - 1) {
        advanceStep();
    } else {

        m_state = State::Completed;
    }
}

void AlgorithmExecutor::setSpeed(float speed) {

    if (speed < Config::ANIMATION_MIN_SPEED) {
        m_speed = Config::ANIMATION_MIN_SPEED;
    } else if (speed > Config::ANIMATION_MAX_SPEED) {
        m_speed = Config::ANIMATION_MAX_SPEED;
    } else {
        m_speed = speed;
    }
}

void AlgorithmExecutor::update(float deltaTime) {
    if (m_state != State::Running) {
        return;
    }
    
    if (m_steps.empty()) {
        m_state = State::Completed;
        return;
    }

    m_timeSinceLastStep += deltaTime;

    float requiredDelay = m_stepDelay / m_speed;
    if (m_timeSinceLastStep >= requiredDelay) {
        advanceStep();
        m_timeSinceLastStep = 0.0f;

        if (m_currentStepIndex < m_steps.size()) {
            m_stepDelay = calculateStepDelay(m_steps[m_currentStepIndex]);
        }
    }
}

const SortStep* AlgorithmExecutor::getCurrentStep() const {
    if (m_steps.empty() || m_currentStepIndex >= m_steps.size()) {
        return nullptr;
    }
    
    return &m_steps[m_currentStepIndex];
}

std::string AlgorithmExecutor::getCurrentMessage() const {
    const SortStep* step = getCurrentStep();
    if (step) {
        return step->message;
    }
    return "";
}

std::string AlgorithmExecutor::getAlgorithmName() const {
    if (m_sorter) {
        return m_sorter->getName();
    }
    return "";
}

void AlgorithmExecutor::advanceStep() {
    if (m_currentStepIndex < m_steps.size() - 1) {
        ++m_currentStepIndex;
    } else {

        m_state = State::Completed;
    }
}

float AlgorithmExecutor::calculateStepDelay(const SortStep& step) const {

    switch (step.type) {
        case StepType::Compare:
            return Config::ANIMATION_COMPARE_DURATION_MS / 1000.0f;
            
        case StepType::Swap:
            return Config::ANIMATION_SWAP_DURATION_MS / 1000.0f;
            
        case StepType::Highlight:
            return Config::ANIMATION_COMPARE_DURATION_MS / 1000.0f;
            
        case StepType::Complete:
            return 1.0f;
            
        default:
            return 0.5f;
    }
}

} 
