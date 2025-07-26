#ifndef END_GAME_HPP
#define END_GAME_HPP

#include <SFML/Graphics.hpp>
#include "./GameInformation.hpp"
#include "../PopWindow.hpp"
#include "../../Transition.hpp"
#include "../../Particulars.hpp"
#include "../../Setup/ResultsSetup.hpp"

namespace game
{

    /**
     * @brief Класс отображения победителя.
     *        Этот класс отвечает за отображение победителя. Включает в себя логику расположения 
     *        элементов на экране и их отображение, а также методы для установки позиции и смещения.
     */
    class Winner
    {
    private:
        struct Decor
        {
            sf::FloatRect backgroundSize = {0.f, 0.f, 350.f, 350.f}; ///< Размер фона.
            float backgroundRadius = 15.f;                           ///< Радиус скругления фона.
            float sizeBetweenAvatarAndName = 20.f;                   ///< Расстояние между аватаром и именем.
            float padding = 30.f;                                    ///< Отступ.
        } Decor;                                                     ///< Декоративные параметры.

        Text _winnerName;         ///< Текст с именем победителя.
        sf::Sprite _winnerAvatar; ///< Спрайт аватара победителя.
        Rectangle _background;    ///< Фон.
        sf::Sprite _cup;          ///< Спрайт кубка.

        void init();              ///< Инициализация объекта.
        void Align();             ///< Выравнивание.
    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        Winner() = default;

        /**
         * @brief Конструктор класса Winner.
         * 
         * @param winnerName   Имя победителя.
         * @param winnerAvatar Аватар победителя в виде спрайта.
         */
        Winner(Text winnerName, sf::Sprite winnerAvatar);

        ~Winner() {} ///< Деструктор.

        /**
         * @brief  Получить границы.
         * @return Границы фона.
         */
        sf::FloatRect GetBounds() const { return _background.getBounds(); }

        /**
         * @brief Установить позицию.
         * 
         * @param x Координата X.
         * @param y Координата Y.
         */
        void SetPosition(float x, float y) { SetOffset({x - _background.GetPosition().x, y - _background.GetPosition().y}); }

        /**
         * @brief Установить смещение для каждого элемента окна.
         * 
         * @param offset Смещение для установки.
         */
        void SetOffset(sf::Vector2f offset);

        /**
         * @brief Отрисовать элементы окна.
         * 
         * @param target Указатель на объект, на который будет происходить отрисовка.
         */
        void Draw(sf::RenderTarget* target) const;
    };

    class GamingDisplay; ///< Объявление класса GamingDisplay.
    
    /**
     * @brief Класс для отображения экрана завершения игры.
     *        Класс, управляющий отображением экрана завершения игры, включая логику расположения 
     *        и вывода элементов, методы обновления, обработки событий и другое.
     */
    class EndGame : public PopWindow
    {
    private:
        struct Decor
        {
            float titlePositionOnOY = 40.f;                     ///< Положение заголовка по оси OY.
            float stepBetweenTextFields = 40.f;                 ///< Расстояние между текстовыми полями.
            float margin = 80.f;                                ///< Отступ.
            float stepBetweenAvatarAndName = 20.f;              ///< Расстояние между аватаром и именем.
            float backgroundWidth = 1200.f;                     ///< Ширина фона.
            float backgroundRadius = 30.f;                      ///< Радиус скругления фона.
            sf::FloatRect buttonSize = {0.f, 0.f, 500.f, 80.f}; ///< Размер кнопки.
            float buttonRadius = 15.f;                          ///< Радиус кнопки.
        } Decor;                                                ///< Декоративные параметры.

        GamingDisplay* _gamingDisplay;  ///< Объект отображения игры.
        Rectangle _background;          ///< Фон.
        Text _title;                    ///< Заголовок.
        Winner _winner;                 ///< Объект победителя.
        Text _draw;                     ///< Текст о ничьей.
        Score _gameScore;               ///< Очки игры.
        ButtonWithText _backToMainMenu; ///< Кнопка "В главное меню".
        ButtonWithText _retry;          ///< Кнопка "Повторить".

        void init();  ///< Инициализация объекта.
        void Align(); ///< Выравнивание.

    public:
        EndGame() = default; ///< Конструктор по умолчанию.

        /**
         * @brief Конструктор класса EndGame.
         * 
         * @param gameStack     Стек игры.
         * @param gamingDisplay Отображение игры.
         */
        EndGame(game::GameStack* gameStack, GamingDisplay* gamingDisplay);

        ~EndGame(); ///< Деструктор.

        /**
         * @brief  Метод получения размера окна.
         * @return Возвращает размер окна в виде вектора (ширина, высота).
         */
        sf::Vector2f GetSize() const override;

        /**
         * @brief Метод установки смещения для всех компонентов окна.
         * 
         * @param offset Вектор смещения (x, y).
         */
        void SetOffset(sf::Vector2f offset);

        /**
         * @brief Метод установки позиции окна.
         * 
         * @param position Позиция окна.
         */
        void SetPosition(const sf::Vector2f& position) override;

        /**
         * @brief Метод отрисовки окна.
         * 
         * @param target Цель отрисовки.
         */
        void Draw(sf::RenderTarget* target) override;

        /**
         * @brief Метод отрисовки заднего окна из стека игры.
         * 
         * @param target Цель отрисовки.
         */
        void DrawBackWindow(sf::RenderTarget* target) override;

        /**
         * @brief Метод отрисовки плавающего окна.
         * 
         * @param target Цель отрисовки.
         */
        void DrawPopupWindow(sf::RenderTarget* target) override;

        /**
         * @brief Обновить экран завершения игры.
         * 
         * @param dt Время обновления.
         */
        void Update(float dt) override;

        /**
         * @brief Метод обработки событий для плавающего окна.
         * 
         * @param event         Событие.
         * @param mousePosition Позиция курсора.
         * 
         * @return Возвращает true, если обработка события прошла успешно, иначе false.
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon) override;
    };
}

#endif