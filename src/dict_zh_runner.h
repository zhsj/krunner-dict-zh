#ifndef DICT_ZH_H
#define DICT_ZH_H

#include "youdao.h"

#include <KRunner/AbstractRunner>

class DictZhRunner : public Plasma::AbstractRunner
{
    Q_OBJECT
public:
    DictZhRunner( QObject *parent, const QVariantList& args );
    ~DictZhRunner();

    void match(Plasma::RunnerContext &context) Q_DECL_OVERRIDE;
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) Q_DECL_OVERRIDE;

private:
    QString m_triggerWord;
    Youdao *m_youdao;

signals:
    void startQuery(const QString &word);
};

#endif /* DICT_ZH_H */
