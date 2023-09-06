#include "closabletabcontent.h"
#include <QPushButton>

ClosableTabContent::ClosableTabContent(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *tabLayout = new QVBoxLayout(this);

    // Ajoutez le bouton de fermeture
    closeButton = new QPushButton("x");
    closeButton->setFixedSize(20, 20);
    closeButton->setStyleSheet("background-color: transparent; border: none;");
    tabLayout->addWidget(closeButton, Qt::AlignRight);
}
