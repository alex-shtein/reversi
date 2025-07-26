#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include "./SettingsMenu/MultiplayerStartColor.hpp"
#include "./GamingDisplay/GameField.hpp"
#include "./ReversiTitle.hpp"
#include "../Particulars.hpp"
#include "../Transition.hpp"
#include "../Setup/PlayerSetup.hpp"
#include "../Setup/BoardSetup.hpp"

namespace game
{

    /**
     * @brief Класс PlayerNickname представляет элемент интерфейса для ввода имени игрока.
     */
    class PlayerNickname
    {
    private:

        /**
         * @brief Структура Decor содержит параметры для оформления элемента интерфейса.
         */
        struct Decor
        {
            float stepBetweenTitleAndTextBox = 15.f; ///< Шаг между заголовком и текстовым полем.
        } Decor;

        Text _title;      ///< Заголовок элемента.
        TextBox _textBox; ///< Текстовое поле для ввода имени.

        /**
         * @brief Инициализирует элемент интерфейса.
         */
        void init() {}

        /**
         * @brief Выравнивает элементы интерфейса.
         */
        void Align();
    public:

        /**
         * @brief Конструктор по умолчанию для класса PlayerNickname.
         */
        PlayerNickname();

        /**
         * @brief Деструктор для класса PlayerNickname.
         */
        ~PlayerNickname() {}

        /**
         * @brief Отрисовывает элемент интерфейса на указанном окне рендеринга.
         * 
         * @param target Указатель на окно рендеринга.
         */
        void Draw(sf::RenderTarget* target);

        /**
         * @brief Обновляет состояние элемента интерфейса на основе прошедшего времени.
         * 
         * @param dt Прошедшее время с момента последнего обновления в секундах.
         */
        void Update(float dt) 
        { 
            _textBox.Update(dt);
        }

        /**
         * @brief Обновляет состояние элемента интерфейса на основе пользовательского ввода и событий мыши.
         * 
         * @param mousePositon Позиция мыши.
         * @param event        Событие мыши.
         */
        void Update(const sf::Vector2f& mousePositon, const sf::Event& event)
        {
            _textBox.Update(mousePositon, event);
        }

        /**
         * @brief Устанавливает позицию элемента интерфейса.
         * 
         * @param x Координата X позиции.
         * @param y Координата Y позиции.
         */
        void SetPostion(float x, float y)
        {
            SetOffset(x - _title.getPosition().x, y - _title.getPosition().y - GetHeight() / 2.f + _title.getGlobalBounds().height / 2.f);
        }

        /**
         * @brief Устанавливает смещение элемента интерфейса.
         * 
         * @param OXOffset Смещение по оси X.
         * @param OYOffset Смещение по оси Y.
         */
        void SetOffset(float OXOffset, float OYOffset);

        /**
         * @brief Возвращает высоту элемента интерфейса.
         * 
         * @return Высота элемента интерфейса.
         */
        float GetHeight() const 
        {
            return _title.getGlobalBounds().height + Decor.stepBetweenTitleAndTextBox + _textBox.getBounds().height;
        }

        /**
         * @brief Возвращает введенное имя из текстового поля.
         * 
         * @return Введенное имя из текстового поля.
         */
        sf::String GetName() const 
        { 
            return _textBox.GetText(); 
        }

        /**
         * @brief Проверяет, заполнено ли текстовое поле.
         * 
         * @return true, если текстовое поле заполнено, в противном случае - false.
         */
        bool IsFill() const 
        { 
            return _textBox.IsFill(); 
        }
    };

    /**
     * @brief Класс ShowTips представляет элемент интерфейса с подсказкой и двумя кнопками ответа.
     */
    class ShowTips
    {
    private:

        /**
         * @brief Класс ButtonWithAnswer представляет элемент интерфейса кнопки с ответом.
         */
        class ButtonWithAnswer : public ButtonWithText
        {
        private:

            /**
             * @brief Структура Decor содержит параметры для оформления элемента интерфейса.
             */
            struct Decor
            {
                sf::Color blurColor = sf::Color(80, 80, 80, 140); ///< Цвет размытия.
            } Decor;

            Rectangle _blur;                  ///< Область размытия.
            mutable bool _isSelected = false; ///< Флаг выбора.

            /**
             * @brief Инициализирует элемент интерфейса.
             */
            void init() {}

            /**
             * @brief Выравнивает элемент интерфейса.
             */
            void Align() 
            { 
                _blur.SetPosition(GetPosition()); 
            }
        public:

            /**
             * @brief Конструктор по умолчанию.
             */
            ButtonWithAnswer() = default;

            /**
             * @brief Конструктор с параметрами.
             *        Создает кнопку с текстом и ответом для показа подсказок.
             * 
             * @param rectangle          Прямоугольная область кнопки
             * @param radius             Радиус скругления углов кнопки
             * @param text               Текст кнопки
             * @param function           Функция, вызываемая при нажатии на кнопку
             * @param topDefaultColor    Цвет верхней части кнопки по умолчанию
             * @param bottomDefaultColor Цвет нижней части кнопки по умолчанию
             * @param topHoverColor      Цвет верхней части кнопки при наведении
             * @param bottomHoverColor   Цвет нижней части кнопки при наведении
             * @param shadowColor        Цвет тени кнопки
             * @param outlineColor       Цвет обводки кнопки
             * @param outlineThickness   Толщина обводки кнопки
             */
            ButtonWithAnswer(const sf::FloatRect& rectangle, const float& radius, const Text &text, const std::function<void()>& function = [](){}, 
                            sf::Color topDefaultColor = sf::Color(68, 164, 208), 
                            sf::Color bottomDefaultColor = sf::Color(11, 86, 125),
                            sf::Color topHoverColor = sf::Color(24, 110, 151),
                            sf::Color bottomHoverColor = sf::Color(7, 50, 73),
                            sf::Color shadowColor = sf::Color(94, 140, 164, 160),
                            sf::Color outlineColor = sf::Color(14, 52, 74),
                            float outlineThickness = 4.f
                );

            /**
             * @brief Отрисовывает элемент интерфейса на указанном окне рендеринга.
             * 
             * @param target Указатель на окно рендеринга.
             */
            void Draw(sf::RenderTarget* target) const;

            /**
             * @brief Устанавливает позицию элемента интерфейса.
             * 
             * @param x Координата X позиции.
             * @param y Координата Y позиции.
             */
            void SetPosition(float x, float y);

            /**
             * @brief Возвращает флаг выбора элемента интерфейса.
             * 
             * @return Флаг выбора элемента интерфейса.
             */
            bool& GetSelected() const 
            {
                return _isSelected; 
            }
        };
    private:

        /**
         * @brief Структура Decor содержит параметры для оформления элемента интерфейса.
         */
        struct Decor
        {
            float sizeBetweenButtonsAndText = 15.f;                 ///< Расстояние между кнопками и текстом.
            sf::FloatRect buttonSize = sf::FloatRect(0, 0, 90, 90); ///< Размер кнопки.
            float buttonRadius = 15.f;                              ///< Радиус кнопки.
        } Decor;

        Text _title; ///< Текст подсказки.

        ButtonWithAnswer _yes; ///< Кнопка "Да".
        ButtonWithAnswer _no;  ///< Кнопка "Нет".

        /**
         * @brief Инициализирует элемент интерфейса.
         */
        void init();

        /**
         * @brief Выравнивает элемент интерфейса.
         */
        void Align();
    public:

        /**
         * @brief Конструктор по умолчанию для класса ShowTips.
         */
        ShowTips();

        /**
         * @brief Деструктор для класса ShowTips.
         */
        ~ShowTips() {};

        /**
         * @brief Устанавливает позицию элемента интерфейса.
         * 
         * @param x Координата X позиции.
         * @param y Координата Y позиции.
         */
        void SetPosition(float x, float y)
        {
            SetOffset(x - _title.getPosition().x, y - _title.getPosition().y - GetHeight() / 2.f + _title.getGlobalBounds().height / 2.f);
        }

        /**
         * @brief Устанавливает смещение элемента интерфейса.
         * 
         * @param OXOffset Смещение по оси X.
         * @param OYOffset Смещение по оси Y.
         */
        void SetOffset(float OXOffset, float OYOffset);
        
        /**
         * @brief Отрисовывает элемент интерфейса на указанном окне рендеринга.
         * 
         * @param target Указатель на окно рендеринга.
         */
        void Draw(sf::RenderTarget* target);

        /**
         * @brief Обновляет элемент интерфейса на основе положения указателя мыши и событий ввода.
         * 
         * @param mousePos Положение указателя мыши.
         * @param event    Событие ввода.
         */
        void Update(const sf::Vector2f& mousePos, const sf::Event& event);

        /**
         * @brief Возвращает высоту элемента интерфейса.
         * 
         * @return Высота элемента интерфейса.
         */
        float GetHeight() const
        {
            return _title.getGlobalBounds().height + Decor.sizeBetweenButtonsAndText + Decor.buttonSize.height;
        }

        /**
         * @brief Проверяет, показан ли элемент интерфейса.
         * 
         * @return true, если элемент интерфейса показан, в противном случае - false.
         */
        bool IsShowed() const 
        { 
            return _yes.GetSelected(); 
        }
    };

    /**
     * @brief Класс Options представляет элемент интерфейса опций и наследуется от класса ReversiTitle.
     */
    class Options : public ReversiTitle
    {
    private:

        /**
         * @brief Класс GameField представляет игровое поле внутри элемента интерфейса опций.
         */
        class GameField
        {
        private:

            /**
             * @brief Класс Cell представляет отдельную ячейку игрового поля.
             */
            class Cell
            {
            private:

                /**
                 * @brief Класс Chip представляет фишку внутри ячейки.
                 */
                class Chip : public sf::Sprite
                {
                private:
                    CellDefinitions _cellItem; ///< Элемент ячейки.

                public:
                    Chip() = default;

                    /**
                     * @brief Конструктор класса Chip.
                     * 
                     * @param cellItem Элемент ячейки.
                     */
                    explicit Chip(CellDefinitions cellItem)
                        : _cellItem(cellItem)
                    {
                        SetCellItem(cellItem);
                    };

                    ~Chip() {}

                    /**
                     * @brief Устанавливает элемент ячейки.
                     * 
                     * @param cellItem Элемент ячейки.
                     */
                    void SetCellItem(CellDefinitions cellItem);
                };

                sf::RectangleShape _background; ///< Фон ячейки.
                Chip _chip;                     ///< Фишка внутри ячейки.
                sf::CircleShape _tip;           ///< Подсказка.
                sf::Vector2i _coordinates;      ///< Координаты ячейки.

                std::vector<std::vector<Cell>>& _cells; ///< Ссылка на все ячейки игрового поля.

                /**
                 * @brief Инициализирует объект класса Cell.
                 */
                void init();

            public:
                Cell() = default;

                /**
                 * @brief Конструктор класса Cell.
                 * 
                 * @param cellOptions Опции ячейки.
                 * @param coordinates Координаты ячейки.
                 * @param cells       Ссылка на все ячейки игрового поля.
                 */
                Cell(game::Cell::CellOptions cellOptions,
                    sf::Vector2i coordinates, std::vector<std::vector<Cell>>& cells);

                ~Cell() {}

                /**
                 * @brief Устанавливает подсказку для ячейки.
                 */
                void SetTip() 
                { 
                    _tip.setOutlineThickness(2.f); 
                }

                /**
                 * @brief Устанавливает цвет фона ячейки.
                 * 
                 * @param color Цвет фона.
                 */
                void SetBackgroundColor(sf::Color color) 
                { 
                    _background.setFillColor(color); 
                }

                /**
                 * @brief Устанавливает позицию ячейки.
                 * 
                 * @param x Координата X позиции.
                 * @param y Координата Y позиции.
                 */
                void SetPosition(float x, float y);

                /**
                 * @brief Возвращает позицию ячейки.
                 * 
                 * @return Позиция ячейки.
                 */
                sf::Vector2f GetPosition() const 
                { 
                    return _background.getPosition(); 
                }

                /**
                 * @brief Отрисовывает ячейку на указанном окне рендеринга.
                 * 
                 * @param target Указатель на окно рендеринга.
                 */
                void Draw(sf::RenderTarget* target);

                /**
                 * @brief Устанавливает элемент ячейки.
                 * 
                 * @param cellItem Элемент ячейки.
                 */
                void SetCellItem(CellDefinitions cellItem) 
                { 
                    _chip.SetCellItem(cellItem); 
                }
            };

            /**
             * @brief Структура Decor содержит параметры для оформления игрового поля.
             */
            struct Decor
            {
                sf::FloatRect backgroundSize = {0.f, 0.f, 520.f, 550.f}; ///< Размер фона игрового поля.
                float backgroundRadius = 15.f;                           ///< Радиус закругления углов фона игрового поля.
                float stepBetweenCells = 2.5f;                           ///< Расстояние между ячейками.
                float cellSize = 60.f;                                   ///< Размер ячейки.

                sf::Color blurColor = sf::Color(80, 80, 80, 100);  ///< Цвет размытия.
                sf::Color hoverBlurColor = sf::Color(0, 0, 0, 40); ///< Цвет размытия при наведении курсора.
            } Decor;

            Rectangle _backgroundField; ///< Фон игрового поля.
            Rectangle _blur;            ///< Размытие.
            Rectangle _hoverBlur;       ///< Размытие при наведении курсора.
            BoardSetup::Theme _theme;   ///< Тема игрового поля.

            std::vector<std::vector<Cell>> _cells; ///< Ячейки игрового поля.
            std::function<void()> _function;       ///< Функция.

            mutable bool _isActive = false; ///< Флаг активности.
            mutable bool _isHover = false;  ///< Флаг наведения курсора.

            /**
             * @brief Инициализирует объект класса GameField.
             */
            void init();

            /**
             * @brief Выравнивает элементы игрового поля.
             */
            void Align() {}
        public:

            /**
             * @brief Конструктор класса GameField.
             * 
             * @param theme            Тема игрового поля.
             * @param function         Функция.
             * @param outlineThickness Толщина контура.
             * @param outlineColor     Цвет контура.
             */
            GameField(BoardSetup::Theme theme, std::function<void()> function,
                        float outlineThickness = 4.f, sf::Color outlineColor = sf::Color(68, 164, 208));

            ~GameField() {}

            /**
             * @brief Возвращает все ячейки игрового поля.
             * 
             * @return Ссылка на все ячейки игрового поля.
             */
            const std::vector<std::vector<Cell>>& GetCells() const 
            { 
                return _cells; 
            }

            /**
             * @brief Отрисовывает игровое поле на указанном окне рендеринга.
             * 
             * @param target Указатель на окно рендеринга.
             */
            void Draw(sf::RenderTarget* target);

            /**
             * @brief Устанавливает смещение для игрового поля.
             * 
             * @param OXOffset Смещение по оси X.
             * @param OYOffset Смещение по оси Y.
             */
            void SetOffset(float OXOffset, float OYOffset);

            /**
             * @brief Возвращает глобальные границы игрового поля.
             * 
             * @return Глобальные границы игрового поля.
             */
            sf::FloatRect GetGlobalBounds() const 
            { 
                return _backgroundField.getBounds(); 
            }

            /**
             * @brief Возвращает позицию игрового поля.
             * 
             * @return Позиция игрового поля.
             */
            sf::Vector2f GetPosition() const 
            { 
                return _backgroundField.GetPosition(); 
            }

            /**
             * @brief Устанавливает позицию игрового поля.
             * 
             * @param x Координата X позиции.
             * @param y Координата Y позиции.
             */
            void SetPosition(float x, float y)
            {
                SetOffset(x - _backgroundField.GetPosition().x, y - _backgroundField.GetPosition().y);
            }

            /**
             * @brief Устанавливает тему игрового поля.
             * 
             * @param theme Тема игрового поля.
             */
            void SetTheme(BoardSetup::Theme theme)
            {
                _backgroundField.SetTopColor(BoardSetup::GetColors().at(theme).x);
                _backgroundField.SetBottomColor(BoardSetup::GetColors().at(theme).x);
                for (int i = 0; i < 8; i++)
                    for (int j = 0; j < 8; j++)
                        _cells[i][j].SetBackgroundColor((i + j) % 2 == 0 ? BoardSetup::GetColors().at(theme).y : BoardSetup::GetColors().at(theme).z);
            }

            /**
             * @brief Возвращает флаг активности игрового поля.
             * 
             * @return Ссылка на флаг активности игрового поля.
             */
            bool& GetActive() const 
            { 
                return _isActive; 
            }

            /**
             * @brief Возвращает флаг наведения курсора на игровое поле.
             * 
             * @return Ссылка на флаг наведения курсора на игровое поле.
             */
            bool& GetHover() const 
            { 
                return _isHover; 
            }

            /**
             * @brief Обновляет состояние игрового поля в соответствии с положением курсора и событием мыши.
             * 
             * @param mousePos Позиция курсора.
             * @param event    Событие мыши.
             */
            void Update(const sf::Vector2f& mousePos, const sf::Event& event);
        };
    private:

        /**
         * @brief Структура, содержащая параметры оформления игрового поля.
         * 
         * @param backButtonMargin Отступ кнопки "назад".
         * @param buttonSize       Размер кнопки.
         * @param buttonRadius     Радиус скругления углов кнопки.
         * @param margin           Отступ между элементами интерфейса.
         * @param step             Шаг между элементами интерфейса.
         */
        struct Decor
        {
            float backButtonMargin = 30.f;
            sf::FloatRect buttonSize = sf::FloatRect({0.f, 0.f, 90.f, 90.f});
            float buttonRadius = 15.f;

            float margin = 100.f;
            float step = 80.f;
        } Decor;

        /**
         * @brief Класс кнопки с иконкой.
         */
        ButtonWithIcon _back;

        /**
         * @brief Класс обычного игрового поля.
         */
        GameField _solidGameField;

        /**
         * @brief Класс цветного игрового поля.
         */
        GameField _colorfulGameField;

        /**
         * @brief Класс для ввода никнейма игрока.
         */
        PlayerNickname _playerNickname;

        /**
         * @brief Класс для отображения подсказок.
         */
        ShowTips _showTips;

        /**
         * @brief Метод для инициализации объектов и загрузки настроек.
         */
        void init();

        /**
         * @brief Метод для выравнивания элементов интерфейса.
         */
        void Align();

        /**
         * @brief Метод для сохранения настроек в файл.
         */
        void SaveConfigurations() const;
    public:

        /**
         * @brief Конструктор класса Options.
         * 
         * @param gameStack Указатель на игровой стек.
         */
        Options(game::GameStack* gameStack);

        /**
         * @brief Деструктор класса Options.
         */
        ~Options() {};

        /**
         * @brief Метод для отрисовки элементов интерфейса.
         * 
         * @param target Указатель на целевой объект отрисовки.
         */
        void Draw(sf::RenderTarget* target) override;

        /**
         * @brief Метод для обновления состояния объектов.
         * 
         * @param dt Время, прошедшее с предыдущего кадра.
         */
        void Update(float dt) override 
        {
            _playerNickname.Update(dt); 
        }

        /**
         * @brief Метод для обработки событий мыши.
         * 
         * @param event         Событие мыши.
         * @param mousePosition Позиция курсора мыши.
         * 
         * @return true, если событие было обработано, иначе false.
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePosition) override;
    };
}

#endif