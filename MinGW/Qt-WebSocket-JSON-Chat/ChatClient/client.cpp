#include "client.h"
#include <QInputDialog>

Client::Client(QObject *parent) : QObject(parent)
{
    clientSocket = new QWebSocket();
    connect(clientSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onReceiveMessage(QString)));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

/**
 * 连接到服务器的插座
 */
void Client::onDisconnected()
{
    clientSocket->deleteLater();
}

/**
 * 连接到服务器
 */
void Client::connectSocket(const QString& host, unsigned int port)
{
    if (clientSocket != NULL && clientSocket->isValid()) {
        return; // Necessary to check and close (or return) connection if it is open
    }

    _port = port;
    _host = host;

    QUrl qUrl;
    qUrl.setPort(_port);
    qUrl.setHost(_host);
    qUrl.setScheme("ws");

    clientSocket->open(qUrl);
}

/**
 * 发送用户名
 */
void Client::sendUsername(const QString& username)
{
    QJsonObject json;
    json.insert("username", username);

    QJsonDocument doc;
    doc.setObject(json);
    clientSocket->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}

/**
 * 发送文本消息
 */
void Client::sendMessage(const QString& message)
{
    QJsonObject json;
    json.insert("message", message);

    QJsonDocument doc;
    doc.setObject(json);
    clientSocket->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}

/**
 * 报文槽
 */
void Client::onReceiveMessage(QString message)
{
    // 交通中断
    QJsonDocument messageDocument = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject messageJson;
    messageJson = messageDocument.object();


    // 服务器请求用户名
    if ( messageJson.contains("request_username") ) {
        emit requestUsername();
    }
    // 服务器发送文本消息
    else if ( messageJson.contains("message") ) {
        QString messageText = messageJson["message"].toString();
        QString username = messageJson["username"].toString();
        emit receiveMessage(username, messageText);
    }
    else if ( messageJson.contains("userlist") ) {
        QJsonArray userlist = messageJson["userlist"].toArray();
        emit receiveUserlist(userlist);
    }
    else if ( messageJson.contains("service_message") ) {
        QString messageText = messageJson["service_message"].toString();
        emit receiveServiceMessage(messageText);
    }

}
