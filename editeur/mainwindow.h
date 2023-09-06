#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void fileLoad(const QString &fileName);

private slots: void fileOpen();
private slots: void fileSave();
private slots: void updateCursorPosition();
private slots: void showSearchDialog();
private slots: void highlightText(const QString &searchText);
private slots: void addNewTab();
private slots: void closeLastTab();
private slots: void createNewEditor();
private slots: void closeEvent(QCloseEvent *event);
private slots: void copyText();
private slots: void cutText();
private slots: void pasteText();
private slots: void undoText();




private:
    int currentLine = 1;
    int currentColumn = 1; // Ajoutez ces membres
    Ui::MainWindow *ui;

    bool fileModified = false;
    bool isFileModified = false;
    QString currentFileName;





    QWidget *cloneTabContent();
    QMap<int, QString> tabFileNames;




};

#endif // MAINWINDOW_H
