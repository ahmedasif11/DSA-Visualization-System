

#include "PauseMenuState.h"
#include "../Core/State/StateContext.h"
#include "../Core/Events/EventBus.h"
#include "../Core/Events/EventTypes.h"
#include "../Core/Events/Event.h"
#include "../Core/State/StateID.h"
#include "../UI/Theme/ThemeManager.h"
#include "../App/Config.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

namespace DSA {

PauseMenuState::PauseMenuState(StateContext& context)
    : State(context)
    , m_overlay()
    , m_menuBackground()
    , m_selectedButtonIndex(0)
{
}

void PauseMenuState::onEnter() {
    setupButtons();
    
    sf::Vector2u windowSize = m_context.getWindow().getSize();

    m_overlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    m_overlay.setFillColor(sf::Color(0, 0, 0, 180));

    float menuWidth = 300.0f;
    float menuHeight = 250.0f;
    float menuX = (static_cast<float>(windowSize.x) - menuWidth) / 2.0f;
    float menuY = (static_cast<float>(windowSize.y) - menuHeight) / 2.0f;
    
    m_menuBackground.setSize(sf::Vector2f(menuWidth, menuHeight));
    m_menuBackground.setPosition(sf::Vector2f(menuX, menuY));
    m_menuBackground.setFillColor(sf::Color(
        Config::Colors::PRIMARY_R,
        Config::Colors::PRIMARY_G,
        Config::Colors::PRIMARY_B,
        240
    ));

    m_titleLabel.setText("PAUSED");
    m_titleLabel.setPosition(sf::Vector2f(menuX + menuWidth / 2.0f - 60.0f, menuY + 20.0f));
    
    std::cout << "PauseMenuState entered" << std::endl;
}

void PauseMenuState::setupButtons() {
    m_buttons.clear();
    
    sf::Vector2u windowSize = m_context.getWindow().getSize();
    float menuWidth = 300.0f;
    float menuHeight = 250.0f;
    float menuX = (static_cast<float>(windowSize.x) - menuWidth) / 2.0f;
    float menuY = (static_cast<float>(windowSize.y) - menuHeight) / 2.0f;
    
    float buttonWidth = 200.0f;
    float buttonHeight = 50.0f;
    float buttonSpacing = 15.0f;
    float startY = menuY + 80.0f;
    float centerX = menuX + menuWidth / 2.0f;

    auto resumeBtn = std::make_unique<UI::Button>(
        sf::Vector2f(centerX - buttonWidth / 2.0f, startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Resume"
    );
    resumeBtn->setCallback([this]() { onResumeClicked(); });
    m_buttons.push_back(std::move(resumeBtn));

    auto mainMenuBtn = std::make_unique<UI::Button>(
        sf::Vector2f(centerX - buttonWidth / 2.0f, startY + buttonHeight + buttonSpacing),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Main Menu"
    );
    mainMenuBtn->setCallback([this]() { onMainMenuClicked(); });
    m_buttons.push_back(std::move(mainMenuBtn));

    auto exitBtn = std::make_unique<UI::Button>(
        sf::Vector2f(centerX - buttonWidth / 2.0f, startY + 2 * (buttonHeight + buttonSpacing)),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Exit"
    );
    exitBtn->setCallback([this]() { onExitClicked(); });
    m_buttons.push_back(std::move(exitBtn));
}

void PauseMenuState::handleInput(const sf::Event& event) {

    if (event.is<sf::Event::KeyPressed>()) {
        const auto* keyData = event.getIf<sf::Event::KeyPressed>();
        if (keyData) {
            if (keyData->code == sf::Keyboard::Key::Escape) {
                onResumeClicked();
            }
            else if (keyData->code == sf::Keyboard::Key::Up) {
                if (m_selectedButtonIndex > 0) {
                    --m_selectedButtonIndex;
                }
            }
            else if (keyData->code == sf::Keyboard::Key::Down) {
                if (m_selectedButtonIndex < static_cast<int>(m_buttons.size()) - 1) {
                    ++m_selectedButtonIndex;
                }
            }
            else if (keyData->code == sf::Keyboard::Key::Enter || keyData->code == sf::Keyboard::Key::Space) {
                if (m_selectedButtonIndex >= 0 && m_selectedButtonIndex < static_cast<int>(m_buttons.size())) {
                    m_buttons[m_selectedButtonIndex]->trigger();
                }
            }
        }
    }

    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto* mouseData = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseData && mouseData->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_context.getWindow());
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            
            for (auto& button : m_buttons) {
                if (button->contains(mousePosF)) {
                    button->trigger();
                    break;
                }
            }
        }
    }

    if (event.is<sf::Event::MouseMoved>()) {
        const auto* mouseData = event.getIf<sf::Event::MouseMoved>();
        if (mouseData) {
            sf::Vector2f mousePos(static_cast<float>(mouseData->position.x), 
                                 static_cast<float>(mouseData->position.y));
            
            for (std::size_t i = 0; i < m_buttons.size(); ++i) {
                if (m_buttons[i]->contains(mousePos)) {
                    m_selectedButtonIndex = static_cast<int>(i);
                    break;
                }
            }
        }
    }
}

void PauseMenuState::update(float deltaTime) {
    (void)deltaTime;
}

void PauseMenuState::render(sf::RenderTarget& target) {

    target.draw(m_overlay);

    target.draw(m_menuBackground);

    m_titleLabel.render(target);

    for (auto& button : m_buttons) {
        button->render(target);
    }
}

void PauseMenuState::onResumeClicked() {

    EventBus& eventBus = m_context.getEventBus();
    Event popEvent(EventType::StatePopped);
    eventBus.publish(popEvent);
}

void PauseMenuState::onMainMenuClicked() {

    EventBus& eventBus = m_context.getEventBus();
    Event mainMenuEvent(EventType::StateChanged);
    mainMenuEvent.setData(StateID::MainMenu);
    eventBus.publish(mainMenuEvent);
}

void PauseMenuState::onExitClicked() {

    EventBus& eventBus = m_context.getEventBus();
    Event closeEvent(EventType::WindowClosed);
    eventBus.publish(closeEvent);
}

} 
