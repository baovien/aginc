#include <cstring>
#include "../../Include/States/stateGameMode1.h"
#include "../../Include/States/stateMainMenu.h"
#include "../../Include/States/StateGameOver.h"

void StateGameMode1::initialize(sf::RenderWindow *window) {
    //TODO:
    sl.LoadSounds();
    sl.PlaySound(sl.ARCADE);

    sf::View newView( sf::FloatRect( 0, 0, window->getSize().x, window->getSize().y ) );
    window->setView(newView);

    memset(machine.keyPressed, 0, sizeof(machine.keyPressed)); //For at tastetrykk gjort i andre states ikke skal beholdes

    this->bgTexture = new sf::Texture();
    this->bgTexture->loadFromFile("Graphics/Sprites/bg_purple.png");

    this->background = new sf::Sprite();
    this->background->setTexture(*this->bgTexture);
    this->background->scale(window->getSize().x/background->getGlobalBounds().width,window->getSize().y/background->getGlobalBounds().height);
    util = new Utilities;
    this->font = new sf::Font();
    this->font->loadFromFile("Graphics/font.ttf");

    this->score = new Score(*font, 32U);
    this->score->setPosition(20, 5);

    this->lives = new Lives(*font, 32U);
    this->lives->setPosition(window->getSize().x - this->lives->getGlobalBounds().width - 20, 5);

    manager = new EntityManager();
    boss = new Boss(this->manager);
    this->manager->addEntity("boss", new Boss(this->manager));
    this->player =  new Player(this->lives, this->score, this->manager, window->getSize().x /2, window->getSize().y/2, window, 1);
    this->manager->addEntity("ship", this->player);

    this->pausedText = new sf::Text("Paused\nPress Q to Quit", *font, 32U);
    this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
    this->pausedText->setPosition(window->getSize().x / 2, window->getSize().y / 2);
}

void StateGameMode1::update(sf::RenderWindow *window)
{
    if (!util->paused) //Stopper spillet fra å oppdateres når det pauses
    {
        this->manager->updateEntity(window);
        this->score->updateScore();
        this->lives->updateLife();
    }
    else if(machine.keyPressed[sf::Keyboard::Q])
        machine.setState(new StateMainMenu());

    if (machine.keyPressed[sf::Keyboard::P] || machine.keyPressed[sf::Keyboard::Escape])
    {
        memset(machine.keyPressed, 0, sizeof(machine.keyPressed));
        util->pauseScreen();                        //Kaller pausefunksjonen
    }

    if(this->lives->getValue() <= 0) {
        machine.setGameOverScore(this->score->getValue());
        machine.setState(new StateGameOver);
        return;
    }
    //Spawn enemies and asteroids randomly
    sf::Time elapsed1 = clock.getElapsedTime(); //Tar her her opp verdien som ligger i klokk
    sf::Time elapsed2 = bossclock.getElapsedTime(); //Tar her her opp verdien som ligger i klokk

    if(rand() % 1000 < 2){
        enemyObject = new EnemyObject();
        this->manager->addEntity("Enemy", enemyObject);
        this->enemyObject->setEnemy(this->player);
    }

    if(elapsed1.asMicroseconds() > 3000000) //Sjekker om verdien til clock er mer enn 3 sekunder
    {
        this->manager->addEntity("Asteroid", new AsteroidObject(0,0)); //er clock mer enn 3 sekunder lager jeg en ny astroide
        clock.restart(); //restarter clock(nullstiller)
    }

    if(elapsed2.asMicroseconds() > 15000000) //Sjekker om verdien til clock er mer enn 3 sekunder
    {
        this->manager->addEntity("Boss", new Boss(this->manager));
        bossclock.restart(); //restarter clock(nullstiller)
    }
}

void StateGameMode1::render(sf::RenderWindow *window)
{
    window->draw(*this->background);
    window->draw(*this->score);
    window->draw(*this->lives);
    this->manager->renderEntity(window);

    if (util->paused)
    {
        window->draw(*this->pausedText);
    }
}

void StateGameMode1::destroy(sf::RenderWindow *window)
{
    delete this->lives;
    delete this->score;
    delete this->util;
    delete this->pausedText;
    delete this->font;
    delete this->background;
    delete this->manager;
    //TODO
    sl.~SoundLoader();
}