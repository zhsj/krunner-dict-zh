#include "youdao.h"

#include <iostream>

Youdao::Youdao(QObject *parent)
    : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(queryCompleted(QNetworkReply*)));
}

void Youdao::query(const QString &word)
{
    QUrl url = QUrl("http://aidemo.youdao.com/trans");
    QUrlQuery data = QUrlQuery("from=Auto&to=Auto");
    data.addQueryItem("q", word);
    url.setQuery(data);
    QNetworkRequest request(url);
    m_manager->get(request);
}

void Youdao::queryCompleted(QNetworkReply* reply)
{
    m_result = QJsonDocument::fromJson(reply->readAll());
    reply->deleteLater();
    emit finished();
}

QStringList Youdao::result()
{
    QStringList results;
    if(m_result.isObject())
    {
        QJsonValue basic = m_result.object().value("basic");
        if(basic.isObject())
        {
            QJsonArray explains = basic.toObject().value("explains").toArray();
            foreach(QJsonValue i, explains)
            {
                results << i.toString();
            }
        }
    }
    return results;
}
