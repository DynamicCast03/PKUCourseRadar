#include "radarwindow.h"
#include "ui_radarwindow.h"

RadarWindow::RadarWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RadarWindow)
{
    ui->setupUi(this);
    nowTable = QVector<QVector<QSet<QUuid>>>(7, QVector<QSet<QUuid>>(12));
    nowDisabled = QVector<QVector<int>>(7, QVector<int>(12, 0));
    nowReadyTags = CourseManager::theManager.AllTags;
    nowSelectedTags = QSet<QString>();
    ui -> Table -> setCanDisable(true);
    connect(ui -> Table, &CourseTableWidget::cellClicked, this, &RadarWindow::cellClicked);
    connect(ui -> Table, &CourseTableWidget::cellRightClicked, this, &RadarWindow::cellRightClicked);
    showTags();
    reSearchCourses();
}

RadarWindow::~RadarWindow()
{
    delete ui;
}

void RadarWindow::on_i_name_textChanged(const QString &str)
{
    nowName = str;
    reSearchCourses();
}

void RadarWindow::on_i_teacher_textChanged(const QString &str)
{
    nowTeacher = str;
    reSearchCourses();
}

void RadarWindow::on_i_building_textChanged(const QString &str)
{
    nowBuilding = str;
    reSearchCourses();
}

void RadarWindow::on_i_room_textChanged(const QString &str)
{
    nowRoom = str;
    reSearchCourses();
}

void RadarWindow::on_i_tags_textChanged(const QString &str)
{
    nowSearchingTags = str;
    showTags();
}

void RadarWindow::reSearchCourses()
{
    nowCourses.clear();
    nowTable = QVector<QVector<QSet<QUuid>>>(7, QVector<QSet<QUuid>>(12));
    for(auto uuid : CourseManager::theManager.AllCourses.keys())
    {
        Course course = CourseManager::theManager.AllCourses[uuid];
        if((nowName.isEmpty() || course.name.contains(nowName, Qt::CaseInsensitive))
        && (nowTeacher.isEmpty() || course.teacher.contains(nowTeacher, Qt::CaseInsensitive))
        && (nowBuilding.isEmpty() || course.building.contains(nowBuilding, Qt::CaseInsensitive))
        && (nowRoom.isEmpty() || course.room.contains(nowRoom, Qt::CaseInsensitive))
        && (nowSelectedTags.isEmpty() || course.tags.contains(nowSelectedTags))
        && isFree(uuid)
        ){
            nowCourses.insert(course.id);
            qDebug() << course.id.toString() << "\n";
            for(int i = 0; i < 7; ++i){
                for(int j = 0; j < 12; ++j){
                    if(course.ct.table[i][j] == 1)
                    {
                        nowTable[i][j].insert(course.id);
                    }
                }
            }

        }
    }
    for(int i = 0; i < 7; ++i){
        for(int j = 0; j < 12; ++j){
            ui -> Table -> cells[i][j] -> setDisplayText(QString::number(nowTable[i][j].size()));
        }
    }
}


void RadarWindow::on_l_all_tags_itemDoubleClicked(QListWidgetItem *item)
{
    if(!item) return;
    QString tag = item -> text();
    nowReadyTags.remove(tag);
    nowSelectedTags.insert(tag);
    showTags();
    reSearchCourses();
}

void RadarWindow::on_l_selected_tags_itemDoubleClicked(QListWidgetItem *item)
{
    if(!item) return;
    QString tag = item -> text();
    nowSelectedTags.remove(tag);
    nowReadyTags.insert(tag);
    showTags();
    reSearchCourses();
}

void RadarWindow::showTags()
{
    ui -> l_all_tags -> clear();
    ui -> l_selected_tags -> clear();
    for(const QString& tag : nowReadyTags)
    {
        if(nowSearchingTags.isEmpty() || tag.contains(nowSearchingTags, Qt::CaseInsensitive))
        {
            ui -> l_all_tags -> addItem(new QListWidgetItem(tag));
        }
    }
    for(const QString& tag : nowSelectedTags)
    {
        ui -> l_selected_tags -> addItem(new QListWidgetItem(tag));
    }
}

void RadarWindow::cellClicked(int x, int y)
{
    qDebug() << x << " " << y;
    if(nowTable[x - 1][y - 1].isEmpty()) return;
    QVector<QUuid> markedCourses;
    for(const QUuid id : nowTable[x - 1][y - 1]) {
        markedCourses.push_back(id);
    }
    CourseInfoWindow* window = new CourseInfoWindow(this, markedCourses, x, y);
    window->show();
}

void RadarWindow::cellRightClicked(int x, int y, bool disabled)
{
    nowDisabled[x - 1][y - 1] = disabled;
    reSearchCourses();
}

bool RadarWindow::isFree(const QUuid& courseId)
{
    for(int i = 0; i < 7; ++i){
        for(int j = 0; j < 12; ++j){
            if(CourseManager::theManager.AllCourses[courseId].ct.table[i][j] && nowDisabled[i][j]) return false;
        }
    }
    return true;
}
