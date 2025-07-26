#ifndef GAME_PARAMETERS_HPP
#define GAME_PARAMETERS_HPP

#include <SFML/Graphics.hpp>
#include "./ReversiTitle.hpp"
#include "./SettingsMenu/SettingsMenu.hpp"
#include "./PopWindow.hpp"
#include "../Particulars.hpp"
#include "../Setup/GameSetup.hpp"
#include "../Transition.hpp"

namespace game
{
    /**
     * @brief Класс GameParameters представляет собой параметры игры.
     */
    class GameParameters : public ReversiTitle
    {
    private:

        /**
         * @brief Структура Decor содержит настройки дизайна элементов окна параметров игры.
         */
        struct Decor
        {
            float ButtonWithIconMargin = 30.f;                                        ///< Отступ между кнопками с иконками
            sf::FloatRect sizeofButtonWithIcon = sf::FloatRect{0.f, 0.f, 90.f, 90.f}; ///< Размер кнопок с иконками
            float radiusButtonWithIcon = 15.f;                                        ///< Радиус кнопок с иконками

            const float stepBetweenTitleAndButtons = 120.f; ///< Шаг между заголовком и кнопками
            const float stepBetweenButtons = 50.f;          ///< Шаг между кнопками

            sf::FloatRect buttonSize = sf::FloatRect(0.f, 0.f, 400.f, 90.f); ///< Размер обычных кнопок
            float buttonRadius = 15.f;                                       ///< Радиус обычных кнопок

            sf::FloatRect modeButtonSize = sf::FloatRect(0.f, 0.f, 700.f, 90.f); ///< Размер кнопок выбора режима
            sf::FloatRect typeButtonSize = sf::FloatRect(0.f, 0.f, 550.f, 90.f); ///< Размер кнопок выбора типа игры

            float margin = 200.f; ///< Отступ
        } Decor;

        sf::Vector2<ButtonWithText> _changeButtons; ///< Кнопки для изменения параметров игры
        game::ButtonWithIcon _back;                 ///< Кнопка "назад"
        game::ButtonWithIcon _next;                 ///< Кнопка "вперед"
        Text _gameParametersText;                   ///< Текст "Параметры игры"
    
        GameParametersID _gameParametersID = GameParametersID::DefaultReversi; ///< ID параметров игры

        Text _gameTypeText;                            ///< Текст "Тип игры"
        GameTypeID _gameTypeID = GameTypeID::Computer; ///< ID типа игры

        std::map<sf::String, GameParametersID> _gameParameters{{L"обычные реверси", GameParametersID::DefaultReversi}, 
                                                    {L"антиреверси", GameParametersID::Antireversi}, 
                                                    {L"реверси с черной дырой", GameParametersID::ReversiWithBlackHole}}; ///< Список параметров игры

        std::map<sf::String, GameTypeID> _gameTypes{{L"игра с компьютером", GameTypeID::Computer}, 
                                                    {L"мультиплеер", GameTypeID::Multiplayer}}; ///< Список типов игры

        void init() { Update(); } ///< Инициализация параметров игры
        void Update(); ///< Обновление параметров игры
    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        GameParameters() = default;

        /**
         * @brief Конструктор класса GameParameters.
         *        Инициализирует объект класса GameParameters с помощью конструктора базового класса ReversiTitle.
         *        Задает параметры кнопок "Назад" и "Далее", а также кнопок "Изменить" для выбора режима и типа игры.
         *        Устанавливает начальные значения для текстовых полей "Режим игры" и "Тип игры".
         * 
         * @param gameStack Указатель на стек игры.
         */
        GameParameters(game::GameStack* gameStack);

        /**
         * @brief Деструктор класса GameParameters.
         */
        ~GameParameters() {}

        /**
         * @brief Выравнивание элементов по ширине окна.
         *        Выставляет позиции кнопок "Назад" и "Далее", а также текстовых полей и кнопок изменения настройки игры, 
         *        чтобы они были выровнены по горизонтали.
         */
        void AlignWidth();


        /**
         * @brief Выравнивание элементов на экране.
         * 
         * Устанавливает позиции элементов на экране, включая кнопки, текстовые поля и заголовок, 
         * чтобы они были выровнены вертикально и по ширине окна игры.
         */
        void Align();

        /**
         * @brief Отрисовка элементов на экране.
         *        Отображает на экране все элементы игровых параметров, включая кнопки, текстовые поля и заголовок.
         * 
         * @param target Цель для отрисовки.
         */
        void Draw(sf::RenderTarget* target) override;

        /**
         * @brief Обновление параметров игры.
         *        Обновляет текстовые описания выбранных параметров игры, таких как режим и тип игры.
         *        Также осуществляет установку соответствующих параметров в объект GameSetup в зависимости от выбранного типа игры.
         */
        void Update(float dt) override { return; }


        /**
         * @brief Обработка событий в окне игровых параметров.
         *        Управляет обработкой событий, таких как нажатие кнопок, обновление значений параметров и закрытие окна.
         * 
         * @param event        Событие, вызванное пользователем.
         * @param mousePositon Текущая позиция курсора.
         * 
         * @return true, если состояние окна должно быть изменено, в противном случае - false.
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon) override;
    };
}

#endif