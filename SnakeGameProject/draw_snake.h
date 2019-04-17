#ifndef DRAW_SNAKE_H
#define DRAW_SNAKE_H

#include "snake_algorithm.h"
#include "theme_window.h"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QBrush>
#include <QColor>
#include <QTimer>
#include <QPixmap>
#include <QRectF>

#include "options.h"

/*!
 * \brief Klasa służąca do wyświetlania planszy.
 *\details Zawiera ona metody wyświetlające planszę gry oraz pętlę w której wykonywana jest gra. Klasa ta dziedziczy po QWidget.
 */

class draw_snake : public QWidget {

    Q_OBJECT

public:

    /*!
      *\fn draw_snake(QWidget *parent = 0)
     * \brief Konstruktor
     * \param parent wskaźnik na rodzica
     * \details Konstruktor domyślny.
     */
    draw_snake(QWidget *parent = 0);

    /*!
     *\fn draw_snake(int width, int height, Options *options_w, int theme_id, QWidget *parent = 0)
     * \brief Konstruktor
     * \param width wysokość planszy podana w pikselach
     * \param height szerokość planszy podana w pikselach
     * \param options_w wskaźnik na okno dialogowe wyboru opcji
     * \param theme_id id wybranego motywu
     * \param parent wskaźnik na rodzica
     * \details Parametry <B>width</B> oraz <B>height</B> określają rozmiar planszy.
     * \details Parametr <B>options_w</B> wykorzystywany jest aby pobrać bierzące ustawienia gry.
     * \details Parametr <B>theme_id</B> przekazuje id obecnie używanego motywu gry.
     * \details W konstruktorze obliczana jest wartość <B>pixToHorizontalCentre</B> oraz <B>pixToVerticalCentre</B>, dodatkowo
     * wykonywane są obliczenia by wybrać możliwie jak największy rozmiar <B>CellSize</B> tak, aby plansza nie wykraczała poza okno.
     */
    draw_snake(int width, int height, Options *options_w, int theme_id, QWidget *parent = 0);


    /*!
     * \brief Obiekt typu snake_algorithm
     *\details Obiekt ten zawiera algorytm gry Snake, odpowiadający m.in. poruszanie się węża.
     */
    snake_algorithm *snake;

    /*!
     * \brief Określa czy gra się rozpoczęła
     *\details Przechowuje <B>true</B> jeśli gra trwa, <B>false</B> kiedy gracz zatrzyma grę.
     */
    bool isGameStarted = false;

    /*!
     * \brief Ustawienie prędkości gry
     * \details Ustawienie predkości poruszania się wężą w <B>ms</B> na jedno przemieszczenie.
     * \details Ustawienie wartości <B>speed</B> jako czas trwania jednego taktu w <B>timer</B>.
     * \param speed wartość w ms
     */
    void setSpeed(int speed);

    ~draw_snake();

public slots:

    /*!
     * \brief Slot wywoływany przez timer
     * \details Slot ten wywoływany jest przez <B>timer </B> i stanowi on pętlę w której wykonuje sie gra.
     * \details Jeśli gra się nie zakończyła, wywołuje on metodę <B>move()</B>, a następnie <B>update()</B>.
     * \details W przeciwnym razie zatrzymuje <B>timer</B> oraz ustawia wartość <B>isGameStarted</B> na <B>false</B>.
     */
    void gameLoop();

    /*!
     * \brief Wywołanie tego slotu rozpoczyna grę.
     * \details Slot ten Ustawienie wartości <B>speed</B> jako czas trwania jednego taktu w <B>timer</B> oraz ustawia wartość <B>isGameStarted</B> na <B>true</B>.
     */
    void startGame();

    /*!
     * \brief Wywołanie tego slotu zatrzymuje grę.
     * \details Slot ten zatrzymuje <B>timer</B> oraz ustawia wartość <B>isGameStarted</B> na <B>false</B>.
     */
    void pauseGame();

private:

    /*!
     * \brief Rozmiar pojedynczego elementu na planszy w pikselach.
     */
    int CellSize;

    /*!
     * \brief Czas pomiędzy przemieszczeniami się węża podany w <B>ms</B>
     */
    int speed;

    /*!
     * \brief Ilość pikseli potrzebnych do wyrównania planszy w poziomie.
     */
    int pixToHorizontalCentre;

    /*!
     * \brief Ilość pikseli potrzebnych do wyrównania planszy w pionie.
     */
    int pixToVerticalCentre;

    /*!
     * \brief Przechowuje id aktualnie wybranego motywu.
     */
    int theme_id;

    /*!
     * \brief timer gry.
     * \details Po upływie określonego czasu (podanego w <B>ms</B>) wywołuje on slot gameLoop().
     */
    QTimer *timer;

    /*!
     * \brief Przechowuje on teksturę węża.
     */
    QPixmap *Snake;

    /*!
     * \brief Przechowuje on teksturę pustego pola na planszy.
     */
    QPixmap *Null;

    /*!
     * \brief Przechowuje on teksturę owocu nr 1.
     */
    QPixmap *Fruit_1;

    /*!
     * \brief Przechowuje on teksturę owocu nr 2.
     */
    QPixmap *Fruit_2;

    /*!
     * \brief Przechowuje on teksturę owocu nr 3.
     */
    QPixmap *Fruit_3;

    /*!
     * \brief Przechowuje on teksturę przeszkody.
     */
    QPixmap *Eggs;

    /*!
     * \brief Obiekt na którym rysowana jest plansza
     * \details Służy on do wyświetlania zawartości planszy. Tworzony jest on w metodzie paintEvent(QPaintEvent *), która wywoływana jest przy użyciu
     * \details update(). Zależnie od wybranego motywu, pobiera on odpowiednie tekstury z pliku, a następnie rysuje on planszę na podstawie tablicy
     * \details dwuwymiarowej <B>board</B> znajdującej się w obiekcie klasy snake_algorithm.
     */
    QPainter *painter;

    /*!
     * \brief Wypełnienie używane do narysowania granic planszy
     */
    QBrush *Wall_Brush;

protected:

    /*!
     * \brief Metoda odpowiedzialna za rysowanie planszy.
     * \details Metoda ta jest <B>eventem</B>, wywoływanym za każdym razem, kiedy zostanie użyta metoda <B>update()</B>.
     */
    void paintEvent(QPaintEvent *);
};

#endif // DRAW_SNAKE_H
