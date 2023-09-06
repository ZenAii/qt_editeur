#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLabel>

class CustomTabWidget : public QWidget
{
    Q_OBJECT

public:
    CustomTabWidget(QWidget *parent = nullptr, const QString& text = "", const QString& fileName = "");

public slots:
    void updateCursorPosition(int line, int column);

private:
    QPlainTextEdit *textEdit;
    QLabel *lineLabel;
    QLabel *columnLabel;
    int currentLine;
    int currentColumn;
};

#endif // CUSTOMTABWIDGET_H
