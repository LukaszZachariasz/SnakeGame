#include "theme_window.h"
#include "ui_theme_window.h"

theme_window::theme_window(QWidget *parent) : QDialog(parent), ui(new Ui::theme_window) {

    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint); ///

    connect(ui->pushOkTheme, SIGNAL(pressed()), this, SLOT(pressOkTheme()));            ///
    connect(ui->pushCancelTheme, SIGNAL(pressed()), this, SLOT(pressCancelTheme()));    ///

}

void theme_window::showTheme() {

    show();
    activateWindow();
    raise();

}

void theme_window::mousePressEvent(QMouseEvent* event) {

    if(event->button() == Qt::LeftButton) {
        mLastMousePosition = event->pos();
    }
}

void theme_window::mouseMoveEvent(QMouseEvent* event) {

    if( event->buttons().testFlag(Qt::LeftButton) ) {
        this->move(this->pos() + (event->pos() - mLastMousePosition));
    }
}

void theme_window::pressOkTheme() {


    QList<QPushButton *> buttonList = ui->groupBox->findChildren<QPushButton *>();

    for(int  i= 0; i < buttonList.length(); i++) {
        if( buttonList[i]->isChecked() )
            emit updateTheme( i );
    }

    close();

}

void theme_window::pressCancelTheme() {

    close();
}

////////////////////////

theme_window::~theme_window() {
    delete ui;
}



