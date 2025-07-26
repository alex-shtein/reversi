#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <fstream>
#include "../../Particulars.hpp"
#include "../../Setup/GameSetup.hpp"
#include "../../Setup/BoardSetup.hpp"

namespace game
{
    
    /**
     * @brief Перечисление, представляющее различные состояния клеток.
     */
    enum class CellDefinitions : int
    {
        Black = -1, ///< Черная клетка
        White = 1,  ///< Белая клетка
        Empty = 0,  ///< Пустая клетка
        Hole = 2    ///< Дырка или отсутствие клетки
    };

    /**
     * @brief Класс, представляющий фишку на игровом поле.
     */
    class Chip
    {
    private:
        CellDefinitions _cellItem; ///< Тип фишки
        sf::Sprite _chipSprite;    ///< Спрайт фишки для отображения в графическом интерфейсе
    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        Chip() = default;

        /**
         * @brief Конструктор с параметром, устанавливающий тип фишки.
         * 
         * @param cellItem Тип фишки.
         */
        explicit Chip(CellDefinitions cellItem)
            : _cellItem(cellItem)
        {
            SetCellItem(cellItem);
        };

        /**
         * @brief Деструктор класса.
         */
        ~Chip() {}

        /**
         * @brief Установка оригинала спрайта для корректного отображения.
         */
        void Origin()
        {
            _chipSprite.setOrigin(_chipSprite.getGlobalBounds().width / 2.f, _chipSprite.getGlobalBounds().height / 2.f);
        }

        /**
         * @brief Метод для установки типа фишки.
         * 
         * @param cellItem Тип фишки.
         */
        void SetCellItem(CellDefinitions cellItem);

        /**
         * @brief Метод для установки спрайта фишки.
         * 
         * @param sprite Спрайт фишки.
         */
        void SetSprite(const sf::Sprite& sprite);

        /**
         * @brief Установка позиции фишки по координатам x и y.
         * 
         * @param x Координата X.
         * @param y Координата Y.
         */
        void SetPosition(float x, float y) { _chipSprite.setPosition(x, y); }

        /**
         * @brief Отображение фишки на указанной цели.
         * 
         * @param target Цель для отображения.
         */
        void Draw(sf::RenderTarget* target) const { target->draw(_chipSprite); }

        /**
         * @brief Получение типа фишки.
         * 
         * @return Тип фишки.
         */
        CellDefinitions GetCellDefinition() const { return _cellItem; }
    };

    /**
     * @brief Класс, представляющий отдельную ячейку игрового поля.
     */
    class Cell
    {
    public:

        /**
         * @brief Структура, содержащая опции для ячейки.
         */
        struct CellOptions
        {
            /**
             * @brief Конструктор для опций ячейки.
             * 
             * @param backgroundColor Цвет фона ячейки.
             * @param size            Размер ячейки.
             * @param cellItem        Тип ячейки (черная, белая и т.д.).
             */
            CellOptions(sf::Color backgroundColor, sf::Vector2f size, CellDefinitions cellItem)
                : _backgroundColor(backgroundColor), _size(size), _cellItem(cellItem)
            {};

            sf::Color _backgroundColor; ///< Цвет фона
            sf::Vector2f _size;         ///< Размер ячейки
            CellDefinitions _cellItem;  ///< Тип ячейки
        };

    private:
        sf::RectangleShape _background;                  ///< Прямоугольник фона ячейки
        Chip _chip;                                      ///< Игровая фишка в ячейке
        sf::CircleShape _tip;                            ///< Отображение подсветки ячейки (например, возможного хода)

        sf::Vector2i _coordinates;                       ///< Координаты ячейки

        std::vector<std::vector<game::Cell>>& _cells;    ///< Ссылка на ячейки игрового поля

        CellDefinitions& _playerColor;                   ///< Цвет игрока
        CellDefinitions& _opponentColor;                 ///< Цвет противника
        CellDefinitions& _moveColor;                     ///< Цвет хода

        std::vector<Cell*>& _cellsWithFlippedChips;      ///< Ссылка на ячейки с перевернутыми фишками

        const int fieldSize = GameSetup::GetFieldSize(); ///< Размер игрового поля

        /**
         * @brief Инициализация ячейки.
         */
        void init();

    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        Cell() = default;

        /**
         * @brief Конструктор с параметрами.
         * 
         * @param cellOptions           Опции ячейки.
         * @param coordinates           Координаты ячейки.
         * @param cells                 Ссылка на ячейки игрового поля.
         * @param playerColor           Цвет игрока.
         * @param opponentColor         Цвет противника.
         * @param moveColor             Цвет хода.
         * @param cellsWithFlippedChips Ссылка на ячейки с перевернутыми фишками.
         */
        Cell(CellOptions cellOptions, sf::Vector2i coordinates, 
            std::vector<std::vector<game::Cell>>& cells, CellDefinitions& playerColor,
            CellDefinitions& opponentColor, CellDefinitions& moveColor, std::vector<Cell*>& cellsWithFlippedChips);

        /**
         * @brief Деструктор класса.
         */
        ~Cell() {}

        /**
         * @brief Устанавливает спрайт фишки.
         * 
         * @param sprite Спрайт фишки.
         */
        void SetChipSprite(const sf::Sprite& sprite) { _chip.SetSprite(sprite); }

        /**
         * @brief Показывает возможный ход (подсветку) для ячейки.
         * 
         * @param isPossibleMove Флаг: возможен ли ход
         */
        void ShowPossibleMove(bool isPossibleMove);

        /**
         * @brief Проверяет, находится ли шаг в пределах игрового поля.
         * 
         * @param x Координата X.
         * @param y Координата Y.
         * 
         * @return true, если шаг внутри поля, иначе false.
         */
        bool IsStepInBounds(int x, int y) const { return x >= 0 && x < fieldSize && y >= 0 && y < fieldSize; }

        const std::vector<std::pair<int, int>> steps = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};

        /**
         * @brief Проверяет, возможен ли ход.
         * 
         * @return true, если ход возможен, иначе false.
         */
        bool IsPossibleMove();

        /**
         * @brief Возвращает координаты ячейки.
         * 
         * @return Координаты ячейки.
         */
        sf::Vector2i GetCoordinates() const { return _coordinates; }

        /**
         * @brief Выполняет ход (например, поставить фишку, перевернуть фишки вокруг и т.д.).
         */
        void Move();

        /**
         * @brief Обновляет состояние ячейки по позиции мыши и событию.
         * 
         * @param mousePos Позиция мыши.
         * @param event    Событие мыши.
         * 
         * @return true, если обновление прошло успешно, иначе false.
         */
        bool Update(const sf::Vector2f& mousePos, const sf::Event& event);

        /**
         * @brief Устанавливает позицию ячейки по координатам x и y.
         * 
         * @param x Координата X.
         * @param y Координата Y.
         */
        void SetPosition(float x, float y);

        /**
         * @brief Возвращает позицию ячейки.
         * 
         * @return Позиция ячейки.
         */
        sf::Vector2f GetPosition() const { return _background.getPosition(); }

        /**
         * @brief Отображает ячейку на цели.
         * 
         * @param target Цель для отображения.
         */
        void Draw(sf::RenderTarget* target) const;

        /**
         * @brief Добавляет текущую ячейку в контейнер перевернутых фишек.
         */
        void ChangeCellItem() { _cellsWithFlippedChips.push_back(this); }

        /**
         * @brief Устанавливает тип ячейки.
         * 
         * @param cellItem Тип ячейки.
         */
        void SetCellItem(CellDefinitions cellItem) { _chip.SetCellItem(cellItem); }

        /**
         * @brief Возвращает тип ячейки.
         * 
         * @return Тип ячейки.
         */
        CellDefinitions GetCellDefinition() const { return _chip.GetCellDefinition(); }
    };

    /**
     * @brief Класс, представляющий игровое поле.
     */
    class GameField
    {
    private:
        /**
         * @brief Структура, содержащая декоративные опции игрового поля.
         */
        struct Decor
        {
            float backgroundRadius = 15.f;                             ///< Радиус фонового декора
            float stepBetweenCells = 2.5f;                             ///< Расстояние между ячейками
            float cellSize = GameSetup::GetFieldSize() == 8 ? 72.f :   ///< Размер ячейки в зависимости от размера поля
                            GameSetup::GetFieldSize() == 10 ? 60 : 48;

            sf::FloatRect backgroundSize = GameSetup::GetFieldSize() == 8 ? sf::FloatRect{0.f, 0.f, 624.f, 660.f} : ///< Размер фона поля
                                        GameSetup::GetFieldSize() == 10 ? sf::FloatRect{0.f, 0.f, 653.f, 689.f} : 
                                        sf::FloatRect{0.f, 0.f, 634.f, 670.f};

            sf::Color backgroundColor = BoardSetup::GetColors().at(BoardSetup::GetTheme()).x; ///< Цвет фона поля
        } Decor;

        CellDefinitions& _playerColor;   ///< Цвет игрока
        CellDefinitions& _opponentColor; ///< Цвет противника
        CellDefinitions& _moveColor;     ///< Цвет хода

        Rectangle _backgroundField; ///< Фон игрового поля

        std::vector<std::vector<game::Cell>> _cells; ///< Ячейки игрового поля
        std::vector<Cell*> _cellsWithFlippedChips;   ///< Ячейки с перевернутыми фишками

        sf::Thread _computerRun;         ///< Поток для запуска компьютера
        bool _isComputerRunning = false; ///< Флаг: выполняется ли компьютерный ход

        const int fieldSize = GameSetup::GetFieldSize(); ///< Размер игрового поля

        /**
         * @brief Инициализация игрового поля.
         */
        void init();

    public:
        /**
         * @brief Конструктор с параметрами.
         * 
         * @param playerColor      Цвет игрока.
         * @param opponentColor    Цвет противника.
         * @param moveColor        Цвет хода.
         * @param outlineThickness Толщина обводки.
         * @param outlineColor     Цвет обводки.
         */
        GameField(CellDefinitions& playerColor, CellDefinitions& opponentColor, CellDefinitions& moveColor, 
                float outlineThickness = 4.f, sf::Color outlineColor = sf::Color(68, 164, 208));

        /**
         * @brief Деструктор класса.
         */
        ~GameField() {}

        /**
         * @brief Возвращает цвет текущего хода.
         * 
         * @return Цвет текущего хода.
         */
        CellDefinitions GetMoveColor() const { return _moveColor; }

        /**
         * @brief Возвращает цвет противника.
         * 
         * @return Цвет противника.
         */
        CellDefinitions GetOpponentColor() const { return _opponentColor; }

        /**
         * @brief Возвращает цвет игрока.
         * 
         * @return Цвет игрока.
         */
        CellDefinitions GetPlayerColor() const { return _playerColor; }

        /**
         * @brief Возвращает размер игрового поля.
         * 
         * @return Размер игрового поля в виде вектора (ширина, высота).
         */
        sf::Vector2f GetSize() const { return {_backgroundField.getBounds().width, _backgroundField.getBounds().height}; }

        /**
         * @brief Возвращает ячейки с перевернутыми фишками.
         * 
         * @return Ссылка на контейнер ячеек с перевернутыми фишками.
         */
        std::vector<Cell*>& GetCellsWithFlippedChips() { return _cellsWithFlippedChips; }

        /**
         * @brief Устанавливает начальную позицию игрового поля.
         */
        void SetStartPosition();

        /**
         * @brief Отображает игровое поле на цели.
         * 
         * @param target Цель для отображения.
         */
        void Draw(sf::RenderTarget* target) const;

        /**
         * @brief Устанавливает смещение игрового поля.
         * 
         * @param OXOffset Смещение по оси X.
         * @param OYOffset Смещение по оси Y.
         */
        void SetOffset(float OXOffset, float OYOffset);

        /**
         * @brief Устанавливает позицию игрового поля.
         * 
         * @param x Координата X.
         * @param y Координата Y.
         */
        void SetPosition(float x, float y) 
        { 
            SetOffset(x - _backgroundField.GetPosition().x, y - _backgroundField.GetPosition().y);
        }

        /**
         * @brief Сбрасывает подсказки (возможные ходы).
         */
        void ResetTips();

        /**
         * @brief Проверяет, существуют ли возможные ходы.
         * 
         * @return true, если возможные ходы существуют, иначе false.
         */
        bool IsPossibleMoves();

        /**
         * @brief Меняет цвет хода.
         * 
         * @return true, если цвет хода был изменен успешно, иначе false.
         */
        bool ChangeMoveColor();

        /**
         * @brief Класс, представляющий компьютерного игрока.
         */
        class Computer
        {
        private:
            int currentMove; ///< Текущий ход

            int anti = GameSetup::GetGameParametersID() == GameParametersID::Antireversi ? -1 : 1; ///< Коэффициент для антиреверси

            int fieldSize = GameSetup::GetFieldSize();                                    ///< Размер игрового поля
            std::vector<int> Board = std::vector<int>((fieldSize + 2) * (fieldSize + 2)); ///< Игровая доска

            #define WHITE 1 ///< Константа для белой фишки
            #define BLACK 0 ///< Константа для черной фишки
            #define EMPTY 2 ///< Константа для пустой клетки
            #define HOLE 3  ///< Константа для "дырки"
            #define OFF 4   ///< Константа для выключенной клетки

            #define TOPLEFT (fieldSize + 3)                             ///< Верхний левый угол
            #define BOTTOMRIGHT ((fieldSize + 2) * (fieldSize + 1) - 2) ///< Нижний правый угол
            #define TOPRIGHT (2 * fieldSize + 2)                        ///< Верхний правый угол
            #define BOTTOMLEFT ((fieldSize + 2) * fieldSize + 1)        ///< Нижний левый угол

            std::vector<int> Dirs{-fieldSize - 3, -fieldSize - 2, -fieldSize - 1, -1, 1, fieldSize + 1, fieldSize + 2, fieldSize + 3}; ///< Вектор с направлениями движения
        public:

            /**
             * @brief Конструктор по умолчанию.
             */
            Computer() = default;

            /**
             * @brief Конструктор с параметром.
             * 
             * @param gameFiled Ссылка на игровое поле.
             */
            explicit Computer(const GameField& gameFiled);

            /**
             * @brief Деструктор класса.
             */
            ~Computer() {}

            /**
             * @brief Оценка текущей ситуации на игровом поле.
             * 
             * @return Результат оценки
             */
            int Eval();

            /**
             * @brief Проверяет, возможно ли захватить фишки в определенном направлении.
             * 
             * @param move Ход.
             * @param dir  Направление.
             * 
             * @return true, если захват возможен, иначе false.
             */
            bool IsCapture(int move, int dir);

            /**
             * @brief Проверяет, возможно ли захватить фишки в данной клетке.
             * 
             * @param sq Клетка.
             * 
             * @return true, если захват возможен, иначе false.
             */
            bool IsCapture(int sq);

            /**
             * @brief Генерирует ходы.
             * 
             * @param moves Массив для ходов.
             * 
             * @return Количество сгенерированных ходов.
             */
            int GenMoves(int moves[]);

            /**
             * @brief Захват фишек.
             * 
             * @param m    Ход.
             * @param dir  Направление.
             * @param caps Массив для захвата.
             * @param n    Количество захваченных фишек.
             */
            void Capture(int m, int dir, int caps[], int &n);

            /**
             * @brief Выполняет ход.
             * 
             * @param m Ход.
             * @param caps Массив захвата.
             * 
             * @return Результат выполнения хода.
             */
            int MakeMove(int m, int caps[]);

            /**
             * @brief Отменяет ход.
             * 
             * @param m    Ход.
             * @param caps Массив захвата.
             * @param n    Количество захваченных фишек.
             */
            void UnmakeMove(int m, int caps[], int n);

            /**
             * @brief Поиск лучшего хода в заданной глубине.
             * 
             * @param depth Глубина поиска.
             * @param pass  Флаг: пропустить ход.
             * 
             * @return Лучший ход.
             */
            int Search(int depth, bool pass);

            /**
             * @brief Поиск лучшего хода в корне дерева ходов.
             * 
             * @param depth Глубина поиска.
             * 
             * @return Лучший ход.
             */
            int RootSearch(int depth);
        };

        /**
         * @brief Возвращает поток исполнения компьютера.
         * 
         * @return Ссылка на поток исполнения компьютера.
         */
        sf::Thread& GetComputerRunThread() { return _computerRun; }

        /**
         * @brief Устанавливает статус выполнения компьютера.
         * 
         * @param isComputerRunning Флаг: выполняется ли компьютерный ход.
         */
        void SetComputerRunning(bool isComputerRunning) { _isComputerRunning = isComputerRunning; }

        /**
         * @brief Возвращает статус выполнения компьютера.
         * 
         * @return true, если компьютерный ход выполняется, иначе false.
         */
        bool GetComputerRunning() const { return _isComputerRunning; }

        /**
         * @brief Выполняет компьютерный ход.
         */
        void ComputerRun();

        /**
         * @brief Показывает возможные ходы на игровом поле.
         */
        void ShowPossibleMoves();

        /**
         * @brief Обновляет состояние игрового поля по позиции мыши и событию.
         * 
         * @param mousePosition Позиция мыши.
         * @param event         Событие мыши.
         */
        void Update(const sf::Vector2f& mousePosition, const sf::Event& event);

        /**
         * @brief Возвращает ячейку по заданным координатам.
         * 
         * @param coordinates Координаты ячейки.
         * 
         * @return Ссылка на объект ячейки.
         */
        game::Cell& GetCell(const sf::Vector2i& coordinates) { return _cells[coordinates.x][coordinates.y]; }
    };
}

#endif
