#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "./GameField.hpp"
#include "./EndRound.hpp"
#include "./EndGame.hpp"
#include "./EndQuickGame.hpp"
#include "./GameInformation.hpp"
#include "./TimeAndScore.hpp"
#include "../PopWindow.hpp"
#include "../../GameStack.hpp"
#include "../../Particulars.hpp"
#include "../../Transition.hpp"

namespace game
{
    class Pause;

    /**
     * @brief Класс Choice представляет окно выбора в игре.
     *        Он унаследован от класса PopWindow.
     */
    class Choice : public PopWindow
    {
    private:

        /**
         * @brief Структура, описывающая внутреннее украшение окна Choice.
         *        Содержит параметры для расположения элементов в окне.
         */
        struct Decor
        {
            const float titlePositionOnOY = 45.f;          ///< Позиция заголовка по вертикали
            const float stepBetweenTitleAndButtons = 60.f; ///< Расстояние между заголовком и кнопками
            const float stepBetweenButtons = 50.f;         ///< Шаг между кнопками
            float margin = 250.f;                          ///< Внешний отступ
        } Decor;

        game::Rectangle _background;          ///< Фон окна
        Text _title;                          ///< Текст заголовка
        std::vector<ButtonWithText> _buttons; ///< Вектор кнопок с текстом

        /**
         * @brief Инициализирует окно Choice. 
         *        Размещает компоненты окна и настраивает их.
         */
        void init();

        /**
         * @brief Выравнивает элементы окна в соответствии с установленными параметрами Decor.
         */
        void Align();

    public:
        /**
         * @brief Конструктор для создания объекта окна Choice.
         * 
         * @param gameStack Указатель на игровой стек, к которому принадлежит окно.
         * @param title     Текст, отображаемый в заголовке окна.
         * @param buttons   Вектор кнопок с текстом, отображаемых в окне.
         */
        Choice(GameStack* gameStack, Text title, std::vector<ButtonWithText> buttons);

        /**
         * @brief Деструктор для окна Choice.
         */
        ~Choice() {};

        /**
         * @brief Получает размер окна Choice.
         * 
         * @return Размер окна в виде вектора (ширина, высота).
         */
        sf::Vector2f GetSize() const override
        {
            return {_background.getBounds().width, _background.getBounds().height};
        }

        /**
         * @brief Устанавливает позицию окна на экране.
         * 
         * @param position Позиция, куда следует поместить верхний левый угол окна.
         */
        void SetPosition(const sf::Vector2f& position) override
        {
            SetOffset(position.x - _background.GetPosition().x, position.y - _background.GetPosition().y);
        }

        /**
         * @brief Устанавливает смещение окна на экране.
         * 
         * @param OXOffset Смещение по горизонтали.
         * @param OYOffset Смещение по вертикали.
         */
        void SetOffset(float OXOffset, float OYOffset);

         /**
         * @brief Отрисовывает задний фон окна.
         * 
         * @param target Указатель на объект, на который будет произведена отрисовка.
         */
        void DrawBackWindow(sf::RenderTarget* target) override
        {
            GetGameStack()->Penultimate()->Draw(target);
        }

        /**
         * @brief Отрисовывает всплывающее окно.
         * 
         * @param target Указатель на объект, на который будет произведена отрисовка.
         */
        void DrawPopupWindow(sf::RenderTarget* target) override;

        /**
         * @brief Отрисовывает окно.
         * 
         * @param target Указатель на объект, на который будет произведена отрисовка.
         */
        void Draw(sf::RenderTarget* target) override;

        /**
         * @brief Обрабатывает событие в окне.
         * 
         * @param event        Событие для обработки.
         * @param mousePositon Позиция указателя мыши в окне на момент события.
         * 
         * @return true, если событие было обработано, иначе false.
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon) override;

        /**
         * @brief Обновляет окно Choice.
         * 
         * @param dt Время с момента последнего обновления окна.
         */
        void Update(float dt) override { return; }
    };

    /**
     * @brief Класс GamingDisplay представляет экран игры.
     *        Унаследован от класса game::State.
     */
    class GamingDisplay : public game::State
    {
    private:

        /**
         * @brief Структура Decor содержит параметры для оформления экрана.
         *        Здесь определены размеры и отступы для кнопок и других элементов.
         */
        struct Decor
        {
            float buttonMargin = 30.f;                                  ///< Отступ между кнопками
            sf::FloatRect buttonSize = {0.f, 0.f, 90.f, 90};            ///< Размер кнопок
            sf::FloatRect sizeOfButtonsInPause = {0.f, 0.f, 600.f, 90}; ///< Размер кнопок в режиме паузы
            float buttonRadius = 15.f;                                  ///< Радиус кнопок
            float stepBetweenGameInformationFileds = 100.f;             ///< Шаг между информационными полями
        } Decor; ///< Экземпляр структуры Decor

        CellDefinitions _playerColor = GameSetup::GetOpponentMoveColor() == MoveColor::Black ? CellDefinitions::White : CellDefinitions::Black;   ///< Цвет игрока
        CellDefinitions _opponentColor = GameSetup::GetOpponentMoveColor() == MoveColor::Black ? CellDefinitions::Black : CellDefinitions::White; ///< Цвет оппонента

        CellDefinitions _moveColor = CellDefinitions::Black; ///< Цвет текущего хода, по умолчанию черный

        int _currentRound = 1;     ///< Текущий раунд
        bool _isRoundOver = false; ///< Флаг, показывающий, завершен ли раунд

        GameField _gameField;       ///< Игровое поле
        TimeAndScore _timeAndScore; ///< Время и счет

        std::vector<std::unique_ptr<gameInformation::IGameInformation>> _leftColumn;  ///< Левая колонка информации
        std::vector<std::unique_ptr<gameInformation::IGameInformation>> _rightColumn; ///< Правая колонка информации

        ButtonWithIcon _pause;               ///< Кнопка "пауза"
        std::vector<sf::Sprite> _animations; ///< Вектор спрайтов для анимации

        sf::VertexArray _background = sf::VertexArray(sf::PrimitiveType::TriangleFan); ///< Массив вершин для заднего фона

        /**
         * @brief Метод init() производит инициализацию экрана.
         */
        void init();

        /**
         * @brief Метод Align() выравнивает элементы на экране.
         */
        void Align();
    public:

        /**
         * @brief Конструктор по умолчанию для класса GamingDisplay.
         */
        GamingDisplay() = default;

        /**
         * @brief Деструктор класса GamingDisplay.
         */
        ~GamingDisplay() {}

        /**
         * @brief Конструктор класса GamingDisplay с параметром.
         * 
         * @param gameStack Указатель на игровой стек.
         */
        GamingDisplay(GameStack* gameStack);

        /**
         * @brief Метод Flip() отвечает за переключение экрана.
         * 
         * @param flag Флаг переключения.
         */
        void Flip(bool flag = true);

        /**
         * @brief Метод FlipAnimation() производит анимацию переключения экрана.
         */
        void FlipAnimation();

        /**
         * @brief Метод GetCurrentRound() возвращает текущий раунд.
         * 
         * @return Текущий раунд.
         */
        int GetCurrentRound() const { return _currentRound; }

        /**
         * @brief Метод GetGameField() возвращает игровое поле.
         * 
         * @return Ссылка на игровое поле.
         */
        game::GameField& GetGameField();

        /**
         * @brief Метод GetMoveColor() возвращает цвет текущего хода.
         * 
         * @return Ссылка на цвет текущего хода.
         */
        CellDefinitions& GetMoveColor();

        /**
         * @brief Метод GetOpponentColor() возвращает цвет оппонента.
         * 
         * @return Ссылка на цвет оппонента.
         */
        CellDefinitions& GetOpponentColor();

        /**
         * @brief Метод GetPlayerColor() возвращает цвет игрока.
         * 
         * @return Ссылка на цвет игрока.
         */
        CellDefinitions& GetPlayerColor();

        /**
         * @brief Метод GetPlayerRoundScore() возвращает счет игрока в текущем раунде.
         * 
         * @return Счет игрока в текущем раунде.
         */
        int GetPlayerRoundScore() const;

        /**
         * @brief Метод GetOpponentRoundScore() возвращает счет оппонента в текущем раунде.
         * 
         * @return Счет оппонента в текущем раунде.
         */
        int GetOpponenRoundScore() const;

        /**
         * @brief Метод GetPlayerScore() возвращает общий счет игрока.
         * 
         * @return Общий счет игрока.
         */
        int GetPlayerScore() const { return _timeAndScore.GetPlayerScore(); }

        /**
         * @brief Метод GetOpponentScore() возвращает общий счет оппонента.
         * 
         * @return Общий счет оппонента.
         */
        int GetOpponentScore() const { return _timeAndScore.GetOpponentScore(); }

        /**
         * @brief Метод GetGameTime() возвращает текущее время игры.
         * 
         * @return Текущее время игры.
         */
        sf::String GetGameTime() const { return _timeAndScore.GetTime(); }

        /**
         * @brief Метод DrawWithoutAnimation() отвечает за отрисовку экрана без анимации.
         * 
         * @param target Цель для отрисовки.
         */
        void DrawWithoutAnimation(sf::RenderTarget* target);

        /**
         * @brief Метод Draw() отвечает за отрисовку экрана.
         * 
         * @param target Цель для отрисовки.
         */
        void Draw(sf::RenderTarget* target) override;

        /**
         * @brief Метод Restart() перезапускает игру.
         */
        void Restart();

        /**
         * @brief Метод RestartRound() перезапускает текущий раунд.
         */
        void RestartRound();

        /**
         * @brief Метод StartNextRound() начинает следующий раунд.
         */
        void StartNextRound();

        /**
         * @brief Метод UpdateGameField() обновляет игровое поле.
         */
        void UpdateGameField();

        /**
         * @brief Метод Update() обновляет экран с учетом времени.
         * 
         * @param dt Время с момента последнего обновления.
         */
        void Update(float dt) override;

        /**
         * @brief Метод HandleEvent() обрабатывает события, происходящие на экране.
         * 
         * @param event        Событие для обработки.
         * @param mousePositon Позиция курсора мыши.
         * 
         * @return Результат обработки события (успешно/неуспешно).
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon) override;
    };
}

#endif