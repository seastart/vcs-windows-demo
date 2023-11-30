#include "HttpNetworkSync.h"
#include "HttpNetwork.h"
#include "DataModel/UserData.h"
#include <QDebug>
#include "../Tools/Utils.h"
HttpNetworkSync::HttpNetworkSync(QObject* parent)
	: QObject(parent)
{
}

HttpNetworkSync::~HttpNetworkSync()
{
}

QByteArray HttpNetworkSync::OnPost(QString url, QString signature, QMap<QString, QString> value, int Overtime)
{
	QNetworkAccessManager manager;

	QString postValue;

	QList<QString> vSort;
	auto it = value.begin();

	for (; it != value.end(); ++it) {
		bool Addin = false;
		for (int i = 0; i < vSort.length(); i++)
		{
			if (vSort[i].compare(it.key()) > 0)
			{
				Addin = true;
				vSort.insert(i, it.key());
				break;
			}
			else
			{
				continue;
			}
		}
		if (!Addin)
		{
			vSort.append(it.key());
		}
	}

	for (QString s : vSort)
	{
		QString msg = s + "=" + value[s];

		if (!postValue.isEmpty())
		{
			postValue += "&";
		}
		postValue.append(msg);

	}

	qDebug() << "postValue:" << postValue << ",postSignature:" << signature;

	QNetworkRequest request = CreateRequest(HttpNetwork::Get()->Host() + url, signature);
	QNetworkReply* reply = manager.post(request, QByteArray(postValue.toLocal8Bit(), postValue.size()));
	QByteArray responseData;
	QEventLoop eventLoop;
	QTimer timer;
	connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	QObject::connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
	timer.start(Overtime);
    eventLoop.exec();
    responseData = reply->readAll();
	return responseData;
}

QByteArray HttpNetworkSync::OnPost(QString url, QMap<QString, QString> value, int Overtime)
{
	QNetworkAccessManager manager;

	value.insert("appid", HttpNetwork::Get()->Appid());
	QString postValue;
	QString postSignature;

	QList<QString> vSort;
	auto it = value.begin();

	for (; it != value.end(); ++it) {
		bool Addin = false;
		for (int i = 0; i < vSort.length(); i++)
		{
			if (vSort[i].compare(it.key()) > 0)
			{
				Addin = true;
				vSort.insert(i, it.key());
				break;
			}
			else
			{
				continue;
			}
		}
		if (!Addin)
		{
			vSort.append(it.key());
		}
	}

	for (QString s : vSort)
	{
		QString msg = s + "=" + value[s];
		if (s != "appid")
		{
			if (!postValue.isEmpty())
			{
				postValue += "&";
			}
			postValue.append(msg);
		}
		if (!postSignature.isEmpty())
		{
			postSignature += "&";
		}
		postSignature.append(msg);
	}

	qDebug() << "postValue:" << postValue << ",postSignature:" << postSignature;

	QNetworkRequest request = CreateRequest(HttpNetwork::Get()->Host() + url, postSignature);
	QNetworkReply* reply = manager.post(request, QByteArray(postValue.toLocal8Bit(), postValue.size()));
	QByteArray responseData;
	QEventLoop eventLoop;
	QTimer timer;
	connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	QObject::connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
	timer.start(Overtime);
    eventLoop.exec();
    responseData = reply->readAll();
	return responseData;
}

QNetworkRequest HttpNetworkSync::CreateRequest(QString url, QString postSignature)
{
	QNetworkRequest request = QNetworkRequest(QUrl(url));

	QSslConfiguration config = request.sslConfiguration();
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1SslV3);
	request.setSslConfiguration(config);
	QString sig;
	Utils::HmacSha1(sig, HttpNetwork::Get()->Appkey().toUtf8(), postSignature.toUtf8());
	request.setRawHeader("vcs-signature", sig.toUtf8());

	request.setRawHeader("vcs-appid", HttpNetwork::Get()->Appid().toUtf8());
	request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

	request.setRawHeader("vcs-token", HttpNetwork::Get()->Token().toUtf8());

	return request;
}

QByteArray HttpNetworkSync::OnDownload(QString url, int Overtime)
{
	QNetworkAccessManager manager;
	QString s = "appid=" + HttpNetwork::Get()->Appid();
	QNetworkRequest request = CreateRequest(HttpNetwork::Get()->Host() + url, s);
	QNetworkReply* reply = manager.get(request);
	QByteArray responseData;
	QEventLoop eventLoop;
	QTimer timer;
	connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	QObject::connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
	timer.start(Overtime);
    eventLoop.exec();
	responseData = reply->readAll();
	return responseData;
}
