#include "titlebarbutton.hpp"

TitleBarButton::TitleBarButton(PantherDecoration::ButtonType type, QWidget *parent)
    : QLabel(parent)
    , _type(type)
{
    setMouseTracking(true);

    switch (type)
    {
        case PantherDecoration::CloseButton:
            setPixmap(QPixmap(":/decorations/panther/images/close-btn.png"));
            setToolTip(trUtf8("Close"));
            break;
        case PantherDecoration::MinimizeButton:
            setPixmap(QPixmap(":/decorations/panther/images/minimize-btn.png"));
            setToolTip(trUtf8("Minimize"));
            break;
        case PantherDecoration::MaximizeButton:
            setPixmap(QPixmap(":/decorations/panther/images/maximize-btn.png"));
            setToolTip(trUtf8("Maximize"));
            break;
    }
}

void TitleBarButton::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}
