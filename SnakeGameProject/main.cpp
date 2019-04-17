#include "mainwindow.h"
#include <QApplication>

/*!
  * <IMG SRC="title.png"></IMG>
  * \mainpage
  * \section Opis-projektu Opis tematyki projektu
  *Opis tematyki projektu
  * Tematem projektu jest wydana po raz pierwszy w połowie lat siedemdziesiątych XX wieku gra komputerowa „Snake”.
  * Jest to zręcznościowa gra, w której grający kontroluje kierunek w którym porusza się stworzenie zwane tytułowym Wężem.
  * Gracz ma za zadanie tak sterować głównym bohaterem aby zbierać jedzenie pojawiające się na planszy (lub inne przedmioty w zależności
  * od zamysłu twórcy), próbując nie uderzyć głową węża w krawędzie planszy, jego tułów lub przeszkody przez niego pozostawione.
  * Zebrany pokarm to oczywiście punkty dla gracza, ma on ich zdobyć jak najwięcej, jednak najistotniejszym aspektem jest zwiększanie się
  * długości węża. Wąż robi się coraz dłuższy co naturalnie utrudnia graczowi zadanie. Wymaga to coraz większej uwagi i czasami strategicznego
  * podejścia do obieranej trasy przez węża do kolejnego przedmiotu. Sterowanie jest najprostszym z możliwych najczęściej służą do tego cztery
  * klawisze kierunkowe.
  * \section technologie Użyte technologie
  * Projekt został napisany obiektowo w języku programowania C++ w oparciu o Framework QT, który jest zestawem przenośnych bibliotek i narzędzi
  * programistycznych dedykowanych m.in. dla języków C++, QML i Java. Zawiera m.in. Klasy służące do budowy graficznego interfejsu programów,
  * obsługi plików, również multimedialnych takich jak grafiki czy dźwięki. Środowisko QT obsługuje wiele platform m.in. Mac OS X, Android, Linuks.
  * Nie ogranicza do tworzenia programów pod konkretny system, jest wykorzystywany przez znane na całym świecie firmy programistyczne, posiada
  * bardzo bogatą dokumentację i wsparcie, stąd też jego wybór. Kompilacja wykonywana była przy użyciu MS Visual C++ 2013 jako jednym z wielu
  * współpracujących ze środowiskiem QT. Projekt został stworzony z myślą o kompilacji i uruchomieniu w systemie Windows.
  * \author Wychowski Norbert 15B
  * \author Zachariasz Łukasz 15B
  * \version 2.3
  * \date 14.01.2017
 */

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    /*!
     * \brief Utworzenie okna głównego
     */
    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);   ///

    w.show();
    return a.exec();
}
