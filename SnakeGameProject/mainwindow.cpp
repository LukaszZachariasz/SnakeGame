#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Windows.h>
#include <QMouseEvent>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QDataStream>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    theme_w = new theme_window();
    options_w = new Options(theme_w);

    game_music_playlist = new QMediaPlaylist();
    game_over_sound = new QMediaPlayer();
    catch_fruit_sound = new QMediaPlayer();
    game_music_sound = new QMediaPlayer();


    QFile f_high_score_save_read("data.snk");
    QDataStream dataStreamReader(&f_high_score_save_read);

    if (!f_high_score_save_read.open(QIODevice::ReadOnly)) {

        highScore = 0;

    } else {

        dataStreamReader >> highScore;
        ui->highScoreLabel->setText(QString("%1").arg( highScore ));
        f_high_score_save_read.close();

    }


    game_over_sound->setMedia(QUrl("qrc:/sound/sound/game_over_sound.mp3"));
    catch_fruit_sound->setMedia(QUrl("qrc:/sound/sound/catch_fruit_sound.mp3"));

    game_music_playlist->addMedia(QUrl("qrc:/sound/sound/game_music_sound.mp3"));
    game_music_playlist->addMedia(QUrl("qrc:/sound/sound/game_music_sound2.mp3"));
    game_music_playlist->setPlaybackMode(QMediaPlaylist::Loop);

    game_music_sound->setPlaylist(game_music_playlist);

    snake_widget = new draw_snake (

        ui->gameFrame->frameGeometry().width(),
        ui->gameFrame->frameGeometry().height(),
        options_w,
        theme_id

    );

    ui->gameFrame->layout()->addWidget( snake_widget );
    snake_widget->setSpeed(options_w->getSpeedValue());

    createTimer();
    createScore();

    connect(options_w, SIGNAL(updateOptions()), this, SLOT(restartGame()) );

    connect(ui->pushStartGame, SIGNAL(toggled(bool)), this, SLOT(pressPause(bool)) );
    connect(ui->pushExitGame, SIGNAL(pressed()), this, SLOT(pressExitGame()));
    connect(ui->pushOptions, SIGNAL(pressed()), options_w, SLOT(showOptions()));

    connect(ui->pushExitOver, SIGNAL(pressed()), this, SLOT(pressExitGame()) );
    connect(ui->pushRestart, SIGNAL(pressed()), this, SLOT(restartGame()) );
    connect(ui->pushRestart, SIGNAL(toggled(bool)), this, SLOT(pressPause(bool)) );
    connect(ui->pushMenu, SIGNAL(pressed()), this, SLOT(showMenu()) );

    connect(theme_w, SIGNAL(updateTheme(int)), this, SLOT(setTheme(int)) );
    connect(theme_w, SIGNAL(updateTheme(int)), this, SLOT(restartGame()) );

    ui->tabWidget->tabBar()->hide();
    activateTabGame(1);
    ui->graphicsPause->setVisible(false);

}

void MainWindow::createScore() {

    ui->scoreLabel->setText("0");
    connect(snake_widget->snake, SIGNAL(updateScore(int)), this, SLOT(updateScore(int)));

}

void MainWindow::createTimer() {

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()) );
    ui->timeLabel->setText("00:00");

}

void MainWindow::timerTick() {

    if (snake_widget->snake->isGameOver() == true) {

        timer->stop();

        game_music_sound->stop();
        game_over_sound->play();

        Sleep(200);
        restartGame();
    }

    if(snake_widget->isGameStarted == true)
        timer->start(10);
    else
        timer->stop();

    d_time+=0.01;
    time = (int) d_time;
    ui->timeLabel->setText(QString("%1").arg(time/60, 2, 10, QChar('0')) + ":" + QString("%1").arg(time%60, 2, 10, QChar('0')) );
}

void MainWindow::updateScore(int s) {

    if (s > highScore) {

        highScore = s;
        ui->highScoreLabel->setText(QString("%1").arg( highScore ));

        QFile f_high_score_save_write("data.snk");
        QDataStream dataStreamWriter(&f_high_score_save_write);

        if (f_high_score_save_write.open(QFile::WriteOnly)) {

            dataStreamWriter << highScore;
            f_high_score_save_write.close();
        }

    }
    ui->scoreLabel->setText(QString("%1").arg( s ));

    catch_fruit_sound->play();

}

void MainWindow::pressPause(bool b) {


    if (snake_widget->isGameStarted == false) {

        snake_widget->startGame();
        game_music_sound->play();
        game_over_sound->stop();
        activateTabGame(0);
        snake_widget->setSpeed(options_w->getSpeedValue());
        ui->graphicsPause->setVisible(false);

    }

    if ( b == true ) {

        ui->pushStartGame->setChecked(true);
        ui->pushRestart->setChecked(true);
        snake_widget->pauseGame();
        game_music_sound->pause();

        if(snake_widget->snake->isGameOver() == true) {
            ui->highScoreLabelResult->setText(QString("%1").arg( highScore ));
            ui->scoreLabelResult->setText( ui->scoreLabel->text() );
            activateTabGame(2);
        }
        else
            activateTabGame(1);

    } else {

        snake_widget->startGame();
        game_music_sound->play();
        activateTabGame(0);

    }

    timerTick();

}

void MainWindow::restartGame() {

    time = 0;
    d_time = 0.0;

    ui->timeLabel->setText("00:00");
    ui->pushStartGame->setChecked(true);
    ui->pushStartGame->setEnabled(true);

    ui->pushRestart->setChecked(true);
    ui->pushRestart->setEnabled(true);

    game_music_sound->stop();

    delete snake_widget;

    snake_widget = new draw_snake (

        ui->gameFrame->frameGeometry().width(),
        ui->gameFrame->frameGeometry().height(),
        options_w,
        theme_id

    );

    ui->gameFrame->layout()->addWidget( snake_widget );

    createScore();
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Escape) {

        if (ui->tabWidget->currentIndex() == 0) {

            pressPause(true);
            ui->graphicsPause->setVisible(true);

        } else {
            pressExitGame();
        }
    }


    if (event->key() == Qt::Key_Space && snake_widget->isGameStarted) {     
        pressPause(true);
        activateTabGame(1);
        ui->graphicsPause->setVisible(true);
    }

    if(snake_widget->isGameStarted == true) {

        switch( event->key() ) {

        case Qt::Key_A: case Qt::Key_Left:
            if(snake_widget->snake->snake_array != array::r)
                snake_widget->snake->snake_array = array::l;
            update();

        break;

        case Qt::Key_D: case Qt::Key_Right:
            if(snake_widget->snake->snake_array != array::l)
                snake_widget->snake->snake_array = array::r;
            update();
        break;

        case Qt::Key_W: case Qt::Key_Up:
            if(snake_widget->snake->snake_array != array::down)
                snake_widget->snake->snake_array = array::up;
            update();
        break;

        case Qt::Key_S: case Qt::Key_Down:
            if( snake_widget->snake->snake_array != array::up)
                snake_widget->snake->snake_array = array::down;
            update();
        break;
        }
    }
    QWidget::keyPressEvent(event);
}

/////////////////////////// dopisane - poczatek

void MainWindow::mousePressEvent(QMouseEvent* event) {

    if(event->button() == Qt::LeftButton) {

        mLastMousePosition = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {

    if( event->buttons().testFlag(Qt::LeftButton) ) {
        this->move(this->pos() + (event->pos() - mLastMousePosition));
    }
}

void MainWindow::pressExitGame() {

    qApp->quit();
}

void MainWindow::setTheme(int theme_id) {
    this->theme_id = theme_id;
}

void MainWindow::showMenu() {
    activateTabGame(1);
}

void MainWindow::activateTabGame(int id) {

    ui->tabWidget->setCurrentIndex(id);
}

////////////////////////////// dopisane - koniec


void MainWindow::closeEvent(QCloseEvent *) {
    qApp->quit();
}

MainWindow::~MainWindow() {
    delete ui;
    f_high_score_save_read.close();
    f_high_score_save_write.close();
}

