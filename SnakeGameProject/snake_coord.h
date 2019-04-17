#ifndef SNAKE_COORD_H
#define SNAKE_COORD_H

/*!
 * \brief Klasa zawierająca współrzędne w formie indeksów tablicy
 * \details Klasa ta umożliwia zapisanie współrzędnych w formie indeksów tablicy, a następnie stworzenie z obiektów tej klasy np. tablicy przechowującej grupę elementów o podanych współrzędnych.
 */
class snake_coord {

private:

    /*!
     * \brief Przechowuje indeks kolumny
     */
    int X;

    /*!
     * \brief Przechowuje indeks wiersza
     */
    int Y;

public:

    /*!
     * \brief Konstruktor
     * \details Konstruktor domyślny
     */
    snake_coord();

    /*!
     * \brief Konstruktor
     * \param X indeks kolumny
     * \param Y indeks wiersza
     * \details Przypisuje indeksy podane w parametrach do pól <B>X</B> i <B>Y</B>.
     */
    snake_coord(int X, int Y);

    /*!
     * \brief Zwraca indeks kolumny
     * \return Zwraca indeks kolumny w postaci zmiennej typu <B>int</B>.
     */
    int getX();

    /*!
     * \brief Zwraca indeks wiersza
     * \return Zwraca indeks wiersza w postaci zmiennej typu <B>int</B>.
     */
    int getY();

    /*!
     * \brief Przypisanie indeksów podanych w parametrach
     * \param X indeks kolumny
     * \param Y indeks wiersza
     * \details Przypisuje indeksy podane w parametrach do pól <B>X</B> i <B>Y</B>.
     */
    void setCoord(int X, int Y);
};

#endif // SNAKE_COORD_H
