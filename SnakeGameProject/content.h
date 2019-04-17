#ifndef CONTENT_H
#define CONTENT_H

/*!
 * \brief Typ wyliczeniowy określający zawartość tablicy <B>board</B> w klasie snake_algorithm
 */
enum content {
    Null, /**< Puste pole */
    Fruit_1, /**< Owoc nr 1 */
    Fruit_2, /**< Owoc nr 2 */
    Fruit_3, /**< Owoc nr 3 */
    Egg, /**< Przeszkoda */
    Wall, /**< Ściana */
    Snake /**< Wąż */
};

#endif // CONTENT_H
