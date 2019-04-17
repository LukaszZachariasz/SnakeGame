#ifndef OPTIONS_H
#define OPTIONS_H

#include <QMouseEvent>
#include <QDialog>
#include <QList>
#include <QAbstractButton>
#include "theme_window.h"   //
#include <QMainWindow>      //
#include <QMouseEvent>      //

#include "theme_window.h"


namespace Ui {
class Options;
}

///klasa odpowiedzialna za okno dialogowe opcji
/*!
 * \brief Klasa okna dialogowego opcji
 * \details Klasa ta dziedziczy po QDialog. Służy ona do wyświetlenia okna dialogowego umożliwiającego zmianę ustawień gry.
 * \details Okno opcji zawiera umożliwia:
 * \details - zmianę rozmiaru planszy - zawiera 3 domyślne rozmiary oraz opcję ustawienia niestandardowego rozmiaru,
 * \details - zmianę ilość owoców po zjedzeniu których wąż zostawia przeszkodę wraz z możliwością wyłączenia tej opcji,
 * \details - ustawienie wartości owoców,
 * \details - zmianę szybkości gry
 */

class Options : public QDialog {

    Q_OBJECT
signals:

    /*!
     * \brief Sygnał wysyłany w momencie zatwierdzenia zmian w opcjach
     * \details Sygnał ten wysyłany jest w momencie zatwierdzenia zmian wprowadzonych w oknie opcji.
     * \details Powoduje on zrestartowanie gry z wprowadzonymi nowymi ustawieniami.
     */
    void updateOptions();

public:

    /*!
     * \brief Konstruktor
     * \param parent Wskaźnik na rodzica.
     * \details Konstruktor domyślny.
     */
    Options(QWidget *parent = 0);

    /*!
     * \brief Konstruktor
     * \param theme Wskaźnik na okno klasy theme_window.
     * \param parent Wskaźnik na rodzica.
     * \details Jako parametr przekazywany jest wskaźnik na okno klasy theme_window, aby umożliwić wyświetlenie go po wciśnięciu odpowiedniego przycisku.
     */
    Options(theme_window *theme, QWidget *parent = 0);


    /*!
     * \brief Zwraca ilość wierszy.
     * \return Zwraca ilość wierszy z których składać się będzie plansza.
     */
    int getRows();

    /*!
     * \brief Zwraca ilość kolumn.
     * \return Zwraca ilość kolumn z których składać się będzie plansza.
     */
    int getColumns();

    /*!
     * \brief Zwraca ilość owoców po zjedzeniu których wąż zostawi przeszkodę
     * \return Zwraca ilość owoców po zjedzeniu których wąż zostawi przeszkodę.
     */
    int getFruitsToGrow();

    /*!
     * \brief Wartość owocu nr 1
     * \return Zwraca wartość owocu nr 1.
     */
    int getFruit1Value();

    /*!
     * \brief Wartość owocu nr 2
     * \return Zwraca wartość owocu nr 2.
     */
    int getFruit2Value();

    /*!
     * \brief Wartość owocu nr 3
     * \return Zwraca wartość owocu nr 3.
     */
    int getFruit3Value();


    /*!
     * \brief Informacja czy można przejść przez ściany.
     * \return Zwraca wartość <B>true</B> jeśli nie można przejsc przez ściany, natomiast <B>false</B> jeśli nie występują kolizje ze scianami.
     */
    bool isCollision();

    /*!
     * \brief Ustawienie czy wąż ma zostawiać przeszkody
     * \return Zwraca <B>true</B> jeśli wąż ma zostawiać przeszkody, <B>false</B> jeśli ma nie zostawiać przeszkód.
     */
    bool isEgg();

    /*!
     * \brief Zwraca szybkość węża.
     * \return Zwraca czas w <B>ms</B> po jakim wąż wykona jedno przemieszczenie.
     */
    int getSpeedValue();

    ~Options();

public slots:

    /*!
     * \brief Otwarcie okna opcji.
     * \details Wywołanie tego slotu powoduje otwarcie okna opcji oraz wysunięcie go na wierzch.
     * \details Slot ten jest publiczny, ponieważ połączony jest z przyciskiem znajdującym się w głównym oknie gry.
     */
    void showOptions();

private:

    /*!
     * \brief Przechowuje ostatnie współrzędne myszy
     * \details Używane podczas zmiany położenia okna poprzez kliknięcie w dowolnym miejscu w oknie.
     */
    QPoint mLastMousePosition;

    /*!
     * \brief Domyślna ilość kolumn.
     */
    int columns = 35;

    /*!
     * \brief Domyślna ilość wierszy.
     */
    int rows = 20;

    Ui::Options *ui;

private slots:

    /*!
     * \brief Włączenie ustawień niestandardowych
     * \param b określa czy mają być włączone ustawienia niestandardowe
     * \details Umożliwia włączenie niestandardowych ustawień rozmiaru planszy. Dla parametru <B>b</B> równego <B>true</B> opcje zostaną włączone,
     * \details dla <B>false</B> - wyłączone.
     */
    void setEnabledNonStandardOptions(bool b);

    /*!
     * \brief Włączenie przeszkód
     * \param b określa czy wąż ma zostawiać przeszkody
     * \details Umożliwia włączenie przeszkód zostawianych przez węża po zjedzeniu odpowiedniej ilości owoców.
     * \details Dla parametru <B>b</B> równego <B>true</B> opcje zostaną włączone, dla <B>false</B> - wyłączone.
     */
    void setEnabledEggOptions(bool b);


    /*!
     * \brief Slot wywołany po wciśnięciu przycisku Ok
     * \details Slot ten powoduje wysyła sygnał updateOptions() oraz zamyka okno opcji.
     */
    void pushOkOptions();

    /*!
     * \brief Slot wywołany po wciśnięciu przycisku Cancel
     * \details Slot ten powoduje zamknięcie okna opcji, bez zapisywania ustawień.
     */
    void pushCancelOptions();

    /*!
     * \brief Slot zmienia rozmiar planszy na mały
     */
    void updateValSmall();

    /*!
     * \brief Slot zmienia rozmiar planszy na średni
     */
    void updateValNormal();

    /*!
     * \brief Slot zmienia rozmiar planszy na duży
     */
    void updateValBig();

protected:

    /*!
     * \brief Event wywoływany za każdym razem, kiedy kursor myszy się przemieści.
     * \param event Parametr przekazuje dane QMouseEvent
     * \details Event ten zostaje wywołany w momencie przemieszczenia się kursoru myszy.
     * \details Z parametru <B>event</B> odczytane zostają dane dotyczące położenia kursoru.
     * \details Event ten wykorzystywany jest do przemieszczenia okna, odczytując aktualne położenie oraz położenie z <B>mLastMousePosition</B>, jeśli przycisk myszy jest wciśniety.
     */
    void mouseMoveEvent(QMouseEvent* event);

    /*!
     * \brief Event ten wywoływany jest za każdym razem, kiedy wykryje naciśnięcie przycisku myszy.
     * \param event Parametr przekazuje dane QMouseEvent
     * \details Event ten zostaje wywołany po naciśnięciu przycisku myszy.
     * \details Kiedy przycisk myszy jest wciśniety, zapisuje on do <B>mLastMousePosition</B> ostatnią pozycję kursora.
     */
    void mousePressEvent(QMouseEvent* event);

};

#endif // OPTIONS_H
