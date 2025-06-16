#include "mylike.h"

MarkedCourseManager MarkedCourseManager::theMarkedManager;

MarkedCourseManager::MarkedCourseManager(QObject *parent)
    : QObject{parent}
{}
