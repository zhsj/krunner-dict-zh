#ifndef YOUDAO_H
#define YOUDAO_H

#include <QtNetwork>

class Youdao : public QObject
{
    Q_OBJECT
public:
    Youdao(QObject *parent = 0);
    QStringList result();
public slots:
    void query(const QString &word);
private slots:
    void queryCompleted(QNetworkReply *);
signals:
    void finished();
private:
    QNetworkAccessManager *m_manager;
    QJsonDocument m_result;
};

#endif /* YOUDAO_H */
