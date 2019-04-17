#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFont>
#include <QFile>
#include <QByteArray>
#include <QDataStream>

#include "snake_algorithm.h"
#include "draw_snake.h"


namespace Ui {

    class MainWindow;

}

/*!
 * \brief Klasa głównego okna gry
 * \details Klasa ta odpowiedzialna jest za główne okno gry. Zawiera ona trzy zakładki, zmieniane zależnie od aktualnego stanu gry:
 * \details - w pierwszej zakładce znajduje się plansza gry oraz informacje o aktualnym czasie gry oraz wyniku. Jest ona aktywowana w momencie kiedy użytkownik rozpoczyna rozgrywkę,
 * \details - w drugiej zakładce znajduje się okno głównego menu gry, pozwalające rozpocząc nową grę, otworzyć okno opcji oraz zakończyć program. Jest ona aktywna w momencie startu programu oraz aktywowana w momencie zatrzymania rozgrywki,
 * \details - w trzeciej zakładce znajduje się okno wyników bieżącej rozgrywki, wyświetlające się po przegranej. Okno to umożliwia rozpoczęcie nowej rozgrywki, zmianę ustawień oraz zakończenie programu.
 */

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    /*!
     * \brief Konstruktor
     * \param parent Wskaźnik na rodzica
     * \details Konstruktor domyślny. Typ <B>explicit</B> oznacza, że jest to konstruktor jawny. Został on użyty aby zapobiec możliwej konwersji, która mogłaby spowodować błędy.
     */
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:

    /*!
     * \brief Licznik
     * \details Służy on jako licznik czasu gry. Został wykorzystany aby zapewnić większą precyzję podczas odtwarzania dźwięku końca gry.
     */
    double d_time = 0.00;

    /*!
     * \brief Najwyższy wynik
     * \details Wyświetla on wartość najwyższego wyniku w czasie gry.
     * \details Przypisywana jest mu wartość najwyższego wyniku odczytanego z pliku. W przypadku braku pliku, następuje przypisanie wartości <B>0</B>.
     * \details Jeśli aktualny wynik jest wyższy niż zawartość <B>highscore</B>, zostaje on zapisany do <B>highscore</B>.
     */
    int highScore;

    /*!
     * \brief Aktualny czas gry
     * \details Aktualny czas gry w <B>sekundach</B>.
     */
    int time = 0;

    /*!
     * \brief ID aktualnie używanego motywu
     * \details ID aktualnie używanego motywu:
     * \details - 0 - motyw domyślny,
     * \details - 1 - motyw "Flat",
     * \details - 2 - motyw "Draft",
     * \details - 3 - motyw "Win 95",
     * \details Przekazywane jest ono jako parametr dla obiektu klasy draw_snake.
     */
    int theme_id = 0;

    /*!
     * \brief Timer służący do pomiaru aktualnego czasu w grze
     * \details Obiekt klasy <B>QTimer</B> służący do pomiaru aktualnego czasu w grze.
     * \details Jako odstęp pomiędzy kolejnymi wywołaniami slotu timerTick() podana została wartość <B>10 ms</B>, tak aby dokładność z jaką zostanie odtwarzany dźwięk podczas przegranej był jak największa.
     */
    QTimer *timer;

    /*!
     * \brief Przechowuje ostatnie współrzędne myszy
     * \details Używane podczas zmiany położenia okna poprzez kliknięcie w dowolnym miejscu w oknie.
     */
    QPoint mLastMousePosition;

    /*!
     * \brief Widget wyświetlający planszę gry.
     * \details Obiekt klasy draw_snake dziedziczącej po <B>QWidget</B>, odpowiada on za wyświetlanie planszy gry oraz zawiera pętle gry.
     */
    draw_snake *snake_widget;

    /*!
     * \brief Interfejs obsługi pliku
     * \details Obiekt klasy <B>QFile</B> tworzącej interfejs obsługi pliku. Używany jest do <B>zapisu</B> (tworzenia jeśli nie ma) najwyższego wyniku zapisanego w <B>highScore</B> do pliku.
     */
    QFile f_high_score_save_read;

    /*!
     * \brief Interfejs obsługi pliku
     * \details Obiekt klasy <B>QFile</B> tworzącej interfejs obsługi pliku. Używany do odczytu najwyższego wyniku z pliku oraz zapisu go do <B>highScore</B>.
     */
    QFile f_high_score_save_write;

    /*!
     * \brief Obiekt przechowujący listę utworów.
     * \details Obiekt klasy <B>QMediaPlaylist</B>, służacy do utworzenia zapętlonej listy odtwarzanych utworów.
     */
    QMediaPlaylist *game_music_playlist;

    /*!
     * \brief Obiekt służacy do odtwarzania utworu.
     * \details Obiekt klasy <B>QMediaPlayer</B> służacy do odtworzenia dźwięku w czasie przegrania rozgrywki.
     */
    QMediaPlayer *game_over_sound;

    /*!
     * \brief Obiekt służacy do odtwarzania utworu.
     * \details Obiekt klasy <B>QMediaPlayer</B> służacy do odtworzenia dźwięku w czasie zjedzenia przez węża owocu.
     */
    QMediaPlayer *catch_fruit_sound;

    /*!
     * \brief Obiekt służacy do odtwarzania utworu.
     * \details Obiekt klasy <B>QMediaPlayer</B> służacy do odtworzenia dźwięku podczas rozgrywki. Odtwarza on zawartość <B>game_music_playlist</B>.
     */
    QMediaPlayer *game_music_sound;

    /*!
     * \brief Zakładki okna gry
     * \details Przełączane zakładki w głównym oknie gry, zależnie od tego aktualnego stanu gry. Zawiera następujące zakładki:
     * \details - okno gry - w tej zakładce znajduje się plansza gry oraz informacje o aktualnym czasie gry oraz wyniku. Zakładka otwarta w czasie trwania rozgrywki.
     * \details - okno menu gry - zakładka w której znajdują sie przyciski umożliwiające rozpoczęcie gry, zmianę ustawień oraz wyjście z gry. Jest on aktywna jako zakładka startowa oraz podczas wstrzymania rozgrywki.
     * \details - okno wyniku - zakładka wyświetlania po przegranej rozgrywce. Zawiera informację o aktulanym oraz najwyższym wyniku, dodatkowo umożliwia zmiane wrócenie do okna menu, rozpoczęcie nowej rozgrywki oraz zakończenie gry.
     */
    QTabWidget *gameTab();

    /*!
     * \brief Okno dialogowe wyboru motywu
     * \details Obiekt klasy theme_window dziedziczącej po QDialog. Okno to umożliwia zmianę motywu gry.
     */
    theme_window *theme_w;

    /*!
     * \brief Okno dialogowe opcji
     * \details Obiekt klasy Options dziedziczącej po QDialog. Okno to umożliwia zmianę ustawień rozgrywki taki jak:
     * \details - rozmiar planszy,
     * \details - ilosc przeszkód zostawianych przez węża,
     * \details - wartość owoców,
     * \details - prędkość rozgrywki
     */
    Options *options_w;

    /*!
     * \brief Metoda tworząca pole aktualnego wyniku
     * \details Metoda ta formatuje zawartość wyświetlaną przez obiekt klasy <B>QLabel</B> oraz tworzy połączenie sygnału updateScore(int) znajdującego sie w obiekcie klasy snake_algorithm ze slotem updateScore(int s).
     */
    void createScore();

    /*!
     * \brief Metoda tworząca pole aktualnego czasu gry
     * \details Metoda ta formatuje zawartość wyświetlaną przez obiekt klasy <B>QLabel</B> oraz tworzy obiekt klasy <B>QTimer</B>, który wywołuje slot updateTick() co każde <B>10 ms</B>.
     */
    void createTimer();

    /*!
     * \brief Ustawienie aktywnej zakładki
     * \param id ID zakładki która ma zostać ustawiona jako aktywna: \n- 0 - okno gry, \n- 1 - okno menu, \n- 2 - okno wyniku
     * \details Metoda ta zmienia aktywną zakładkę na tą o indeksie podanym przez parametr <B>id</B>.
     */
    void activateTabGame(int id);

    Ui::MainWindow *ui;

private slots:

    /*!
     * \brief Slot wywoływany przez timer
     * \details Slot ten odpowiada za wyświetlanie aktualnego czasu rozgrywki. Dodatkowo sprawdza czy gra dalej się toczy, jeśli tak to ustawia timer nową wartością.
     * \details Jeśli rozgrywka zakończyła się przegraną - zatrzymuje dźwięk odtwarzany podczas gry oraz zmienia go na dźwięk
     * przegranej po czym wywołuje metodę restartGame().
     */
    void timerTick();

    /*!
     * \brief Slot ten odpowiada za wyświetlanie aktualnego wyniku
     * \param s aktualny wynik przekazywany przez <B>updateScore(int)</B>
     * \details Slot wywoływany jest przez sygnał <B>updateScore(int)</B> znajdujący się w klasie snake_algorithm.
     * \details Odpowiada on za wyświetlanie aktualnego wyniku rozgrywki oraz aktualizację najwyższego wyniku jeśli użytkownikowi udało się go przewyższyć.
     * \details W przypadku pobicia najwyższego wyniku, nowy wynik ustawiany jest jako najwyższy oraz zapisywany jest do pliku.
     * \details Slot ten odtwarza również dźwięk zjedzenia owocu przez węża.
     */
    void updateScore(int s);

    /*!
     * \brief Slot odpowiedzialny za sterowanie zatrzymaniem gry
     * \param b parametr określający czy gra ma zostać zatrzymana
     * \details Slot ten odpowiada za zatrzymywanie oraz wznawianie rozgrywki. Zostaje on wywołany:
     * \details - podczas wciśnięcia przycisku Start oraz Restart - przyciski te domyślnie są wciśniete, dlatego kiedy użytkownik naciska przycisk tak naprawdę
     * go zwalnia co powoduje przekazanie do parametru <B>b</B> wartości <B>false</B>
     * co powoduje wznowienie rozgrywki oraz zmianę aktywnej zakładki.
     * \details - podczas wciśnięcia klawiszy ESC, Spacja oraz przycisku Options - przekazywana jest wtedy wartość <B>true</B>,
     * zmieniając aktywną zakładkę na zakładkę menu, zatrzymując grę oraz muzykę.
     * \details - dodatkowo, rozgrywka zakończy się przegraną zmienia on aktywną zakładkę na
     * zakładkę wyników rozgrywki oraz wyświetla aktualny i najwyższy wynik.
     */
    void pressPause(bool b);

    /*!
     * \brief Slot odpowiedzialny za zresetowanie gry
     * \details Slot ten wywoływany jest w momencie zatwierdzenia zmian w opcjach, zmiany motywu oraz podczas przegrania rozgrywki. Slot ten powoduje
     * wyzerowanie wartości <B>d_time</B>, <B>time</B>, zatrzymanie muzyki, ustawienie przycisków Start oraz Restart jako wciśnięte (co powoduje wywołanie
     * slotu pressPause(bool b) który z kolei wyświetla okno o wynikach) oraz usunięcie i utworzenie nowego obiektu draw_snake, który zostaje dodany do okna gry.
     * Slot ten również wywołuje createScore().
     */
    void restartGame();

    /*!
     * \brief Slot zamykający aplikację
     * \details Slot ten wywoływany jest w momencie wciśnięcia przycisku Exit oraz naciśnięcia klawisza ESC w oknie menu.
     * \details Powoduje on zamknięcie gry wraz ze wszystkimi oknami.
     */
    void pressExitGame();

    /*!
     * \brief Ustawienie aktualnie wybranego motywu
     * \param theme_id ID aktualnie wybranego motywu
     * \details Przypisuje on wartość przekazaną przez parametr do <B>theme_id</B>.
     */
    void setTheme(int theme_id);

    /*!
     * \brief Ustawia okno menu jako aktywna zakładkę
     * \details Slot wywoływany po wciśnięciu przycisku Menu w zakładce wyników rozgrywki. Powoduje on zmianę aktywnej zakładki na zakładkę menu.
     */
    void showMenu();


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

    /*!
     * \brief Event wywoływany w momencie wciśnięcia klawisza na klawiaturze
     * \param event Parametr przekazuje dane QKeyEvent
     * \details Event ten, zależnie od tego jaki klawisz zostanie wciśnięty, wykonuje następujące czynności: \n
     * - klawisz <B>Spacja</B> powoduje <B>zatrzymanie gry</B> (wywołanie metody pressPause(bool b) ), jeśli gra jest zatrzymana (bądź się jeszcze nie rozpoczęła) - powoduje wciśnięcie ostatnio
     * używanego przycisku (jeśli żaden klawisz przycisk nie był używany, będzie to Start), \n
     * - klawisz <B>ESC</B> powoduje <B>wyjście</B> z gry jeśli został wciśnięty w oknie menu lub wyników, natomiast jeśli został wciśniety w oknie gry - zatrzymuje grę (wywołanie metody pressPause(bool b) ),
     * - klawisze <B>W, S, A, D</B> oraz <B>klawisze strzałek</B> służą do zmiany <B>kierunku poruszania się węża</B>.
     */
    void keyPressEvent(QKeyEvent *event);

    /*!
     * \brief Event wywoływany po zamknięciu okna
     * \param event Parametr przekazuje dane QCloseEvent
     * \details Event ten powoduje zamknięcie wszystkich aktywnych okien w grze.
     */
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
