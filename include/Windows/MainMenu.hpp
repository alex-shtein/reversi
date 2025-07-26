#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include "./GameParameters.hpp"
#include "./Settings.hpp"
#include "./ExitWindow.hpp"
#include "./ReversiTitle.hpp"
#include "../Particulars.hpp"
#include "../Transition.hpp"
#include "./Statistics.hpp"
#include "./Test.hpp"

namespace game
{

    /**
     * @brief Класс MainMenu представляет собой основное меню игры.
     */
    class MainMenu : public ReversiTitle
    {
    private:

        /**
         * @brief Структура MainMenuDesignSettings содержит настройки дизайна элементов основного меню.
         */
        struct MainMenuDesignSettings
        {
            const float stepBetweenTitleAndButtons = 80.f; ///< Шаг между заголовком и кнопками
            const float stepBetweenButtons = 40.f;         ///< Шаг между кнопками

            sf::FloatRect buttonSize = sf::FloatRect({0.f, 0.f, 400.f, 90.f}); ///< Размер кнопок
            float buttonRadius = 15.f;                                         ///< Радиус кнопок
        } Decor;

        ButtonWithText _play;       ///< Кнопка "Играть"
        ButtonWithText _statistics; ///< Кнопка "Статистика"

        ButtonWithIcon _exit;       ///< Кнопка "Выход"
        ButtonWithIcon _settings;   ///< Кнопка "Настройки"

        void init(); ///< Инициализация основного меню
    public:

        /**
         * @brief Конструктор класса MainMenu.
         * 
         * @param gameStack Указатель на игровой стек.
         */
        MainMenu(game::GameStack* gameStack);

        ~MainMenu() override {}; ///< Деструктор класса MainMenu

        void AlignWidth(); ///< Выравнивание ширины элементов основного меню

        void Align(); ///< Выравнивание элементов основного меню

        void Draw(sf::RenderTarget* target) override; ///< Отрисовка основного меню

        void Update(float dt) override { return; } ///< Обновление основного меню

        /**
         * @brief Обработка событий для основного меню.
         * 
         * @param event        Событие ввода от пользователя.
         * @param mousePositon Позиция указателя мыши.
         * 
         * @return true, если событие было обработано, иначе false.
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon);
    };
}

#endif