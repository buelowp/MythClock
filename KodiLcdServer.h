/*
 * Copyright (c) 2019 <copyright holder> <email>
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef KODILCDSERVER_H
#define KODILCDSERVER_H

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

#define ONE_SECOND  1000
#define ONE_MINUTE  (ONE_SECOND * 60)
#define PING_ID     1
#define PLAYER_ID   2

/**
 * @todo write docs
 */
class KodiLcdServer : QObject
{
    Q_OBJECT
public:
    KodiLcdServer(QObject *parent = 0);
    ~KodiLcdServer();
    
public slots:
    void kodiError(QAbstractSocket::SocketError socketError);
    void kodiConnected();
    void connectionClosed();
    void kodiResponse();
    void ping();
    void exec();
    void testForPlayback();
    
signals:
    void connectionError();
    void apiError();
    
private:
    QTimer *m_connectionTimer;
    QTimer *m_pingTimer;
    QTimer *m_metadataTimer;
    QTimer *m_mediaCheck;
    QTcpSocket *m_kodi;
    
    qint64 m_lastPing;
    bool m_connected;
};

#endif // KODILCDSERVER_H
