#include "options.h"
#include "ui_options.h"


Options::Options(QWidget *parent) : QDialog(parent), ui(new Ui::Options) {

    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);   ///

    connect(ui->radioButton_4, SIGNAL(toggled(bool)), this, SLOT(setEnabledNonStandardOptions(bool)) );
    connect(ui->eggs, SIGNAL(toggled(bool)), this, SLOT(setEnabledEggOptions(bool)) );
    connect(ui->pushOkOptions, SIGNAL(pressed()), this, SLOT(pushOkOptions())); ///
    connect(ui->pushCancelOptions, SIGNAL(pressed()), this, SLOT(pushCancelOptions())); ///
}

Options::Options(theme_window *theme, QWidget *parent) : QDialog(parent), ui(new Ui::Options) {

    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);   ///

    connect(ui->radioButton_4, SIGNAL(toggled(bool)), this, SLOT(setEnabledNonStandardOptions(bool)) );
    connect(ui->eggs, SIGNAL(toggled(bool)), this, SLOT(setEnabledEggOptions(bool)) );
    connect(ui->pushOkOptions, SIGNAL(pressed()), this, SLOT(pushOkOptions())); ///
    connect(ui->pushCancelOptions, SIGNAL(pressed()), this, SLOT(pushCancelOptions())); ///
    connect(ui->pushChangeTheme, SIGNAL(clicked(bool)), theme, SLOT(showTheme()) );

    connect(ui->radioButton, SIGNAL(pressed()), this, SLOT(updateValSmall()));
    connect(ui->radioButton_2, SIGNAL(pressed()), this, SLOT(updateValNormal()));
    connect(ui->radioButton_3, SIGNAL(pressed()), this, SLOT(updateValBig()));


}

void Options::updateValSmall() {

    ui->rows->setValue(20);
    ui->columns->setValue(35);
}

void Options::updateValNormal() {

    ui->rows->setValue(30);
    ui->columns->setValue(53);
}

void Options::updateValBig() {

    ui->rows->setValue(50);
    ui->columns->setValue(88);
}

int Options::getRows() {
    return rows;
}

int Options::getColumns() {
    return columns;
}

int Options::getFruitsToGrow() {
    return ui->FruitsToGrow->value();
}

int Options::getFruit1Value() {
    return ui->Fruit_1_Value_Options->value();
}

int Options::getFruit2Value() {
    return ui->Fruit_2_Value_Options->value();
}

int Options::getFruit3Value() {
    return ui->Fruit_3_Value_Options->value();
}

bool Options::isCollision() {
    return ui->collisions->isChecked();
}

bool Options::isEgg() {
    return ui->eggs->isChecked();
}

void Options::showOptions() {

    show();
    activateWindow();
    raise();
}

void Options::setEnabledNonStandardOptions(bool b) {

    ui->label->setEnabled(b);
    ui->label_2->setEnabled(b);
    ui->columns->setEnabled(b);
    ui->rows->setEnabled(b);
}

void Options::setEnabledEggOptions(bool b) {

    ui->FruitsToGrow->setEnabled(b);
    ui->label_3->setEnabled(b);
}

Options::~Options() {
    delete ui;
}

/////////////////////////// dopisane - poczatek

int Options::getSpeedValue() {

   return ui->dial->value();
}

void Options::mousePressEvent(QMouseEvent* event) {

    if (event->button() == Qt::LeftButton) {
        mLastMousePosition = event->pos();
    }
}

void Options::mouseMoveEvent(QMouseEvent* event) {

    if ( event->buttons().testFlag(Qt::LeftButton) ) {
        this->move(this->pos() + (event->pos() - mLastMousePosition));
    }
}

void Options::pushOkOptions() {

    QList<QRadioButton *> buttonList = ui->groupBox->findChildren<QRadioButton *>();

    for (int i=0; i<buttonList.length(); i++) {

        if ( buttonList[i]->isChecked() ) {

            if ( buttonList[i] == ui->radioButton ) {

                rows = 20;
                columns = 35;
                ui->rows->setValue(20);
                ui->columns->setValue(35);
                close();

            } else if ( buttonList[i] == ui->radioButton_2 ) {

                rows = 30;
                columns = 53;
                ui->rows->setValue(30);
                ui->columns->setValue(53);
                close();

            } else if ( buttonList[i] == ui->radioButton_3 ) {

                rows = 50;
                columns = 88;
                ui->rows->setValue(50);
                ui->columns->setValue(88);
                close();

            } else if( buttonList[i] == ui->radioButton_4 ) {

                rows = ui->rows->value();
                columns = ui->columns->value();
                close();

            }
        }
    }

    emit updateOptions();

}

void Options::pushCancelOptions() {

    close();
}

