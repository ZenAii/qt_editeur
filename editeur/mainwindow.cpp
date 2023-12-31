#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QTextStream"
#include "QFileDialog"
#include <QTextCursor>
#include <QTextBlock>
#include <QInputDialog>
#include "customtabwidget.h"
#include "closabletabcontent.h"







MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::fileOpen);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::fileSave);
    connect(ui->textEdit, &QPlainTextEdit::cursorPositionChanged, this, &MainWindow::updateCursorPosition);
    connect(ui->actionFind, &QAction::triggered, this, &MainWindow::showSearchDialog);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addNewTab()));
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::closeLastTab);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::createNewEditor);
    connect(ui->actionCopy, &QAction::triggered, ui->textEdit, &QPlainTextEdit::copy);
    connect(ui->actionCut, &QAction::triggered, ui->textEdit, &QPlainTextEdit::cut);
    connect(ui->actionPaste, &QAction::triggered, ui->textEdit, &QPlainTextEdit::paste);
    connect(ui->actionUndo, &QAction::triggered, ui->textEdit, &QPlainTextEdit::undo);







}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        fileLoad(fileName); // Appelez la fonction fileLoad avec le nom de fichier sélectionné
         currentFileName = fileName;
}

void MainWindow::fileLoad(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("Cannot open file %1;\n%2").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setPlainText(text);
    statusBar()->showMessage(tr("File loaded"), 1000);
    fileModified = false;

    // Créez un nouvel onglet avec le widget personnalisé et le nom de fichier
    CustomTabWidget *newTabWidget = new CustomTabWidget(this, text, fileName);

    // Ajoutez le nouvel onglet au QTabWidget
    int newTabIndex = ui->tabWidget->addTab(newTabWidget, fileName);

    // Stockez le nom du fichier associé à cet onglet
    tabFileNames[newTabIndex] = fileName;

    // Assurez-vous que le nouvel onglet est activé
    ui->tabWidget->setCurrentIndex(newTabIndex);

    isFileModified = false;
    this->setWindowModified(false);
}


void MainWindow::fileSave()
{
    QString fileName;

    // Si currentFileName est vide, demandez à l'utilisateur de spécifier un nom de fichier
    if (currentFileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this);
    } else {
        // Utilisez currentFileName comme nom de fichier par défaut
        fileName = currentFileName;
    }

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);
            QString text = ui->textEdit->toPlainText();
            out << text;
            file.close();
            statusBar()->showMessage(tr("File saved"), 1000);
            fileModified = false;
            isFileModified = false;
            this->setWindowModified(false);

            // Mettez à jour le nom de l'onglet en supprimant l'astérisque (*)
            int currentIndex = ui->tabWidget->currentIndex();
            if (currentIndex >= 0) {
                QString tabText = ui->tabWidget->tabText(currentIndex);
                if (tabText.endsWith(" *")) {
                    tabText = tabText.left(tabText.length() - 2);
                }

                // Mettez à jour le texte de l'onglet avec le nouveau nom de fichier
                ui->tabWidget->setTabText(currentIndex, QFileInfo(fileName).fileName());

                // Mettez à jour currentFileName avec le nom de fichier réellement utilisé
                currentFileName = fileName;
            }
        } else {
            QMessageBox::warning(this, tr("Warning"),
                                 tr("Cannot save file %1;\n%2").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        }
    }
}






void MainWindow::updateCursorPosition()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    int position = cursor.position();
    int line, column;
    QTextBlock block = ui->textEdit->document()->findBlock(position);
    line = block.blockNumber() + 1;
    column = position - block.position() + 1;

    currentLine = line;
    currentColumn = column;

    QString lineLabel;
    if (currentLine > 1) {
        lineLabel = QString("Lignes : %1").arg(currentLine);
    } else {
        lineLabel = QString("Ligne : %1").arg(currentLine);
    }

    QString columnLabel;
    if (currentColumn > 1) {
        columnLabel = QString("Colonnes : %1").arg(currentColumn);
    } else {
        columnLabel = QString("Colonne : %1").arg(currentColumn);
    }

    ui->lineLabel->setText(lineLabel);
    ui->columnLabel->setText(columnLabel);
    fileModified = true;
    isFileModified = true;
    this->setWindowModified(true); // Indiquez que la fenêtre est modifiée

    // Mettez à jour le nom de l'onglet avec l'astérisque (*)
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex >= 0) {
        QString tabText = ui->tabWidget->tabText(currentIndex);
        if (!tabText.endsWith(" *")) {
            ui->tabWidget->setTabText(currentIndex, tabText + " *");
        }
    }
}

void MainWindow::showSearchDialog()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Recherche de texte"), tr("Entrez le texte à rechercher :"), QLineEdit::Normal, QString(), &ok);

    if (ok && !searchText.isEmpty()) {
        QString textToSearch = ui->textEdit->toPlainText(); // Obtenez le texte du QTextEdit
        int index = textToSearch.indexOf(searchText, 0, Qt::CaseInsensitive); // Recherche insensible à la casse

        if (index != -1) {
            // Le texte a été trouvé, faites quelque chose avec l'index
        } else {
            // Le texte n'a pas été trouvé, affichez un message
            QMessageBox::information(this, tr("Recherche de texte"), tr("Texte non trouvé."));
        }
        highlightText(searchText);
    }
}


void MainWindow::highlightText(const QString &searchText)
{
    QTextDocument *document = ui->textEdit->document();
    QTextCursor cursor(document);

    QTextCharFormat format;
    format.setBackground(Qt::yellow); // Couleur de surlignage

    QTextCursor highlightCursor(document);
    QTextCursor clearCursor(document); // Ajout d'un nouveau curseur pour effacer la surbrillance précédente

    // Effacez la surbrillance précédente
    clearCursor.select(QTextCursor::Document);
    clearCursor.setCharFormat(QTextCharFormat());
    ui->textEdit->setTextCursor(clearCursor);

    while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
        highlightCursor = document->find(searchText, highlightCursor, QTextDocument::FindWholeWords);

        if (!highlightCursor.isNull()) {
            highlightCursor.mergeCharFormat(format);
            cursor.setPosition(highlightCursor.position() + searchText.length());
            ui->textEdit->setTextCursor(cursor);
        }
    }
}



// Fonction pour cloner le modèle de contenu initial (contenu du premier onglet)
QWidget *MainWindow::cloneTabContent()
{
    // Clonez le contenu du premier onglet (widgets, disposition, etc.)
    QWidget *newTabContent = new QWidget();

    // Copiez les éléments du modèle de contenu initial ici.
    // Par exemple, copiez des lignes, des colonnes, des zones de texte, etc.

    return newTabContent;
}

void MainWindow::addNewTab()
{
    // Récupérez la position de curseur actuelle
    QTextCursor cursor = ui->textEdit->textCursor();
    int currentLine = cursor.blockNumber() + 1;
    int currentColumn = cursor.columnNumber() + 1;

    // Convertissez les entiers en chaînes de caractères
    QString lineString = QString::number(currentLine);
    QString columnString = QString::number(currentColumn);

    // Créez un nouvel onglet avec le widget personnalisé en utilisant les chaînes de caractères
    CustomTabWidget *newTabWidget = new CustomTabWidget(this, lineString, columnString);

    // Ajoutez le nouvel onglet au QTabWidget
    int newTabIndex = ui->tabWidget->addTab(newTabWidget, "Nouvel onglet");

    // Assurez-vous que le nouvel onglet est activé
    ui->tabWidget->setCurrentIndex(newTabIndex);
}


void MainWindow::closeLastTab()
{
    int tabCount = ui->tabWidget->count();
    if (tabCount > 0) {
        int lastIndex = tabCount - 1;
        ui->tabWidget->removeTab(lastIndex);
    }
}


void MainWindow::createNewEditor()
{
    // Créez un nouvel onglet avec le widget personnalisé
    CustomTabWidget *newTabWidget = new CustomTabWidget(this);

    // Ajoutez le nouvel onglet au QTabWidget
    int newTabIndex = ui->tabWidget->addTab(newTabWidget, "Nouvel éditeur");

    // Assurez-vous que le nouvel onglet est activé
    ui->tabWidget->setCurrentIndex(newTabIndex);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (fileModified) {
        QMessageBox::StandardButton result;
        result = QMessageBox::warning(this, tr("Application"),
                                      tr("Le document à été modifié.\nVoulez-vous Enregistrer les modifications ?"),
                                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (result == QMessageBox::Save) {
            fileSave();
        } else if (result == QMessageBox::Cancel) {
            event->ignore(); // Ignorez la fermeture de l'application
            return;
        }
    }

    event->accept(); // Acceptez la fermeture de l'application
}

void MainWindow::copyText()
{
    ui->textEdit->copy();
}

void MainWindow::cutText()
{
    ui->textEdit->cut();
}

void MainWindow::pasteText()
{
    ui->textEdit->paste();
}

void MainWindow::undoText()
{
    ui->textEdit->undo();
}












