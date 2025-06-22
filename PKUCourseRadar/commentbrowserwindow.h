#ifndef COMMENTBROWSERWINDOW_H
#define COMMENTBROWSERWINDOW_H

#include "utils.h"

namespace Ui {
class CommentBrowserWindow;
}

class CommentBrowserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CommentBrowserWindow(QUuid courseId, QWidget *parent = nullptr);
    ~CommentBrowserWindow();
    QUuid courseId;
    QVector<QUuid> commentIds; // 依旧采用列表和QVector同步的架构
    void sync_list();
private slots:
    void on_btn_up_clicked();
    void on_btn_down_clicked();
    void on_lw_all_comments_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void on_btn_write_comment_clicked();
private:
    Ui::CommentBrowserWindow *ui;
};

#endif // COMMENTBROWSERWINDOW_H
