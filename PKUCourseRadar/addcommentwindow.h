#ifndef ADDCOMMENTWINDOW_H
#define ADDCOMMENTWINDOW_H

#include "utils.h"

namespace Ui {
class AddCommentWindow;
}

class AddCommentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddCommentWindow(QUuid courseId, QWidget *parent = nullptr);
    ~AddCommentWindow();
    QUuid courseId;
private slots:
    void on_sl_rating_valueChanged(int value);
    void on_btn_submit_clicked();

private:
    Ui::AddCommentWindow *ui;

signals:
    void updatecomment();
};

#endif // ADDCOMMENTWINDOW_H
