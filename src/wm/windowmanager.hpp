#ifndef _WINDOWMANAGER_HPP
#define _WINDOWMANAGER_HPP

#include <QObject>
#include <QMap>

class Client;

union _XEvent; // avoid X11 include

class WindowManager: public QObject
{
public:
    WindowManager();

    void init();
    bool x11EventFilter(_XEvent *e);

    // Set the active client
    void setActiveClient(Client *client);

    bool compositeManagerIsRunning() const;

    static WindowManager *self();

private:
    // Event window
    Qt::HANDLE eventWindow(_XEvent *e) const;

    // Create client
    Client *createClient(Qt::HANDLE winId);
    // Find client by decoration window
    Client *findClientByDecorationWindow(Qt::HANDLE winId) const;
    // Find client by window
    inline Client *findClient(Qt::HANDLE winId) { return _clients.value(winId); }

private:
    QMap<Qt::HANDLE, Client *> _clients;
};

#endif
