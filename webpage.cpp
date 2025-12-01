#include "webpage.h"
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>

WebPage::WebPage(QWebEngineProfile *profile, QObject *parent)
    : QWebEnginePage(profile, parent)
{
    setBackgroundColor(Qt::transparent);

    connect(this, &QWebEnginePage::windowCloseRequested, this, &WebPage::windowCloseRequested);
}

void WebPage::windowCloseRequested()
{
    qDebug() << "windowCloseRequested";
}

void WebPage::javaScriptConsoleMessage(WebPage::JavaScriptConsoleMessageLevel level,
                                       const QString &message,
                                       int lineId,
                                       const QString &sourceId)
{
//    QWebEnginePage::javaScriptConsoleMessage(level, message, lineId, sourceId);
    QString levelStr;
    switch (level) {
    case InfoMessageLevel:    levelStr = "INFO"; break;
    case WarningMessageLevel: levelStr = "WARNING"; break;
    case ErrorMessageLevel:   levelStr = "ERROR"; break;
    }

    if (level == ErrorMessageLevel) {
        qCritical().noquote() << QString("[JS %1] %2 (line %3, source %4)")
                                 .arg(levelStr, message)
                                 .arg(lineId)
                                 .arg(sourceId);
    } else if (level == WarningMessageLevel) {
        qWarning().noquote() << QString("[JS %1] %2 (line %3, source %4)")
                                 .arg(levelStr, message)
                                 .arg(lineId)
                                 .arg(sourceId);
    } else {
        qDebug().noquote() << QString("[JS %1] %2 (line %3, source %4)")
                              .arg(levelStr, message)
                              .arg(lineId)
                              .arg(sourceId);
    }
}
