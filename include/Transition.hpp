#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

namespace game {

    /**
     * @brief Перечисление режимов шейдера для перехода.
     */
    enum class ShaderMode {
        Appear = 0,   ///< Режим появления
        Disappear = 1 ///< Режим исчезновения
    };

    /**
     * @brief Класс управления переходом между сценами с использованием шейдеров.
     */
    class Transition : public sf::NonCopyable {
    public:
        /**
         * @brief Конструктор класса Transition.
         */
        Transition();

        /**
         * @brief Деструктор класса Transition.
         */
        ~Transition() { delete _shader; }

        /**
         * @brief Получение указателя на единственный экземпляр класса Transition.
		 * 
         * @return Указатель на экземпляр Transition.
         */
        static Transition* Get();

        /**
         * @brief Получение текущего прогресса перехода.
		 * 
         * @return Значение прогресса от 0.0 до 1.0.
         */
        float GetProgress() const { return _progress; }

        /**
         * @brief Получение текущего режима перехода.
		 * 
         * @return Режим перехода (Appear/Disappear).
         */
        ShaderMode GetMode() const { return _mode; }

        /**
         * @brief Обновление состояния перехода.
		 * 
         * @param dt Время с момента предыдущего обновления.
         */
        void Update(const float& dt);

        /**
         * @brief Установка режима перехода.
		 * 
         * @param mode Новый режим (Appear/Disappear).
         */
        void SetMode(ShaderMode mode);

        /**
         * @brief Установка пользовательской функции для перехода.
		 * 
         * @param function Функция, которая будет вызвана при переходе.
         */
        void SetFunction(std::function<void()> function);

        /**
         * @brief Получение ссылки на объект шейдера.
		 * 
         * @return Ссылка на объект шейдера.
         */
        sf::Shader& GetShader();
    private:
        static Transition* _sInstance; // Статический экземпляр класса Transition
        sf::Shader* _shader;           // Указатель на объект шейдера
        float _updateTime   = 0.01f;   // Время обновления
        float _elapsedTime  = 0.0f;    // Прошедшее время
        float _progress  = 1.0f;       // Прогресс перехода

        ShaderMode _mode = ShaderMode::Disappear; // Текущий режим перехода
        std::function<void()> _function = 0;      // Пользовательская функция для перехода

        /**
         * @brief Обновление состояния перехода на следующий шаг.
		 * 
         * @param step Шаг обновления.
         */
        void UpdateTransition(int step);
    };
}

#endif