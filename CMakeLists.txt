cmake_minimum_required(VERSION 3.20)
project(Reversi)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "/opt/homebrew/Cellar/sfml@2/2.6.2_1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

include_directories(include)

add_executable(
    reversi

    ./src/main.cpp 

    ./include/ResourceLoader.hpp ./src/ResourceLoader.cpp
    ./include/Particulars.hpp ./src/Particulars.cpp
    ./include/Transition.hpp ./src/Transition.cpp
    ./include/GameStack.hpp ./src/GameStack.cpp

    ./include/Setup/GameSetup.hpp ./src/Setup/GameSetup.cpp
    ./include/Setup/PlayerSetup.hpp ./src/Setup/PlayerSetup.cpp
    ./include/Setup/BoardSetup.hpp ./src/Setup/BoardSetup.cpp
    ./include/Setup/ResultsSetup.hpp ./src/Setup/ResultsSetup.cpp
    
    ./include/Windows/GameParameters.hpp ./src/Windows/GameParameters.cpp
    ./include/Windows/ReversiTitle.hpp ./src/Windows/ReversiTitle.cpp
    ./include/Windows/ExitWindow.hpp ./src/Windows/ExitWindow.cpp
    ./include/Windows/PopWindow.hpp ./src/Windows/PopWindow.cpp
    ./include/Windows/Settings.hpp ./src/Windows/Settings.cpp
    ./include/Windows/Statistics.hpp  ./src/Windows/Statistics.cpp
    ./include/Windows/MainMenu.hpp ./src/Windows/MainMenu.cpp
    ./include/Windows/Run.hpp ./src/Windows/Run.cpp
    ./include/Windows/Test.hpp ./src/Windows/Test.cpp

    ./include/Windows/GamingDisplay/GameField.hpp ./src/Windows/GamingDisplay/GameField.cpp
    ./include/Windows/GamingDisplay/GameInformation.hpp ./src/Windows/GamingDisplay/GameInformation.cpp
    ./include/Windows/GamingDisplay/GamingDisplay.hpp ./src/Windows/GamingDisplay/GamingDisplay.cpp
    ./include/Windows/GamingDisplay/TimeAndScore.hpp ./src/Windows/GamingDisplay/TimeAndScore.cpp
    ./include/Windows/GamingDisplay/EndRound.hpp ./src/Windows/GamingDisplay/EndRound.cpp
    ./include/Windows/GamingDisplay/EndQuickGame.hpp ./src/Windows/GamingDisplay/EndQuickGame.cpp
    ./include/Windows/GamingDisplay/EndGame.hpp ./src/Windows/GamingDisplay/EndGame.cpp

    ./include/Windows/SettingsMenu/Slider.hpp ./src/Windows/SettingsMenu/Slider.cpp
    ./include/Windows/SettingsMenu/ChoiceWithSlider.hpp ./src/Windows/SettingsMenu/ChoiceWithSlider.cpp
    ./include/Windows/SettingsMenu/SettingsMenu.hpp ./src/Windows/SettingsMenu/SettingsMenu.cpp
    ./include/Windows/SettingsMenu/ComputerStartColor.hpp ./src/Windows/SettingsMenu/ComputerStartColor.cpp
    ./include/Windows/SettingsMenu/MultiplayerStartColor.hpp ./src/Windows/SettingsMenu/MultiplayerStartColor.cpp
)

target_link_libraries(reversi sfml-graphics sfml-audio sfml-window sfml-system)
