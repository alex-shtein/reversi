#ifndef SETTINGS_MENU_HPP
#define SETTINGS_MENU_HPP

#include "./IGameSetting.hpp"
#include "./ChoiceWithSlider.hpp"
#include "./ComputerStartColor.hpp"
#include "./MultiplayerStartColor.hpp"
#include "../ReversiTitle.hpp"
#include "../GamingDisplay/GamingDisplay.hpp"
#include "../../Transition.hpp"
#include "../../Particulars.hpp"
#include "../../Setup/GameSetup.hpp"


namespace game
{
    /**
     * @brief Класс SettingsMenu, представляющий меню настроек.
     * 
     * @details Унаследован от ReversiTitle.
     */
    class SettingsMenu : public ReversiTitle
    {
    private:

        /**
         * @brief Структура Decor для хранения декоративных параметров меню настроек.
         */
        struct Decor
        {
            float buttonWithIconMargin = 30.f;                                        ///< Отступ для кнопок с иконкой
            sf::FloatRect sizeofButtonWithIcon = sf::FloatRect{0.f, 0.f, 90.f, 90.f}; ///< Размер кнопки с иконкой
            float radiusButtonWithIcon = 15.f;                                        ///< Радиус кнопки с иконкой

            float stepBetweenTitleAndSettings = 80.f; ///< Шаг между заголовком и настройками
            float stepBetweenSettings = 55.f;         ///< Шаг между настройками

            sf::Color settingsColor = sf::Color::White; ///< Цвет настроек
            int settingsFontSize = 40;                  ///< Размер шрифта для настроек
        } Decor;

        ButtonWithIcon _back; ///< Кнопка "назад"
        ButtonWithIcon _play; ///< Кнопка "играть"

        std::vector<game::IGameSetting*> _gameSettings; ///< Вектор игровых настроек

        /**
         * @brief Инициализация меню настроек игры.
         *        Добавляет различные настройки игры, такие как размер поля, количество раундов, сложность игры (для компьютера) и выбор цвета (для мультиплеера).
         *        В зависимости от типа игры добавляет соответствующие элементы настроек.
         */
        void init();


        /**
         * @brief Выравнивание элементов меню настроек на экране.
         *        Выставляет позиции кнопок "Назад" и "Играть", а также настройки игры, чтобы они были выровнены по вертикали.
         */
        void Align();

        /**
         * @brief Получение позиции черной дыры на поле.
         * 
         * @return Позиция черной дыры в виде вектора (x, y).
         */
        sf::Vector2i GetBlackHolePosition() const;

        /**
         * @brief Сохранение конфигураций игры.
         *        Сохраняет выбранные настройки в объект GameSetup в зависимости от типа игры (компьютер или мультиплеер).
         */
        void SaveConfigurations() const;
    public:

        /**
         * @brief Конструктор класса SettingsMenu.
         * 
         * @param gameStack Указатель на игровой стек.
         */
        SettingsMenu(game::GameStack* gameStack);

        /**
         * @brief Деструктор класса SettingsMenu.
         */
        ~SettingsMenu();

        /**
         * @brief Отрисовать меню настроек.
         * 
         * @param target Цель отрисовки.
         */
        void Draw(sf::RenderTarget* target) override;

        /**
         * @brief Обновить меню настроек.
         * 
         * @param dt Время с последнего обновления.
         */
        void Update(float dt) override;

        /**
         * @brief Обработать событие.
         * 
         * @param event        Событие.
         * @param mousePositon Позиция указателя мыши.
         * 
         * @return true, если событие обработано, в противном случае - false.
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon) override;
    };
}

#endif