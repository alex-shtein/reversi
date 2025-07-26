#ifndef RESULTS_SETUP_HPP
#define RESULTS_SETUP_HPP

#include <exception>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "./GameSetup.hpp"

namespace game
{
    /**
     * @brief Класс представляет результаты конфигурации.
     */
    class ResultsSetup
    {
    private:
        unsigned _wins;                         ///< Количество побед
        unsigned _loses;                        ///< Количество поражений
        unsigned _draws;                        ///< Количество ничьих
        static ResultsSetup*  _resultsSetupPtr; ///< Указатель на текущий объект конфигурации результатов

    public:

        /**
         * @brief Конструктор класса ResultsSetup.
         * 
         * Если _resultsSetupPtr уже имеет значение, то выбрасывается исключение типа std::logic_error. 
         * В противном случае, указатель _resultsSetupPtr присваивается значению указателя this, а затем вызывается метод Load().
         */
        ResultsSetup();

        /// Деструктор
        ~ResultsSetup() = default;

        /**
         * @brief  Получить общее количество результатов (побед, поражений, ничьих).
         * @return Общее количество результатов.
         */
        static unsigned GetTotal() { return GetWins() + GetLoses() + GetDraws(); }

        /**
         * @brief  Получить количество побед.
         * @return Ссылка на количество побед.
         */
        static unsigned& GetWins() { return _resultsSetupPtr->_wins; }

        /**
         * @brief  Получить количество поражений.
         * @return Ссылка на количество поражений.
         */
        static unsigned& GetLoses() { return _resultsSetupPtr->_loses; }

        /**
         * @brief  Получить количество ничьих.
         * @return Ссылка на количество ничьих.
         */
        static unsigned& GetDraws() { return _resultsSetupPtr->_draws; }

        /**
         * @brief Сохранение результатов в файл.
         *        Открывается файл "../Files/ResultsSetup.txt" для записи. 
         *        Если не удается открыть файл, выбрасывается исключение типа std::runtime_error. 
         *        Затем в файл записываются победы, поражения и ничьи из объекта _resultsSetupPtr.
         */
        static void Save();

        /**
         * @brief Загрузка результатов из файла.
         *        Создается директория "../Files/", затем происходит открытие файла "../Files/ResultsSetup.txt" для чтения значений в переменных класса. 
         *        Если файл не удалось открыть, создается новый файл и в нем записываются нулевые значения для побед, поражений и ничьих. 
         *        В противном случае из файла считываются победы, поражения и ничьи в объект класса ResultsSetup.
         */
        static void Load();
    };
}
    
#endif