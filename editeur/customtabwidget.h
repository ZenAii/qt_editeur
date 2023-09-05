#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLabel>

class CustomTabWidget : public QWidget
{
    Q_OBJECT

public:
    CustomTabWidget(QWidget *parent = nullptr);

private:
    QPlainTextEdit *textEdit;
    QLabel *lineLabel;
    QLabel *columnLabel;
};

#endif // CUSTOMTABWIDGET_H
