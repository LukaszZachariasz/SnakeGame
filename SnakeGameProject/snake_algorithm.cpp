#include "snake_algorithm.h"

snake_algorithm::snake_algorithm ( int xDim,
                                   int yDim,
                                   bool collision_walls,
                                   bool snake_Eggs,
                                   int Fruit_1_Value,
                                   int Fruit_2_Value,
                                   int Fruit_3_Value,
                                   int eaten_Fruits_To_Grow ) {

    srand(time(NULL));

    X = xDim;
    Y = yDim;

    this->Fruit_1_Value = Fruit_1_Value;
    this->Fruit_2_Value = Fruit_2_Value;
    this->Fruit_3_Value = Fruit_3_Value;

    this->eaten_Fruits_To_Grow = eaten_Fruits_To_Grow;
    this->collision_Walls = collision_walls;
    this->snake_Eggs = snake_Eggs;

    QVector<content> xDimension;

    for(int i = 0; i<X; i++)
        xDimension.push_back( content::Null );

    for(int i = 0; i<Y; i++)
        board.push_back( xDimension );

    for(int i= 0; i<X; i++) {
        board[0][i]    = content::Wall;
        board[Y-1][i] = content::Wall;
    }

    for(int i=0; i<Y; i++) {
        board[i][0]    = content::Wall;
        board[i][X-1] = content::Wall;
    }

    for(int i=0; i<4; i++) {
        snake_coords.push_back(
                    *(new snake_coord( (X/2)+i, Y/2 ) )
                    );
    }

    updateBoard();
    genFruit();
}

int snake_algorithm::getX() {
    return X;
}

int snake_algorithm::getY() {
    return Y;
}

bool snake_algorithm::isGameOver() {
    return gameOver;
}

void snake_algorithm::updateBoard() {

    for(int i = 0; i<egg_coords.length(); i++) {
        board[ egg_coords[i].getY() ][ egg_coords[i].getX() ] = content::Egg;
    }

    for(int i = 0; i<snake_coords.length(); i++) {
        board[ snake_coords[i].getY() ][ snake_coords[i].getX() ] = content::Snake;
    }
}

void snake_algorithm::move() {

    bool snake_ate = false;

    switch(snake_array) {

        case up:
            if( (snake_coords[0].getY() == 1) && collision_Walls == false )
                head_coord = new snake_coord( snake_coords[0].getX(), Y-2 );
            else
                head_coord = new snake_coord( snake_coords[0].getX(), snake_coords[0].getY()-1 );
            break;

        case down:
            if( (snake_coords[0].getY() == Y-2) && collision_Walls == false)
                head_coord = new snake_coord( snake_coords[0].getX(), 1 );
            else
                head_coord = new snake_coord( snake_coords[0].getX(), snake_coords[0].getY()+1 );
            break;

        case l:
            if( (snake_coords[0].getX() == 1) && collision_Walls == false)
                head_coord = new snake_coord( X-2, snake_coords[0].getY() );
            else
                head_coord = new snake_coord( snake_coords[0].getX()-1, snake_coords[0].getY() );
            break;

        case r:
            if( (snake_coords[0].getX() == X-2) && collision_Walls == false )
                head_coord = new snake_coord( 1, snake_coords[0].getY());
            else
                head_coord = new snake_coord( snake_coords[0].getX()+1, snake_coords[0].getY());
            break;
    }

    switch( board[ head_coord->getY() ][ head_coord->getX() ] ) {

        case content::Wall:
            gameOver = true;
            break;

        case content::Egg:
            gameOver = true;
            break;

        case content::Snake:
            gameOver = true;
            break;

        case content::Fruit_1:
            score+= Fruit_1_Value;
            eaten_Fruits++;
            snake_ate = true;
            is_Fruit_1 = false;
            genFruit();
            emit updateScore(score);
            break;

        case content::Fruit_2:
            score+= Fruit_2_Value;
            snake_ate = true;
            is_Fruit_2 = false;
            eaten_Fruits++;
            emit updateScore(score);
            break;

        case content::Fruit_3:
            score+= Fruit_3_Value;
            snake_ate = true;
            is_Fruit_3 = false;
            eaten_Fruits++;
            emit updateScore(score);
            break;

    }

    if( eaten_Fruits == eaten_Fruits_To_Grow ) {
        if( snake_Eggs == true ) genEgg();
        eaten_Fruits = 0;
    }

    if( gameOver == false ) {
        snake_coords.push_front( *head_coord );
        board[ snake_coords.last().getY() ][ snake_coords.last().getX() ] = content::Null;

        if( snake_ate == false ) snake_coords.pop_back();
    }
    updateBoard();
}

void snake_algorithm::genFruit() {

    srand(time(NULL));

    int x, y;

    if(is_Fruit_1 == false) {

        is_Fruit_1 = true;

        do {
            x = (rand() % (X-2) )+1;
            y = (rand() % (Y-2) )+1;
        } while( board[y][x] != content::Null  );

        board[y][x] = content::Fruit_1;
    }


    if(is_Fruit_2 == false && rand()%5 == 1 ) {

        is_Fruit_2 = true;

        do {
            x = (rand() % (X-2) )+1;
            y = (rand() % (Y-2) )+1;
        } while( board[y][x] != content::Null );

        board[y][x] = content::Fruit_2;
    }

    if(is_Fruit_3 == false && rand()%10 == 1) {

        is_Fruit_3 = true;

        do {
            x = (rand() % (X-2) )+1;
            y = (rand() % (Y-2) )+1;
        } while( board[y][x] != content::Null );

        board[y][x] = content::Fruit_3;
    }


}

void snake_algorithm::genEgg() {

    egg_coords.push_back
    (
        *( new snake_coord( snake_coords[0].getX(), snake_coords[0].getY() ) )
    );
}

snake_algorithm::~snake_algorithm() {

}

