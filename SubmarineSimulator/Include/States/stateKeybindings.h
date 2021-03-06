#ifndef SUBMARINESIMULATORSTATEKEYBINDINGS_H
#define SUBMARINESIMULATORSTATEKEYBINDINGS_H

#include "../Core/state.h"
#include "../Core/machine.h"
#include "../Core/utilities.h"

class StateKeybindings : public States{
public:

    void initialize(sf::RenderWindow *window);

    void update(sf::RenderWindow *window);

    void render(sf::RenderWindow *window);

    void destroy(sf::RenderWindow *window);

    void handleEvent(sf::RenderWindow *window , sf::Event event);

    void reinitialize(sf::RenderWindow *window);

private:
    Utilities util;

    sf::Font* font = nullptr;
    sf::Font* keyFont = nullptr;
    sf::Text* movementText = nullptr;
    sf::Text* menuNavigationText = nullptr;
    sf::Text* gameplayText = nullptr;
    sf::Text* alreadyBoundText = nullptr;

    sf::Texture* bgTexture = nullptr;
    sf::Texture* btnTexture = nullptr;
    sf::Texture* overlayTexture = nullptr;
    sf::Sprite* background = nullptr;
    sf::Sprite* overlay = nullptr;

    struct keySquares{
        sf::Text* keyText = nullptr;
        sf::Text* titleText = nullptr;
        sf::Sprite* keySquare = nullptr;
    };

    std::vector<keySquares> keyVector;

    std::vector<sf::Vector2f> positionList;

    std::string keyList[sf::Keyboard::KeyCount] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
                                                   "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
                                                   "W", "X", "Y", "Z", "Num0", "Num1", "Num2", "Num3", "Num4",
                                                   "Num5", "Num6", "Num7", "Num8", "Num9", "Escape", "LControl",
                                                   "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt",
                                                   "RSystem", "Menu", "LBracket", "RBracket", "SemiColon", "Comma",
                                                   "Period", "Quote", "Slash", "BackSlash", "Tilde", "Equal", "Dash",
                                                   "Space", "Return", "BackSpace", "Tab", "PageUp", "PageDown", "End",
                                                   "Home", "Insert", "Delete", "Add", "Subtract", "Multiply", "Divide",
                                                   "Left", "Right", "Up", "Down", "Numpad0", "Numpad1", "Numpad2", "Numpad3",
                                                   "Numpad4", "Numpad5", "Numpad6", "Numpad7", "Numpad8", "Numpad9", "F1",
                                                   "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
                                                   "F13", "F14", "F15", "Pause"};

    std::string wordList [8]{"up","down","left","right","select","back","shoot","pause"};

    bool waitingForInput = false;
    bool keyPressedInBinds = true;
    int keyToBind;
    int transparencyValue = 0;
};

#endif //SUBMARINESIMULATORSTATEKEYBINDINGS_H
