#include "draw_snake.h"

draw_snake::draw_snake( QWidget *parent ) : QWidget(parent) {
}

draw_snake::draw_snake( int width, int height, Options *options_w, int theme_id, QWidget *parent) : QWidget(parent) {

    snake = new snake_algorithm (

        options_w->getColumns(),
        options_w->getRows(),
        options_w->isCollision(),
        options_w->isEgg(),
        options_w->getFruit1Value(),
        options_w->getFruit2Value(),
        options_w->getFruit3Value(),
        options_w->getFruitsToGrow()

);

    this->theme_id = theme_id;

    int xCellSize = width / snake->getX();
    int yCellSize = height / snake->getY();

    if(xCellSize > yCellSize)
        CellSize = yCellSize;
    else
        CellSize = xCellSize;


    pixToHorizontalCentre = (width  - ( snake->getX() * CellSize )) / 2;
    pixToVerticalCentre = (height - (snake->getY() * CellSize)) / 2;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gameLoop()));

}

void draw_snake::setSpeed(int speed) {

    this->speed = speed;
    timer->setInterval(this->speed);
}

void draw_snake::gameLoop() {

    if( snake->isGameOver() == false ) {

        snake->move();
        update();


    } else {
        timer->stop();
        isGameStarted = false;

    }
}

void draw_snake::startGame() {

    timer->start(speed);
    isGameStarted = true;

}

void draw_snake::pauseGame() {

    timer->stop();
    isGameStarted = false;

}

void draw_snake::paintEvent(QPaintEvent *) {

    painter = new QPainter(this);

    Wall_Brush = new QBrush(Qt::SolidPattern);


    switch (theme_id) {

        case 0:

            Snake = new QPixmap         (":/themes/themes/Default/snakeSegment.jpg");
            Null = new QPixmap          (":/themes/themes/Default/gameBackground.jpg");
            Fruit_1 = new QPixmap       (":/themes/themes/Default/appleTexture.jpg");
            Fruit_2 = new QPixmap       (":/themes/themes/Default/bananaTexture.jpg");
            Fruit_3 = new QPixmap       (":/themes/themes/Default/pineappleTexture.jpg");
            Eggs = new QPixmap          (":/themes/themes/Default/rockTexture.jpg");

            Wall_Brush->setColor(Qt::white);

        break;

        case 1:

            Snake = new QPixmap         (":/themes/themes/Flat/snakeSegment.jpg");
            Null = new QPixmap          (":/themes/themes/Flat/gameBackground.jpg");
            Fruit_1 = new QPixmap       (":/themes/themes/Flat/appleTexture.jpg");
            Fruit_2 = new QPixmap       (":/themes/themes/Flat/bananaTexture.jpg");
            Fruit_3 = new QPixmap       (":/themes/themes/Flat/pineappleTexture.jpg");
            Eggs = new QPixmap          (":/themes/themes/Flat/rockTexture.jpg");

            Wall_Brush->setColor(Qt::white);

        break;

        case 2:

            Snake = new QPixmap         (":/themes/themes/Draft/snakeSegment.jpg");
            Null = new QPixmap          (":/themes/themes/Draft/gameBackground.jpg");
            Fruit_1 = new QPixmap       (":/themes/themes/Draft/appleTexture.jpg");
            Fruit_2 = new QPixmap       (":/themes/themes/Draft/bananaTexture.jpg");
            Fruit_3 = new QPixmap       (":/themes/themes/Draft/pineappleTexture.jpg");
            Eggs = new QPixmap          (":/themes/themes/Draft/rockTexture.jpg");

            Wall_Brush->setColor(Qt::black);

        break;

        case 3:

            Snake = new QPixmap         (":/themes/themes/Win95/snakeSegment.jpg");
            Null = new QPixmap          (":/themes/themes/Win95/gameBackground.jpg");
            Fruit_1 = new QPixmap       (":/themes/themes/Win95/appleTexture.jpg");
            Fruit_2 = new QPixmap       (":/themes/themes/Win95/bananaTexture.jpg");
            Fruit_3 = new QPixmap       (":/themes/themes/Win95/pineappleTexture.jpg");
            Eggs = new QPixmap          (":/themes/themes/Win95/rockTexture.jpg");

            Wall_Brush->setColor(Qt::white);

        break;
    }

    painter->setPen(Qt::NoPen);


    for( int i = 0; i < (snake->getY()) ; i++ ) {

        for( int j = 0; j < (snake->getX()) ; j++ ) {

            switch(snake->board[i][j]) {

                case content::Wall:
                    painter->setBrush( *Wall_Brush);
                    painter->drawRect(j*CellSize + pixToHorizontalCentre, i*CellSize + pixToVerticalCentre, CellSize, CellSize);
                    break;

                case content::Null:
                    painter->setBrush( *Null);
                    painter->drawRect(j*CellSize + pixToHorizontalCentre, i*CellSize + pixToVerticalCentre, CellSize, CellSize);
                    break;

                case content::Snake:
                    painter->drawPixmap(j*CellSize + pixToHorizontalCentre, i*CellSize + pixToVerticalCentre, CellSize, CellSize, *Snake);
                    break;

                case content::Egg:
                    painter->drawPixmap(j*CellSize + pixToHorizontalCentre, i*CellSize + pixToVerticalCentre, CellSize, CellSize, *Eggs);
                    break;

                case content::Fruit_1:
                    painter->drawPixmap(j*CellSize + pixToHorizontalCentre, i*CellSize + pixToVerticalCentre, CellSize, CellSize, *Fruit_1);
                    break;

                case content::Fruit_2:
                    painter->drawPixmap(j*CellSize + pixToHorizontalCentre, i*CellSize + pixToVerticalCentre, CellSize, CellSize, *Fruit_2);
                    break;

                case content::Fruit_3:
                    painter->drawPixmap(j*CellSize + pixToHorizontalCentre, i*CellSize + pixToVerticalCentre, CellSize, CellSize, *Fruit_3);
                    break;
            }
        }
    }
}

draw_snake::~draw_snake() {

    timer->~QTimer();
    snake->~snake_algorithm();
}
