#include "coursetime.h"

CourseTime::CourseTime() {
    table = QVector<int>(8);
}

void CourseTime::add(int day, int session){
    table[day] |= (1 << session);
}

bool CourseTime::conflict(const CourseTime& ct){
    for(int i = 1; i <= 7; i++){
        if(table[i] & ct.table[i]) return 1;
    }
    return 0;
}

