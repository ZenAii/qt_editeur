#ifndef CUSTOMTABBAR_H
#define CUSTOMTABBAR_H


#include <QTabBar>

class CustomTabBar : public QTabBar
{
    Q_OBJECT

protected:
    void tabLayoutChange() override;
};
