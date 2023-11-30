#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QByteArray>
#include <QMap>
class HttpNetworkSync : public QObject
{
	Q_OBJECT

public:
	HttpNetworkSync(QObject* parent);
	~HttpNetworkSync();

	static QByteArray OnDownload(QString url, int Overtime = 2000);
	static QByteArray OnPost(QString url, QString signature, QMap<QString, QString> value, int Overtime = 2000);
	static QByteArray OnPost(QString url, QMap<QString, QString> value, int Overtime = 2000);
	static QNetworkRequest CreateRequest(QString url, QString postSignature);
};
