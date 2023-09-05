#include "customtabwidget.h"
#include "QVBoxLayout"


CustomTabWidget::CustomTabWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Ajoutez des étiquettes pour les informations de position du curseur
    lineLabel = new QLabel("Ligne : 1", this);
    columnLabel = new QLabel("Colonne : 1", this);

    // Ajoutez le QPlainTextEdit pour le texte
    textEdit = new QPlainTextEdit(this);

    // Ajoutez les étiquettes et le QPlainTextEdit au layout
    layout->addWidget(lineLabel);
    layout->addWidget(columnLabel);
    layout->addWidget(textEdit);

    // Le reste de votre code...
}
