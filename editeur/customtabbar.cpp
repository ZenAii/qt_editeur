#include "customtabbar.h"
#include <QStylePainter>
#include <QStyleOptionTab>

void CustomTabBar::tabLayoutChange()
{
    for (int tabIndex = 0; tabIndex < count(); ++tabIndex)
    {
        QRect tabRect = tabRect(tabIndex);

        // Ajoutez un bouton de fermeture à côté du titre de l'onglet
        QRect closeButtonRect(tabRect.right() - 16, tabRect.top(), 16, tabRect.height());
        setTabButton(tabIndex, QTabBar::RightSide, nullptr); // Supprimez tout bouton précédent
        setTabButton(tabIndex, QTabBar::RightSide, closeButtonRect, QIcon(":/icons/close.png"));
    }
}
