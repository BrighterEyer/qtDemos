#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    server = new QWebSocketServer("CharServer", QWebSocketServer::NonSecureMode);
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

Server::~Server()
{
    if (server->isListening()) {
        server->close();
    }
    server->deleteLater();
    server = NULL;
}

/**
 * 启动服务器
 * 发出错误信号
 */
void Server::Start(unsigned int port)
{
    if (!server->listen(QHostAddress::Any, port) )
    {
        emit errorOccured(server->errorString());
    }
}

/**
 * 从连接列表中删除客户端连接
 */
void Server::onDisconnect()
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client)
    {
        QString username = clients[client];
        clients.remove(client);
        client->deleteLater();

        // 发出信号
        emit userDisconnected(username);

        // 发送修改后的客户名单
        sendServiceMessage("用户 " + username + " 离开聊天室.");
        sendUserList();
    }
}


/**
 * 槽建立新的连接
 * 创建客户端插座
 * 记录客户插座槽
 * 添加克林特套接字到共享列表连接的用户插座，
 * 用户名暂时是空的
 * 发送用户名称查询
 */
void Server::onNewConnection()
{
    QWebSocket* client = server->nextPendingConnection();
    connect(client, SIGNAL(textMessageReceived(QString)), this, SLOT(onReceiveMessage(QString)));
    connect(client, SIGNAL(disconnected()), this, SLOT(onDisconnect()));

    clients.insert(client, "");

    sendRequestUsername(client);
}

/**
 * 发送服务消息给所有用户
 */
void Server::sendServiceMessage(const QString& message)
{
    QJsonObject ansewerJson;

    ansewerJson["service_message"] = message;

    QJsonDocument ansewerDocument;
    ansewerDocument.setObject(ansewerJson);

    QString messageAnswer = QString::fromUtf8(ansewerDocument.toJson(QJsonDocument::Compact));

    sendToAll(messageAnswer);
}

/**
 * 客户端消息槽
 */
void Server::onReceiveMessage(QString message)
{
    QWebSocket* client = qobject_cast<QWebSocket*>(sender());
    if (client == NULL)
    {
        return;
    }

    // 交通中断
    QJsonDocument messageDocument = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject messageJson;
    messageJson = messageDocument.object();

    // 用户登录
    if ( messageJson.contains("username") ) {
        QString username = messageJson.take("username").toString().toUpper();
        clients[client] = username;
        sendServiceMessage("Пользователь " + username + " вошел в чат.");
        sendUserList();
        emit userConnected(username);
    }
    // 用户发送文本消息
    else if ( messageJson.contains("message") ) {
        QJsonObject ansewerJson;

        ansewerJson["username"] = clients[client];
        ansewerJson["message"] = messageJson.take("message").toString();

        QJsonDocument ansewerDocument;
        ansewerDocument.setObject(ansewerJson);

        QString answerMessage = QString::fromUtf8(ansewerDocument.toJson(QJsonDocument::Compact));
        sendToAll(answerMessage);
    }
}

/**
 * 发送消息给所有的用户
 */
void Server::sendToAll(const QString& message)
{
    foreach ( QWebSocket* client, clients.keys() ) {
        client->sendTextMessage(message);
    }
}

/**
 * 发送更新的用户列表
 */
void Server::sendUserList()
{
    QJsonObject ansewerJson;
    QJsonArray userlist;

    foreach(QString username, clients) {
        userlist <<  username;
    }

    ansewerJson["userlist"] = userlist;

    QJsonDocument ansewerDocument;
    ansewerDocument.setObject(ansewerJson);

    QString message = QString::fromUtf8(ansewerDocument.toJson(QJsonDocument::Compact));

    sendToAll(message);
}

/**
 * 发送用户名称查询
 */
void Server::sendRequestUsername(QWebSocket* client)
{
    if (client->isValid()) {
        QJsonObject ansewerJson;
        ansewerJson["request_username"] = true;

        QJsonDocument ansewerDocument;
        ansewerDocument.setObject(ansewerJson);

        QString answerMessage = QString::fromUtf8(ansewerDocument.toJson(QJsonDocument::Compact));

        client->sendTextMessage(answerMessage);
    }
}

