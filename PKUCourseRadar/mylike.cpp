#include "mylike.h"

MyLike MyLike::the_liked;

MyLike::MyLike(QObject *parent)
    : QObject{parent}
{}
