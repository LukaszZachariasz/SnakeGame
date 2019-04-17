#ifndef SNAKE_ALGORITHM_H
#define SNAKE_ALGORITHM_H

#include <QVector>
#include <QObject>
#include <ctime>

#include "snake_coord.h"
#include "array.h"
#include "content.h"

/*!
 * \brief Klasa algorytmu gry Snake
 * \details Klasa ta odpowiedzialna jest za algorytm gry. Zawiera ona dane dotyczące:
 * - aktualnego położenia węża, owoców, przeszkód, \n
 * - kierunku poruszania się węża, \n
 * - rozmiaru planszy,\n
 * - wartości poszczególnych owoców,\n
 * - ilości przeszkód zostawianych przez węża (o ile ma je zostawiać),\n
 * - możliwości przechodzenia przez ściany.
 * \details Klasa ta odpowiada również za poruszanie się węża. Zawiera ona tablicę <B>board</B>, która zawiera wszystkie elementy wyświetlane na planszy.
 */
class snake_algorithm : public QObject {

    Q_OBJECT

signals:

    /*!
     * \brief Sygnał wysyłany by zaktualizować wynik
     * \details Sygnał ten wysyłany jest w momencie zjedzenia owocu przez wężą i przekazuje on aktualny wynik.
     */
    void updateScore(int);

public:

    /*!
     * \brief Konstruktor
     * \param X ilość kolumn
     * \param Y ilość wierszy
     * \param collision_Walls określa czy wąż nie może przechodzić przez ściany
     * \param snake_Eggs określa czy wąż ma zostawiać przeszkody
     * \param Fruit_1_Value wartość owocu nr 1
     * \param Fruit_2_Value wartość owocu nr 2
     * \param Fruit_3_Value wartość owocu nr 3
     * \param eaten_Fruits_To_Grow ilość owoców po których wąż zostawi przeszkodę
     */
    snake_algorithm(int X,
                    int Y,
                    bool collision_Walls = true,
                    bool snake_Eggs = true,
                    int Fruit_1_Value = 10,
                    int Fruit_2_Value = 30,
                    int Fruit_3_Value = 50,
                    int eaten_Fruits_To_Grow = 4);

    /*!
     * \brief Zwraca aktualną ilość kolumn
     * \return Zwraca aktualną ilość kolumn, z których składa się plansza.
     */
    int getX();

    /*!
     * \brief Zwraca aktualną ilość wierszy
     * \return Zwraca aktualną ilość wierszy, z których składa się plansza.
     */
    int getY();

    /*!
     * \brief Zwraca informację o aktualnym stanie gry
     * \return Zwraca <B>true</B> jeśli gracz przegrał, <B>false</B> jeśli gra trwa dalej.
     */
    bool isGameOver();

    /*!
     * \brief Aktualizacja tablicy <B>board</B>
     * \details Metoda ta dodaje do tablicy <B>board</B> elementy węża oraz przeszkody, których współrzędne przetrzymują odpowiednio
     * <B>snake_coords</B> oraz <B>egg_coords</B>. Metoda ta pierw dodaje współrzędne przeszkody, potem dopiero współrzędne węża, tak aby
     * móc je nadpisać, dzięki czemu podczas wyświetlania nie wystąpi sytuacja, w której jakiś element węża będzie przeszkodą.
     */
    void updateBoard();

    /*!
     * \brief Metoda odpowiedzialna za poruszanie się węża.
     * \details Wywołanie tej metody powoduje przemieszczenie się węża o jeden kwadrat. Metoda ta sprawdza w jakim kierunku ma przemieścić się wąż,
     * następnie dokonuje odpowiedniej zmiany współrzędnych pierwszego elementu ciała węża (głowy), po czym dodaje te współrzędne na początek
     * tablicy <B>snake_coords</B> oraz usuwa ostatni element tej tablicy (wykonuje operacje <B>push</B> oraz <B>pop</B>). Jeśli ustawiono tryb gry w
     * którym wąż może przechodzić przez ściany, to w momencie w którym miałoby to nastąpić współrzędne głowy zostaną tak zamienione, aby wąż znalazł się
     * po przeciwnej stronie planszy.
     * \details Metoda ta porównuje również współrzędne głowy węża z elementem tablicy <B>board</B> o tych samych współrzędnych i
     * zależnie od tego co znajduje się w tym elemencie:
     * - jeśli jest to owoc - zwiększy wynik o wartość owocu, wyśle sygnał updateScore(int), nie usunie ostatniego elementu tablicy <B>snake_coords</B>
     * (dzięki czemu wąż będzie większy o jeden element) oraz wywoła metodę updateBoard() (która doda współrzędne węża oraz
     * przeszkód do <B>board</B>, tym samym nadpisując współrzędne owocu głową węża)
     * - jeśli jest to ściana - wartość <B>gameOver</B> zostanie ustawiona na <B>true</B>. Jeśli ustawiono możliwość przechodzenia przez ściany, to
     * współrzędne głowy nigdy nie znajdą się na ścianie.
     * - jeśli to przeszkoda bądź ciało węża - wartość <B>gameOver</B> zostanie ustawiona na <B>true</B>.
     */
    void move();

    /*!
     * \brief Tablica przechowująca zawartość planszy gry
     * \details Tablica ta w rzeczywistości jest wektorem wektorów typu wyliczeniowego <B>content</B>, który zawiera wszystkie elementy mogące znaleźć
     * się na planszy gry. Dostęp do tablicy wygląda następująco: board[<B>indeks_wiersza</B>][<B>indeks_kolumny</B>].
     */
    QVector< QVector<content> > board;

    /*!
     * \brief Zmienna określająca kierunek poruszania się węża
     * \details Zmienna typu <B>array</B>, określa w którym kierunku porusza się wąż.
     */
    array snake_array = array::l;

    ~snake_algorithm();

private:

    /*!
     * \brief Ilość wierszy z których składa się tablica <B>board</B>
     */
    int X;

    /*!
     * \brief Ilość kolumn z których składa się tablica <B>board</B>
     */
    int Y;

    /*!
     * \brief Wartość owocu nr 1
     */
    int Fruit_1_Value;

    /*!
     * \brief Wartość owocu nr 2
     */
    int Fruit_2_Value;

    /*!
     * \brief Wartość owocu nr 3
     */
    int Fruit_3_Value;

    /*!
     * \brief Aktualny wynik
     */
    int score = 0;

    /*!
     * \brief Ilość zjedzonych owoców
     * \details Zmienna ta służy jako licznik określający ile pozostało owoców do zostawienia przez węża przeszkody.
     * Po osiągnięciu wartości równej <B>eate eaten_Fruits_To_Grow</B>, wartość licznika zostaje wyzerowana.
     */
    int eaten_Fruits = 0;

    /*!
     * \brief Określa ile owoców musi zjeść wąż, aby zostawić przeszkodę.
     */
    int eaten_Fruits_To_Grow;

    /*!
     * \brief Określa czy na planszy znajduje się owoc nr 1 (<B>true</B> jeśli znajduje się)
     */
    bool is_Fruit_1 = false;

    /*!
     * \brief Określa czy na planszy znajduje się owoc nr 2 (<B>true</B> jeśli znajduje się)
     */
    bool is_Fruit_2 = false;

    /*!
     * \brief Określa czy na planszy znajduje się owoc nr 3 (<B>true</B> jeśli znajduje się)
     */
    bool is_Fruit_3 = false;

    /*!
     * \brief Określa czy gracz przegrał (<B>true</B> jeśli gracz przegrał)
     */
    bool gameOver = false;

    /*!
     * \brief Określa czy wąż ma zostawiać przeszkody (<B>true</B> jeśli ma zostawiać przeszkody)
     */
    bool snake_Eggs;

    /*!
     * \brief Określa czy wąż może przechodzić przez ściany (<B>false</B> jeśli może przechodzić
     */
    bool collision_Walls;

    /*!
     * \brief Tablica zawierająca współrzędne węża
     * \details Tablica ta jest wektorem obiektów klasy snake_coord, która przechowuje współrzędne elementów ciała węża w postaci
     * indeksów tablicy <B>board</B>.
     */
    QVector< snake_coord > snake_coords;

    /*!
     * \brief Tablica zawierająca współrzędne przeszkód
     * \details Tablica ta jest wektorem obiektów klasy snake_coord, która przechowuje współrzędne przeszkód w postaci indeksów tablicy <B>board</B>.
     */
    QVector< snake_coord > egg_coords;

    /*!
     * \brief Obiekt przechowujący współrzędne głowy węża
     * \details Obiekt klasy snake_coord, służy do przechowywania współrzędnych głowy wężą w postaci indeksów tablicy <B>board</B>.
     * Obiekt ten używany jest w metodzie move().
     */
    snake_coord *head_coord;

    /*!
     * \brief Metoda generująca współrzędne owoców
     * \details Metoda ta wywoływana jest w metodzie move() w momencie w którym wąż zjada owoc. Metoda ta zawsze generuje owoc nr 1, oraz
     * losowo owoce nr 2 i 3. Metoda ta podczas generowania sprawdza czy współrzędne owocu są odpowiednie (tzn. kiedy odpowiadają one pustemu
     * polu na tablicy <B>board</B>).
     */
    void genFruit();

    /*!
     * \brief Metoda generująca przeszkody
     * \details Metoda to wywoływana jest w metodzie move() w momencie kiedy wartość licznika <B>eaten_Fruits</B> osiągneła wymagany poziom.
     * Współrzędne przeszkody równają się pierwszemu elementowi tablicy <B>snake_coords przed dodaniem elementu do tej tablicy</B> (czyli przed
     * "przemieszczeniem się węża"), czyli po zakończu metody move() współrzędne odpowiadają drugiemu elementowi, co nie powoduję przegrania gry.
     */
    void genEgg();

};

#endif // SNAKE_ALGORITHM_H
