#include "../../Include/States/statePlayConfig.h"
#include "../../Include/States/stateGameMode1.h"
#include "../../Include/States/stateMainMenu.h"
#include "../../Include/States/stateGameMode2.h"


void StatePlayConfig::initialize(sf::RenderWindow *window) {
    sf::View newView(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
    window->setView(newView);

    this->bgTexture = new sf::Texture();
    this->bgTexture->loadFromFile("Graphics/Sprites/bakgrunn.png");
    this->background = new sf::Sprite();
    this->background->setTexture(*this->bgTexture);
    this->background->scale(window->getSize().x/background->getGlobalBounds().width,window->getSize().y/background->getGlobalBounds().height);

    machine.selectedObjectsPointer->selectedFighter=0;
    machine.selectedObjectsPointer->selectedTheme=0;

    //Legger til play og back button
    for (unsigned int i = 0; i < sizeof(menuTextures) / sizeof(*menuTextures); ++i) {
        menuTextures[i].buttonMouseOver = new sf::Texture();
        menuTextures[i].buttonMouseOver->loadFromFile("Graphics/Sprites/PlayConfig_buttons/Btn" + std::to_string(i * 3) + ".png");

        menuTextures[i].buttonNormal = new sf::Texture();
        menuTextures[i].buttonNormal->loadFromFile("Graphics/Sprites/PlayConfig_buttons/Btn" + std::to_string(i * 3 + 1) + ".png");

        menuTextures[i].buttonClicked = new sf::Texture();
        menuTextures[i].buttonClicked->loadFromFile("Graphics/Sprites/PlayConfig_buttons/Btn" + std::to_string(i * 3 + 2) + ".png");

        menuButtons[i] = new sf::Sprite();
        menuButtons[i]->setTexture(*this->menuTextures[i].buttonNormal);
        menuButtons[i]->setOrigin(menuButtons[i]->getGlobalBounds().width / 2, menuButtons[i]->getGlobalBounds().height / 2);
    }
    //Legger til alle bildekanppene
    for (unsigned int i = 0; i < sizeof(PictureTexture) / sizeof(*PictureTexture); ++i) {
        PictureTexture[i].buttonNormal = new sf::Texture();
        PictureTexture[i].buttonNormal->loadFromFile("Graphics/Sprites/PlayConfig_pictures/PngBtn" + std::to_string(i * 2) + ".png");

        PictureTexture[i].buttonMouseOver = new sf::Texture();

        PictureTexture[i].buttonMouseOver->loadFromFile("Graphics/Sprites/PlayConfig_pictures/PngBtn" + std::to_string(i * 2 + 1) + ".png");
        PictureButtons[i] = new sf::Sprite();
        PictureButtons[i]->setTexture(*this->PictureTexture[i].buttonNormal);
        PictureButtons[i]->setOrigin(PictureButtons[i]->getGlobalBounds().width / 2, PictureButtons[i]->getGlobalBounds().height / 2);
    }

    //THEMES
    this->theme = util.addText("Select Theme", 35, 2, 2, window->getSize().x / 6.0f, window->getSize().y / 24.0f, window, machine.settingPointer->selectedLanguage);
    //WATERTHEME
    PictureButtons[0]->scale(window->getSize().x / 3456.0f, window->getSize().y / 1944.0f);
    PictureButtons[0]->setPosition(window->getSize().x / 6.0f, window->getSize().y / 4.5f);
    this->WaterTheme = util.addText("Water", 30, 2, 2, window->getSize().x / 6.0f, window->getSize().y / 4.5f + window->getSize().y/9.5f, window, machine.settingPointer->selectedLanguage);
    //SPACETHEME
    PictureButtons[1]->scale(window->getSize().x / 3456.0f, window->getSize().y / 1944.f);
    PictureButtons[1]->setPosition(window->getSize().x / 6.0f, window->getSize().y / 2.1f);
    this->SpaceTheme = util.addText("Space", 30, 2, 2, window->getSize().x / 6.0f, window->getSize().y / 2.1f + window->getSize().y/9.5f, window, machine.settingPointer->selectedLanguage);

    //GAMEMODE
    this->gamemode = util.addText("Select Gamemode", 35, 2, 2, window->getSize().x / 2.0f, window->getSize().y / 24.0f, window, machine.settingPointer->selectedLanguage);
    //ARCADE
    PictureButtons[4]->scale(window->getSize().x / 3456.0f, window->getSize().y / 1944.0f);
    PictureButtons[4]->setPosition(window->getSize().x / 2.0f, window->getSize().y / 4.5f);
    this->Arcade = util.addText("Arcade", 30, 2, 2, window->getSize().x / 2.0f, window->getSize().y / 4.5f + window->getSize().y/9.5f, window, machine.settingPointer->selectedLanguage);
    //CLASSIC
    PictureButtons[5]->scale(window->getSize().x / 3456.0f, window->getSize().y / 1944.0f);
    PictureButtons[5]->setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.1f);
    this->Classic = util.addText("Classic", 30, 2, 2, window->getSize().x / 2.0f, window->getSize().y / 2.1f + window->getSize().y/9.5f, window, machine.settingPointer->selectedLanguage);

    //FIGHTERS
    this->fighter = util.addText("Select Fighter", 35, 2, 2, window->getSize().x - window->getSize().x / 6.f, window->getSize().y / 24.0f, window, machine.settingPointer->selectedLanguage);
    //SUBMARINE
    PictureButtons[2]->scale(window->getSize().x / 1536.0f, window->getSize().y / 864.0f);
    PictureButtons[2]->rotate(90);
    PictureButtons[2]->setPosition( window->getSize().x - window->getSize().x / 6.f, window->getSize().y / 4.5f);
    this->Submarine = util.addText("Submarine", 30, 2, 2, window->getSize().x - window->getSize().x / 6.f, window->getSize().y / 4.5f + window->getSize().y/9.5f, window, machine.settingPointer->selectedLanguage);
    //SPACEFIGHTER
    PictureButtons[3]->scale(window->getSize().x / 1536.0f, window->getSize().y / 864.0f);
    PictureButtons[3]->rotate(90);
    PictureButtons[3]->setPosition(window->getSize().x - window->getSize().x / 6.f, window->getSize().y / 2.1f);
    this->Spaceship = util.addText("Spaceship", 30, 2, 2, window->getSize().x - window->getSize().x / 6.f, window->getSize().y / 2.1f + window->getSize().y/9.5f, window, machine.settingPointer->selectedLanguage);

    //PLAY-button posisjonen og skalinga
    menuButtons[0]->scale(window->getSize().x / 1536.0f, window->getSize().y / 864.0f);
    menuButtons[0]->setPosition(window->getSize().x / 2, window->getSize().y - window->getSize().y /6.0f);

    //BACK-button posisjonen og skalinga
    menuButtons[1]->scale(window->getSize().x / 5120.f, window->getSize().y / 2880.f);
    menuButtons[1]->setPosition(window->getSize().x * 0.95f, window->getSize().y - window->getSize().y / 10.f);

    util.makeMuteButton(window, machine.mutedPointer);
}

void StatePlayConfig::update(sf::RenderWindow *window) {
    util.checkMuteMouseOver(window);
    machine.audioLoaderPointer->updateSounds();

    for (unsigned int i = 0; i < sizeof(menuTextures) / sizeof(*menuTextures); ++i) {
        if (util.checkMouseover(menuButtons[i], window)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                menuButtons[i]->setTexture(*this->menuTextures[i].buttonClicked);
            } else {
                menuButtons[i]->setTexture(*this->menuTextures[i].buttonMouseOver);
            }
        } else {
            menuButtons[i]->setTexture(*this->menuTextures[i].buttonNormal);
        }
    }

    for (unsigned int i = 0; i < sizeof(PictureTexture) / sizeof(*PictureTexture); ++i) {
        if (util.checkMouseover(PictureButtons[i], window))
            PictureButtons[i]->setTexture(*this->PictureTexture[i].buttonMouseOver);
        else {
            PictureButtons[i]->setTexture(*this->PictureTexture[i].buttonNormal);
        }
        if (i == (unsigned)selected_Fighter)
            PictureButtons[i]->setTexture(*this->PictureTexture[i].buttonMouseOver);
        if (i == (unsigned)selected_Theme)
            PictureButtons[i]->setTexture(*this->PictureTexture[i].buttonMouseOver);
        if (i == (unsigned)selected_Gamemode)
            PictureButtons[i]->setTexture(*this->PictureTexture[i].buttonMouseOver);

    }

}

void StatePlayConfig::render(sf::RenderWindow *window) {
    window->draw(*this->background);

    for (unsigned int i = 0; i < sizeof(menuTextures) / sizeof(*menuTextures); ++i) {
        window->draw(*this->menuButtons[i]);
    }
    for (unsigned int i = 0; i < sizeof(PictureTexture) / sizeof(*PictureTexture); ++i) {
        window->draw(*this->PictureButtons[i]);
    }

    window->draw(*this->theme);
    window->draw(*this->fighter);
    window->draw(*this->gamemode);

    window->draw(*this->WaterTheme);
    window->draw(*this->SpaceTheme);

    window->draw(*this->Submarine);
    window->draw(*this->Spaceship);

    window->draw(*this->Arcade);
    window->draw(*this->Classic);

    window->draw(*util.getMuteButton());
}

void StatePlayConfig::destroy(sf::RenderWindow *window) {
    delete this->theme;
    delete this->fighter;
    delete this->gamemode;

    delete this->WaterTheme;
    delete this->SpaceTheme;

    delete this->Submarine;
    delete this->Spaceship;

    delete this->Arcade;
    delete this->Classic;

    for (int i = sizeof(PictureTexture) / sizeof(*PictureTexture) - 1; i >= 0; --i) {
        delete this->PictureButtons[i];
        delete this->PictureTexture[i].buttonMouseOver;
        delete this->PictureTexture[i].buttonNormal;
    }
    for (int i = sizeof(menuTextures) / sizeof(*menuTextures) - 1; i >= 0; --i) {
        delete this->menuButtons[i];
        delete this->menuTextures[i].buttonClicked;
        delete this->menuTextures[i].buttonMouseOver;
        delete this->menuTextures[i].buttonNormal;
    }

    delete this->background;
    delete this->bgTexture;
}

void StatePlayConfig::handleEvent(sf::RenderWindow *window, sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        //Back on escapekey
        if (event.key.code == machine.keybindMap->find("back")->second.second) {
            machine.setState(new StateMainMenu);
            return;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        util.checkMuteMouseClick(window, event, machine.mutedPointer);
        for (unsigned int i = 0; i < sizeof(menuTextures) / sizeof(*menuTextures); ++i)
            if (util.checkMouseclick(menuButtons[i], event)) {
                switch (i) {
                    //playknappen trykket
                    case 0: //ARCADE
                        if (selected_Gamemode == 4) {
                            machine.selectedObjectsPointer->selectedGamemode = 1;
                            machine.setState(new StateGameMode1);
                            return;
                        } else { //CLASSIC
                            machine.selectedObjectsPointer->selectedGamemode = 2;
                            machine.setState(new StateGameMode2);
                            return;
                        }

                    case 1:
                        machine.setState(new StateMainMenu);
                        return;
                        //Returnknappen trykket
                    default:break;
                }
            }
        for (unsigned int i = 0; i < sizeof(PictureTexture) / sizeof(*PictureTexture); ++i)
            if (util.checkMouseclick(PictureButtons[i], event)) {
                switch (i) {
                    case 0:
                        selected_Theme = i;
                        machine.selectedObjectsPointer->selectedTheme = 0;
                        break;
                    case 1:
                        selected_Theme = i;
                        machine.selectedObjectsPointer->selectedTheme = 1;
                        break;
                    case 2:
                        selected_Fighter = i;
                        machine.selectedObjectsPointer->selectedFighter = 0;
                        break;
                    case 3:
                        selected_Fighter = i;
                        machine.selectedObjectsPointer->selectedFighter = 1;
                        break;
                    case 4:
                        selected_Gamemode = i;
                        break;
                    case 5:
                        selected_Gamemode = i;
                        break;
                    default:break;
                }
            }
    }
}

void StatePlayConfig::reinitialize(sf::RenderWindow *window) {
    destroy(window);
    initialize(window);
}
