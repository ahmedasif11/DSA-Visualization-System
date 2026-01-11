

#include "Theme.h"
#include "../../App/Config.h"

namespace DSA {
namespace UI {

Theme::Theme()
{

    primaryColor = sf::Color(Config::Colors::PRIMARY_R, Config::Colors::PRIMARY_G, Config::Colors::PRIMARY_B);
    secondaryColor = sf::Color(Config::Colors::SECONDARY_R, Config::Colors::SECONDARY_G, Config::Colors::SECONDARY_B);
    accentColor = sf::Color(Config::Colors::ACCENT_R, Config::Colors::ACCENT_G, Config::Colors::ACCENT_B);
    backgroundColor = sf::Color(Config::Colors::BACKGROUND_R, Config::Colors::BACKGROUND_G, Config::Colors::BACKGROUND_B);
    textColor = sf::Color(Config::Colors::TEXT_R, Config::Colors::TEXT_G, Config::Colors::TEXT_B);
    hoverColor = sf::Color(Config::Colors::SECONDARY_R, Config::Colors::SECONDARY_G, Config::Colors::SECONDARY_B);
    pressedColor = sf::Color(Config::Colors::ACCENT_R, Config::Colors::ACCENT_G, Config::Colors::ACCENT_B);
    disabledColor = sf::Color(128, 128, 128);
    successColor = sf::Color(Config::Colors::SUCCESS_R, Config::Colors::SUCCESS_G, Config::Colors::SUCCESS_B);
    warningColor = sf::Color(Config::Colors::WARNING_R, Config::Colors::WARNING_G, Config::Colors::WARNING_B);

    fontMainPath = Config::FONT_MAIN_PATH;
    fontMonospacePath = Config::FONT_MONOSPACE_PATH;
    fontTitlePath = Config::FONT_TITLE_PATH;

    fontSizeNormal = 24;
    fontSizeLarge = 32;
    fontSizeSmall = 18;
    fontSizeTitle = 48;
    buttonHeight = 50.0f;
    buttonPadding = 10.0f;
}

}
} 
