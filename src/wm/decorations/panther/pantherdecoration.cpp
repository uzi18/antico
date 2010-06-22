#include "pantherdecoration.hpp"
#include "titlebar.hpp"
#include "titlebarbutton.hpp"
#include "client.hpp"

#include <QHBoxLayout>
#include <QPalette>
#include <QLabel>
#include <QPainter>
#include <QLinearGradient>
#include <QDebug>

PantherDecoration::PantherDecoration(Client *c)
    : Decoration(c)
{
    _titleBar = new TitleBar(this);
    _titleBar->setFixedHeight(borderSize().titleBarHeight());
    connect(_titleBar, SIGNAL(buttonClicked(PantherDecoration::ButtonType)),
            SLOT(buttonClicked(PantherDecoration::ButtonType)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(borderSize().left() - 2, // expand 2px
                               borderSize().top(),
                               borderSize().right() - 2, // expand 2px
                               borderSize().bottom());
    layout->addWidget(_titleBar);
    layout->addStretch();

    addButton(CloseButton);
    addButton(MinimizeButton);
    addButton(MaximizeButton);

    setLayout(layout);
}

BorderSize PantherDecoration::borderSize() const
{
    return BorderSize(1, 3, 3, 3, 22);
}

void PantherDecoration::setTitle(const QString &title)
{
    _titleBar->setTitle(title);
}

void PantherDecoration::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.setPen(QColor(162, 162, 162));

    // top-left to bottom-left
    painter.drawLine(QPoint(0, 0), QPoint(0, rect().height()));
    // bottom-left to bottom-right
    painter.drawLine(QPoint(0, rect().height() - 1), QPoint(rect().width(), rect().height() - 1));
    // bottom-right to top-right
    painter.drawLine(QPoint(rect().width() - 1, rect().height() - 1), QPoint(rect().width() - 1, 0));
    // top-right to top-left
    painter.drawLine(QPoint(rect().width() - 1, 0), QPoint(0, 0));
}

void PantherDecoration::addButton(PantherDecoration::ButtonType type)
{
    TitleBarButton *button = new TitleBarButton(type, this);
    button->resize(18, _titleBar->height());

    switch (type)
    {
        case CloseButton:
          button->move(2, 0);
          break;

        case MinimizeButton:
            button->move(22, 0);
            break;

        case MaximizeButton:
            button->move(42, 0);
            break;
    }
}

void PantherDecoration::buttonClicked(PantherDecoration::ButtonType button)
{
    switch (button)
    {
        case CloseButton:
            client()->close();
            break;

        case MinimizeButton:
            client()->minimize();
            break;

        case MaximizeButton:
            client()->maximize();
            break;
    }
}

