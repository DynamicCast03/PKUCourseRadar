#include "commentbrowserwindow.h"
#include "ui_commentbrowserwindow.h"
#include "coursemanager.h"
#include "addcommentwindow.h"

CommentBrowserWindow::CommentBrowserWindow(QUuid courseId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CommentBrowserWindow)
    , courseId(courseId)
{
    ui->setupUi(this);
    ui->label->setText(QString("课程评价 - ") + CourseManager::theManager.AllCourses[courseId].name);
    sync_list();

}

CommentBrowserWindow::~CommentBrowserWindow()
{
    delete ui;
}

void CommentBrowserWindow::sync_list(){
    ui->lw_all_comments->clear();
    commentIds.clear();
    for(QUuid commentId : CourseManager::theManager.AllCourses[courseId].comments){
        commentIds.push_back(commentId);
    }
    std::sort(commentIds.begin(), commentIds.end(), [](QUuid a, QUuid b){if(CourseManager::theManager.AllComments[a].likes.size() - CourseManager::theManager.AllComments[a].dislikes.size() != CourseManager::theManager.AllComments[b].likes.size() - CourseManager::theManager.AllComments[b].dislikes.size()) return CourseManager::theManager.AllComments[a].likes.size() - CourseManager::theManager.AllComments[a].dislikes.size() >
            CourseManager::theManager.AllComments[b].likes.size() - CourseManager::theManager.AllComments[b].dislikes.size(); return CourseManager::theManager.AllComments[a].commentId > CourseManager::theManager.AllComments[b].commentId; });
    for(QUuid commentId : commentIds)
    ui->lw_all_comments->addItem(new QListWidgetItem(CourseManager::theManager.AllComments[commentId].comment.replace("\n", "")));
}


void CommentBrowserWindow::on_lw_all_comments_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(!current) return;
    int row = ui->lw_all_comments->row(current);
    ui->tb_comment_content->setText(CourseManager::theManager.AllComments[commentIds[row]].format());
    ui->btn_up->setText(QString("👍") + QString::number(CourseManager::theManager.AllComments[commentIds[row]].likes.size()));
    ui->btn_down->setText(QString("👎") + QString::number(CourseManager::theManager.AllComments[commentIds[row]].dislikes.size()));
}

void CommentBrowserWindow::on_btn_up_clicked()
{
    int row = ui->lw_all_comments->currentRow();
    if(row == -1) return;
    QUuid commentId = commentIds[row];
    if(CourseManager::theManager.AllComments[commentId].likes.contains(CourseManager::theManager.currentUserId)){
        CourseManager::theManager.AllComments[commentId].likes.remove(CourseManager::theManager.currentUserId);
    }
    else{
        CourseManager::theManager.AllComments[commentId].likes.insert(CourseManager::theManager.currentUserId);
    }
    ui->btn_up->setText(QString("👍") + QString::number(CourseManager::theManager.AllComments[commentIds[row]].likes.size()));
    ui->btn_down->setText(QString("👎") + QString::number(CourseManager::theManager.AllComments[commentIds[row]].dislikes.size()));
    sync_list();
}


void CommentBrowserWindow::on_btn_down_clicked()
{
    int row = ui->lw_all_comments->currentRow();
    if(row == -1) return;
    QUuid commentId = commentIds[row];
    if(CourseManager::theManager.AllComments[commentId].dislikes.contains(CourseManager::theManager.currentUserId)){
        CourseManager::theManager.AllComments[commentId].dislikes.remove(CourseManager::theManager.currentUserId);
    }
    else{
        CourseManager::theManager.AllComments[commentId].dislikes.insert(CourseManager::theManager.currentUserId);
    }
    ui->btn_up->setText(QString("👍") + QString::number(CourseManager::theManager.AllComments[commentIds[row]].likes.size()));
    ui->btn_down->setText(QString("👎") + QString::number(CourseManager::theManager.AllComments[commentIds[row]].dislikes.size()));
    sync_list();
}


void CommentBrowserWindow::on_btn_write_comment_clicked()
{
    AddCommentWindow* w = new AddCommentWindow(courseId, this);
    connect(w, &AddCommentWindow::updatecomment, this, &CommentBrowserWindow::sync_list);
    w -> exec();
    sync_list();
}

