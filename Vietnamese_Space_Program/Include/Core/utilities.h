#ifndef VIETNAMESE_SPACE_PROGRAM_UTIL_H
#define VIETNAMESE_SPACE_PROGRAM_UTIL_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Utilities {
private:
    sf::Font *font;
    sf::Sprite *muteButton;

    struct muteTextureStruct{
        sf::Texture* buttonNormal;
        sf::Texture* buttonMouseOver;
        sf::Texture* buttonClicked;
    };
    muteTextureStruct muteTextures[2];

    std::map<const std::string, std::tuple<std::string, std::string, std::string>> languageMap =
            {{"submarine simulator", std::make_tuple("Ubatsimulator" , "podmornica simulator", "Simulateur de sous-marin")},
             {"wave: ", std::make_tuple("Bolge: " , "talas: ", "vague: ")},
             {"settings", std::make_tuple("Innstillinger" , "podesavanja", "parametres")},
             {"music", std::make_tuple("Musikk" , "muzika", "la musique")},
             {"controls", std::make_tuple("Kontroller" , "kontrole", "controles")},
             {"reset highscore", std::make_tuple("Reset pallen" , "reset high score ", "Reinitialiser les scores")},
             {"reset controls", std::make_tuple("Reset kontroller" , "reset kontrole ", "Reinitialiser les controles")},
             {"movement", std::make_tuple("Bevegelse" , "pokret", "mouvement")},
             {"menu navigation", std::make_tuple("Menynavigering" , "navigacioni meni ", "Navigation menu")},
             {"up", std::make_tuple("Opp" , "gore", "Up")},
             {"down", std::make_tuple("Ned" , "dole", "en bas")},
             {"left", std::make_tuple("Venstre" , "levo", "a gauche")},
             {"right", std::make_tuple("hoyre" , "u pravu", "droite")},
             {"back", std::make_tuple("Tilbake" , "nazad", "arriere")},
             {"select", std::make_tuple("Velg" , "odabrati", "selectionner")},
             {"pause", std::make_tuple("Pause" , "pauza", "pause")},
             {"shoot", std::make_tuple("Skyt" , "pucati", "tirer")},
             {"key already bound", std::make_tuple("Tast allerede bundet" , "kljuc vec vezan", "Cle deja reliee")},
             {"highscore", std::make_tuple("Pall" , "visoku ocenu", "score eleve")},
             {"arcade", std::make_tuple("Arcade" , "arkada", "Arcade")},
             {"classic", std::make_tuple("Klassisk" , "klasik", "classique")},
             {"player", std::make_tuple("Spiller" , "igrac", "joueur")},
             {"how to play", std::make_tuple("Hvordan spille" , "kako igrati", "comment jouer")},
             {"select theme", std::make_tuple("Velg tema" , "Izaberi temu", "selectionne un theme")},
             {"select gamemode", std::make_tuple("Velg spillmodus" , "izaberite igra rezim", "Selectionner le mode")},
             {"select fighter", std::make_tuple("Velg kjemper" , "izaberite borac", "Choisir un combattant")},
             {"space", std::make_tuple("Rommet" , "prostor", "espace")},
             {"water", std::make_tuple("Vann" , "voda", "eau")},
             {"submarine", std::make_tuple("Ubat" , "podmornica", "Sous-marin")},
             {"spaceship", std::make_tuple("Romskip" , "svemirski brod", "vaisseau spatial")},
             {"lives: ", std::make_tuple("Liv: " , "zivoti: ", "vies: ")},
             {"score: ", std::make_tuple("Poeng" , "skor: ", "But: ")},
             {"game over", std::make_tuple("Spill over" , "kraj igre", "jeu termine")},
             {"lives", std::make_tuple("Liv" , "zivoti", "Vies")},
             {"score", std::make_tuple("Poeng" , "skor", "But")},
             {"paused. press", std::make_tuple("Pauset. Trykk" , "Zastade. presa", "En Pause. Appuyez sur")},
             {" to quit", std::make_tuple(" for menyen" , " da se vratim", " pour quitter")},
             {"gameplay", std::make_tuple("Spill" , "igranja", "Jeu")},
             {"are you sure?", std::make_tuple("Er du sikker?" , "da li ste sigurni?", "etes-vous sur?")},
             {"score", std::make_tuple("1" , "2", "3")},
             {"score", std::make_tuple("1" , "2", "3")},
             {"score", std::make_tuple("1" , "2", "3")}
            };


public:
    bool paused = false;

    sf::Sprite *getMuteButton() const;

    void pauseScreen() {
        //Funksjonen setter og fjerner pause
        paused = !paused;
    }

    void makeMuteButton(sf::RenderWindow* window, bool* mutedPointer);
    void checkMuteMouseOver(sf::RenderWindow* window);
    void checkMuteMouseClick(sf::RenderWindow* window, sf::Event event, bool* mutedPointer);

    //Oversetter spesifike ord
    std::string translate(std::string wordToTranslate, int language);

    //PARAM::::: Texture, scale x, scale y, position x, position y, window
    //Ubrukt
    sf::Sprite *addButton(sf::Texture* texture, float scaleX, float scaleY, float posX, float posY, sf::RenderWindow *window);

    //PARAM::::: Text, textsize, origin x, origin y, position x, position y, window, language int
    //Lager og oversetter teksten
    sf::Text *addText(std::string textContent, unsigned int textSize, int originX, int originY, float posX, float posY, sf::RenderWindow *window, int language);

    //Tar inn sprite og returnerer true om mouseover
    bool checkMouseover(sf::Sprite *buttonSprite, sf::RenderWindow *window);

    //Tar inn sprite og returnerer true om mouseclick
    bool checkMouseclick(sf::Sprite *buttonSprite, sf::Event event);

};

#endif //VIETNAMESE_SPACE_PROGRAM_UTIL_H
