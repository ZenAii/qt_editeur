#ifndef CLOSABLETABCONTENT_H
#define CLOSABLETABCONTENT_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class ClosableTabContent : public QWidget
{
    Q_OBJECT

public:
    ClosableTabContent(QWidget *parent = nullptr);
    QPushButton *closeButton;
};

#endif // CLOSABLETABCONTENT_H
