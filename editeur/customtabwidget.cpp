#include "customtabwidget.h"
#include <QVBoxLayout>

CustomTabWidget::CustomTabWidget(QWidget *parent, const QString& text, const QString& fileName) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Ajoutez des étiquettes pour les informations de position du curseur
    lineLabel = new QLabel(QString("Ligne : %1").arg(1), this);
    columnLabel = new QLabel(QString("Colonne : %1").arg(1), this);

    // Ajoutez le QPlainTextEdit pour le texte
    textEdit = new QPlainTextEdit(this);

    // Ajoutez les étiquettes et le QPlainTextEdit au layout
    layout->addWidget(lineLabel);
    layout->addWidget(columnLabel);
    layout->addWidget(textEdit);

    // Initialisez la position de curseur propre à cet onglet
    currentLine = 1;
    currentColumn = 1;

    // Mettez à jour le texte du QPlainTextEdit avec le contenu de l'onglet
    textEdit->setPlainText(text);

    // Mettez à jour les étiquettes de position du curseur
    lineLabel->setText(QString("Ligne : %1").arg(currentLine));
    columnLabel->setText(QString("Colonne : %1").arg(currentColumn));
}

void CustomTabWidget::updateCursorPosition(int line, int column)
{
    currentLine = line;
    currentColumn = column;

    lineLabel->setText(QString("Ligne : %1").arg(currentLine));
    columnLabel->setText(QString("Colonne : %1").arg(currentColumn));
}
