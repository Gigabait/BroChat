#ifndef QACESCHAT_H
#define QACESCHAT_H

#include "../core/qchatservice.h"

class QNetworkAccessManager;
class QWebSocket;

class QAcesChat: public QChatService
{
    Q_OBJECT
public:
    explicit                QAcesChat( QObject * parent = nullptr );
                            ~QAcesChat() override;

protected:
    void                    timerEvent( QTimerEvent * ) override;

private:
    void                    loadSettings();
    void                    loadChannelInfo();
    void                    loadLastMessage();

    void                    connectToWebSocket();

public slots:
    void                    connect() override;
    void                    disconnect() override;
    void                    reconnect() override;

private slots:
    void                    onChannelInfoLoaded();
    void                    onChannelInfoLoadError();

    void                    onWebSocketConnected();
    void                    onWebSocketError();

    void                    onTextMessageReceived( const QString & message );
private:
    QNetworkAccessManager * nam_;
    QWebSocket            * socket_ = {nullptr};
    QString                 channelName_;
    QString                 channelId_;

    int                     reconnectTimerId_ = {-1};
    int                     saveConnectionId_ = {-1};

    static const QString    SERVICE_USER_NAME;
    static const QString    SERVICE_NAME;

    static const int        RECONNECT_INTERVAL;    
    static const int        SAVE_CONNECTION_INTERVAL;
};

#endif // QACESCHAT_H
