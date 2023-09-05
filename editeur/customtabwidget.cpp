#include "customtabwidget.h"
#include <QVBoxLayout>

CustomTabWidget::CustomTabWidget(QWidget *parent, int initialLine, int initialColumn) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Ajoutez des étiquettes pour les informations de position du curseur
    lineLabel = new QLabel(QString("Ligne : %1").arg(initialLine), this);
    columnLabel = new QLabel(QString("Colonne : %1").arg(initialColumn), this);

    // Ajoutez le QPlainTextEdit pour le texte
    textEdit = new QPlainTextEdit(this);

    // Initialisez la position de curseur propre à cet onglet
    currentLine = initialLine;
    currentColumn = initialColumn;

    // Ajoutez les étiquettes et le QPlainTextEdit au layout
    layout->addWidget(lineLabel);
    layout->addWidget(columnLabel);
    layout->addWidget(textEdit);
}



void CustomTabWidget::updateCursorPosition(int line, int column)
{
    currentLine = line;
    currentColumn = column;

    lineLabel->setText(QString("Ligne : %1").arg(currentLine));
    columnLabel->setText(QString("Colonne : %1").arg(currentColumn));
}

