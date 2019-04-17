#ifndef THEME_WINDOW_H
#define THEME_WINDOW_H

#include <QMouseEvent>
#include <QDialog>
#include <QList>
#include <QAbstractButton>

namespace Ui {
class theme_window;
}

/*!
 * \brief Klasa odpowiedzialna za okno wyboru motywu gry
 * \details Klasa ta dziedziczy po QDialog, tworząc okno dialogowe umożliwiające zmianę motywu gry. Gra umożliwia graczowi wybór jednego z czterech motywów:
 * \details - motyw domyślny,
 * \details - "draft",
 * \details - "flat",
 * \details - "Win 95"
 */

class theme_window : public QDialog {

    Q_OBJECT
signals:

    /*!
     * \brief Aktualizacja motywu
     * \details Sygnał ten wywoływany jest podczas zmiany motywu. Przekazuje on <B>id wybranego motywu</B>.
     */
    void updateTheme(int);

public:

    /*!
     * \brief Konstruktor
     * \param parent Wskaźnik na rodzica
     * \details Konstruktor domyślny.
     */
    theme_window( QWidget *parent = 0);

    ~theme_window();

public slots:

    /*!
     * \brief Otwarcie okna wyboru motywu
     * \details Wywołanie tego slotu powoduje otwarcie okna wyboru motywu oraz wysunięcie go na wierzch.
     * \details Slot ten jest publiczny, ponieważ połączony jest z przyciskiem znajdującym się w oknie opcji.
     */
    void showTheme();

private:


    /*!
     * \brief Przechowuje ostatnie współrzędne myszy
     * \details Używane podczas zmiany położenia okna poprzez kliknięcie w dowolnym miejscu w oknie.
     */
    QPoint mLastMousePosition;

    Ui::theme_window *ui;

private slots:

    /*!
     * \brief Slot wywołany po naciśnięciu przycisku Ok
     * \details Slot ten wysyła sygnał updateTheme(int), przekazując id wybranego motywu oraz zamyka okno wyboru motywu.
     */
    void pressOkTheme();

    /*!
     * \brief Slot wywołany po wciśnięciu przycisku Cancel
     * \details Slot ten powoduje zamknięcie okna wyboru motywu, nie zapisując zmian w wybranym motywie.
     */
    void pressCancelTheme();

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

#endif // THEME_WINDOW_H
