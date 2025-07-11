#include "bettermessagebox.h"
#include "betterbutton.h"

void BetterMessageBox::info(QWidget *parent, const QString &title, const QString &text) {
    QDialog dlg(parent);
    dlg.setWindowTitle(title);
    dlg.setModal(true);
    dlg.setFixedSize(340, 150);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dlg);
    QHBoxLayout *topLayout = new QHBoxLayout();

    QSize iconSize(32, 32);
    QLabel *icon = new QLabel(&dlg);
    QIcon ico = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation);
    icon->setFixedSize(iconSize);
    icon->setPixmap(ico.pixmap(iconSize));
    icon->setAlignment(Qt::AlignCenter);
    QLabel *lbl = new QLabel(text, &dlg);
    lbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QFont f = lbl->font();
    f.setPointSize(12);
    lbl->setFont(f);
    lbl->setWordWrap(true);

    topLayout->addWidget(icon, 1);
    topLayout->addSpacing(30);
    topLayout->addWidget(lbl, 5);

    mainLayout->addLayout(topLayout, 3);

    QHBoxLayout *botLayout = new QHBoxLayout();


    BetterButton *btn = new BetterButton(&dlg);
    btn->setText(tr("确定"));
    // btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    btn->setFixedSize(100, 50);
    QObject::connect(btn, &QPushButton::clicked, &dlg, &QDialog::accept);

    botLayout->addWidget(btn, 0, Qt::AlignRight);
    mainLayout->addLayout(botLayout,1);

    dlg.exec();
}
