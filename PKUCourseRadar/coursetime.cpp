#include "coursetime.h"

CourseTime::CourseTime() {
    table = QVector<QVector<int>>(7, QVector<int>(12, 0));
}

CourseTime::CourseTime(const CourseTime& ct){
    table = ct.table;
}

CourseTime& CourseTime::operator=(const CourseTime& ct){
    table = ct.table;
    return *this;
}

void CourseTime::add(int day, int session){
    table[day - 1][session - 1] = 1;
}

bool CourseTime::conflict(const CourseTime& ct){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 12; j++){
            if(table[i][j] && ct.table[i][j]) return 1;
        }
    }
    return 0;
}

QString CourseTime::toString(){
    QString res;
    QStringList days = {tr("周一"), tr("周二"), tr("周三"), tr("周四"), tr("周五"), tr("周六"), tr("周日")};
    for(int i = 0; i < 7; i++){
        QString now;
        for(int j = 0; j < 12; j++){
            if(table[i][j]){
                if(now != "") now += ", ";
                now += QString::number(j + 1);
            }
        }
        if(now != ""){
            res += days[i] + tr(": 第") + now + tr("节;\n");
        }
    }
    return res;
}

