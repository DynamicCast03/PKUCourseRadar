#include "aboutus.h"
#include "ui_aboutus.h"
#include "utils.h"

AboutUs::AboutUs(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutUs)
{
    ui->setupUi(this);
}

AboutUs::~AboutUs()
{
    delete ui;
}
