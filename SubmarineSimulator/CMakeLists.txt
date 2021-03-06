cmake_minimum_required(VERSION 3.6)
project(SubmarineSimulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCE_FILES
        Graphics Audio

        "Source/main.cpp"
        "Include/json/json.h"
        "Include/json/json-forwards.h"
        "Source/jsoncpp.cpp"

        #Core Headers
        "Include/Core/app.h"                   "Source/Core/app.cpp"
        "Include/Core/entity.h"                "Source/Core/entity.cpp"
        "Include/Core/entityManager.h"         "Source/Core/entityManager.cpp"
        "Include/Core/machine.h"               "Source/Core/machine.cpp"
        "Include/Core/playerLives.h"           "Source/Core/playerLives.cpp"
        "Include/Core/state.h"
        "Include/Core/score.h"                 "Source/Core/score.cpp"
        "Include/Core/utilities.h"
        "Include/Core/audioLoader.h"           "Source/Core/audioLoader.cpp"
        "Include/Core/pauseableClock.h"           "Source/Core/pauseableClock.cpp"

        #Entities Headers
        "Include/Entities/indestructableObject.h"          "Source/Entities/indestructableObject.cpp"
        "Include/Entities/boss.h"             "Source/Entities/boss.cpp"
        "Include/Entities/bullet.h"            "Source/Entities/bullet.cpp"
        "Include/Entities/player.h"            "Source/Entities/player.cpp"
        "Include/Entities/enemy.h"             "Source/Entities/enemy.cpp"
        "Include/Entities/enemy2.h"            "Source/Entities/enemy2.cpp"
        "Include/Entities/healthPack.h"        "Source/Entities/healthPack.cpp"
        "Include/Entities/dynamicBar.h"        "Source/Entities/dynamicBar.cpp"


        #State Headers
        "Include/States/stateGameMode1.h"      "Source/States/stateGameMode1.cpp"
        "Include/States/stateGameMode2.h"      "Source/States/stateGameMode2.cpp"
        "Include/States/stateGameOver.h"       "Source/States/stateGameOver.cpp"
        "Include/States/stateCredits.h"        "Source/States/stateCredits.cpp"
        "Include/States/stateHighscore.h"      "Source/States/stateHighscore.cpp"
        "Include/States/stateKeybindings.h"    "Source/States/stateKeybindings.cpp"
        "Include/States/statePlayConfig.h"     "Source/States/statePlayConfig.cpp"
        "Include/States/stateMainMenu.h"       "Source/States/stateMainMenu.cpp"
        "Include/States/stateSettings.h"       "Source/States/stateSettings.cpp" Source/Core/utilities.cpp Source/States/stateHelp.cpp Include/States/stateHelp.h Source/Entities/shieldEntity.cpp Include/Entities/shieldEntity.h Source/States/stateCredits.cpp Include/States/stateCredits.h)




add_executable(SubmarineSimulator ${SOURCE_FILES})

# Link with SFML dependencies
target_link_libraries(SubmarineSimulator sfml-graphics sfml-window sfml-system sfml-audio)