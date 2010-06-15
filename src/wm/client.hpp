#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <QObject>
#include <QRect>

class Decoration;
union _XEvent;

class Client: public QObject
{
public:
    Client(Qt::HANDLE winId, QObject *parent);
    ~Client();

    bool x11EventFilter(_XEvent *e);

    // These methods are interesting if you want to create a custom decoration
    void move(const QPoint &p);
    void resize(const QSize &size);
    void minimize();
    void maximize();
    void close();

    inline Decoration *decoration() const { return _decoration; }

    inline QRect geometry() const { return _geometry; }

protected:
    friend class WindowManager;

    void map();

private:
    Qt::HANDLE _winId;
    Decoration *_decoration;
    QRect _geometry;
};

#endif
