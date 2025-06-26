#include "addcommentwindow.h"
#include "ui_addcommentwindow.h"
#include "coursemanager.h"

AddCommentWindow::AddCommentWindow(QUuid courseId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCommentWindow)
    , courseId(courseId)
{
    ui->setupUi(this);
    ui->label->setText(tr("为课程 %1 撰写评价").arg(QString::fromStdString(CourseManager::theManager.AllCourses[courseId].name.toStdString())));
    on_sl_rating_valueChanged(ui->sl_rating->value());
}

AddCommentWindow::~AddCommentWindow()
{
    delete ui;
}

void AddCommentWindow::on_sl_rating_valueChanged(int value)
{
    ui->lb_rating->setText(QString(tr("评分：")) + QString::number(value / 10.0));
}


void AddCommentWindow::on_btn_submit_clicked()
{
    CourseComment newComment;
    newComment.commentId = QUuid::createUuid();
    newComment.courseId = courseId;
    newComment.comment = ui->te_comment->toPlainText();
    newComment.commenterId = CourseManager::theManager.currentUserId;
    qDebug() << CourseManager::theManager.currentUserId.toString() << "\n";
    qDebug() << newComment.commenterId.toString() << "\n";
    newComment.commentTime = QDateTime::currentSecsSinceEpoch();
    newComment.rating = ui->sl_rating->value() / 10.0;
    CourseManager::theManager.AllComments[newComment.commentId] = newComment;
    CourseManager::theManager.AllCourses[courseId].comments.push_back(newComment.commentId);
    close();
}

