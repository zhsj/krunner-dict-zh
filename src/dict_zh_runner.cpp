#include "dict_zh_runner.h"

#include <KLocalizedString>

#include <QApplication>
#include <QClipboard>
#include <QMutex>
#include <QWaitCondition>

DictZhRunner::DictZhRunner(QObject *parent, const QVariantList &args):
    Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args);
    setSpeed(SlowSpeed);
    setPriority(HighestPriority);
    setObjectName(QLatin1String("Zh Dict"));
    setIgnoredTypes(Plasma::RunnerContext::Directory | Plasma::RunnerContext::File |
        Plasma::RunnerContext::NetworkLocation | Plasma::RunnerContext::Executable |
        Plasma::RunnerContext::ShellCommand);

    m_triggerWord = QString("zh");
    setSyntaxes(QList<Plasma::RunnerSyntax>() << Plasma::RunnerSyntax(
            Plasma::RunnerSyntax(QString("%1:q:").arg(m_triggerWord), i18n("Lookup Chinese meanings of :q:.")))
        );

    m_youdao = new Youdao(this);
    connect(this, SIGNAL(startQuery(const QString&)), m_youdao, SLOT(query(const QString&)));

}

DictZhRunner::~DictZhRunner()
{
}

void DictZhRunner::match(Plasma::RunnerContext &context)
{
    QString query = context.query();
    if (!query.startsWith(m_triggerWord, Qt::CaseInsensitive))
        return;
    query.remove(0, m_triggerWord.length());
    if (query.isEmpty())
        return;

    QEventLoop loop;
    emit(startQuery(query.trimmed()));
    connect(m_youdao, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QList<Plasma::QueryMatch> matches;
    foreach(const QString &result, m_youdao->result())
    {
        Plasma::QueryMatch match(this);
        match.setText(result);
        matches.append(match);
    }
    context.addMatches(matches);
}

void DictZhRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context);
    QApplication::clipboard()->setText(match.text());
}

K_EXPORT_PLASMA_RUNNER(krunner_dict_zh, DictZhRunner)

#include "dict_zh_runner.moc"
