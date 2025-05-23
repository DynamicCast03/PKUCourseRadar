#include "debug_utils.h"

void displayCourses(const CourseManager& manager)
{
    qDebug() << "--- 开始打印 CourseManager 中的课程信息 (不修改 Course 类) ---";
    if (manager.AllCourses.isEmpty()) {
        qDebug() << "CourseManager 中没有课程信息。";
    } else {
        int count = 0;
        // 遍历 CourseManager 的 AllCourses 集合
        for (const Course& course : manager.AllCourses) {
            qDebug() << "课程 #" << ++count;
            qDebug() << "  课程名称:" << course.name;
            qDebug() << "  教学楼:" << course.building;
            qDebug() << "  教室:" << course.room;

            qDebug() << "  课程时间:";
            // 直接访问 CourseTime 的 table 并解析二进制
            const QString weekDays[] = {"", "周一", "周二", "周三", "周四", "周五", "周六", "周日"};
            // CourseTime::table 的下标从 1 到 7 对应周一到周日
            for (int i = 1; i <= 7; ++i) {
                if (i < course.ct.table.size()) { // 确保索引在范围内
                    QString sessionsString;
                    int daySchedule = course.ct.table[i];
                    for (int session = 1; session <= 12; ++session) {
                        // 检查对应节次的二进制位
                        if ((daySchedule >> session) & 1) {
                            sessionsString += QString::number(session) + " ";
                        }
                    }
                    if (!sessionsString.isEmpty()) {
                        qDebug() << "    " << weekDays[i] << ":" << sessionsString.trimmed();
                    } else {
                        qDebug() << "    " << weekDays[i] << ": 无课程";
                    }
                } else {
                    qDebug() << "    " << weekDays[i] << ": 错误 - CourseTime table 索引超出范围";
                }
            }
            // 直接访问 Course 的 tags 并打印
            qDebug() << "  课程标签:" << course.tags; // 将 QSet 转换为 QList 便于打印
            qDebug() << "--------------------"; // 分隔符
        }
        qDebug() << "总计:" << manager.AllCourses.size() << "门课程。";
    }
    qDebug() << "--- 打印 CourseManager 中的课程信息结束 ---";
}
