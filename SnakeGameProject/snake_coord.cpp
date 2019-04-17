#include "snake_coord.h"

snake_coord::snake_coord() {
    this->X = 0;
    this->Y = 0;
}

snake_coord::snake_coord(int X, int Y) {
    this->X = X;
    this->Y = Y;
}

int snake_coord::getX() {
    return X;
}

int snake_coord::getY() {
    return Y;
}

void snake_coord::setCoord(int X, int Y) {
    this->X = X;
    this->Y = Y;
}
