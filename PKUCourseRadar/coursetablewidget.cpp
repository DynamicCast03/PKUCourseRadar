#include "coursetablewidget.h"

CourseTableWidget::CourseTableWidget(QWidget *parent)
    : QWidget{parent}, layout{new QGridLayout{this}}
{
    layout->setSpacing(0);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    QStringList headerLabels = {tr("\\"), tr("一"), tr("二"), tr("三"), tr("四"), tr("五"), tr("六"), tr("日")};
    for (int i = 0; i < headerLabels.size(); i++) {
        CourseCell *cell = new CourseCell(this, headerLabels[i]);
        cell->isConstText=true;
        layout->addWidget(cell, 0, i);
    }

    for(int i = 1; i <= 12; i++){
        CourseCell *cell = new CourseCell(this, QString::number(i));
        cell->isConstText=true;
        layout->addWidget(cell, i, 0);
    }
    layout->setColumnStretch(0, 1);
    layout->setRowStretch(0, 1);
    cells = QVector<QVector<CourseCell*>>(7, QVector<CourseCell*>(12, nullptr));
    for(int i = 1; i <= 12; i++){
        for(int j = 1; j <= 7; j++){
            CourseCell *cell = new CourseCell(this, "");
            connect(cell, &CourseCell::clicked, this, &CourseTableWidget::handleCellClicked);
            connect(cell, &CourseCell::rightClicked, this, &CourseTableWidget::handleCellRightClicked);
            layout->addWidget(cell, i, j);
            cell->x = i;
            cell->y = j;
            cells[j - 1][i - 1] = cell;
        }
        layout->setRowStretch(i, 1);
    }
    for(int j = 1; j <= 7; j++){
        layout->setColumnStretch(j, 2);
    }
}

void CourseTableWidget::handleCellClicked(){
    CourseCell *cell = qobject_cast<CourseCell*>(sender());
    if(cell){
        emit cellClicked(cell->y, cell->x);
    }
}

void CourseTableWidget::handleCellRightClicked(bool disabled){
    CourseCell *cell = qobject_cast<CourseCell*>(sender());
    if(cell){
        emit cellRightClicked(cell->y, cell->x, cell->disabled);
    }
}
