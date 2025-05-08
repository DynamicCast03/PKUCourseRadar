#ifndef ABOUTUS_H
#define ABOUTUS_H

#include "utils.h"

namespace Ui {
class AboutUs;
}

class AboutUs : public QDialog
{
    Q_OBJECT

public:
    explicit AboutUs(QWidget *parent = nullptr);
    ~AboutUs();

private:
    Ui::AboutUs *ui;
};

#endif // ABOUTUS_H
