#ifndef HTTPNETWORK_H
#define HTTPNETWORK_H

#include <QNetworkAccessManager>
#include <QObject>
#include <unordered_map>
#include <QHttpMultiPart>
#include <QNetworkReply>

class HttpNetwork : public QObject
{
	Q_OBJECT

public:
	HttpNetwork();

	static HttpNetwork* Get();

	void SetHost(QString inHost);

	QString Host();

	QString Appkey();

	const QString& Appid();

	const QString& PassKey() { return passkey; }
	const QString& FileHost() { return fileHost; }

	void SetFileHost(QString fh) { fileHost = fh; }
	void SetPassKey(QString key) { passkey = key; }

	void SetAppid(QString id);
	void SetAppkey(QString key);

	void SetToken(QString token);

	QString Token();

	static void OnPost(
		const char* url,
		QMap<QString, QString>& value,
		std::function<void(QByteArray& byte)> function,
		bool haveHost = false);

	static void OnUplodPost(
		const char* url,
		QMap<QString, QString>& value,
		std::function<void(QHttpMultiPart* part)> parameter,
		std::function<void(QByteArray& byte)> function,
		bool haveHost = false);

	static void OnDownload(
		const char* url,
		std::function<void(QByteArray& byte)> function);

	static void ClearUrlPost(QString url);
private slots:
	void OnRequestComplete(QNetworkReply* reply);

private:
	static HttpNetwork* object;
	QNetworkAccessManager* network;

    QString appid;
	QString host;

	QString fileHost;
	QString passkey;
	QString appkey;
	QString token;

	QNetworkRequest CreateRequest(QString& urlString, QString postSignature);

	QMap<QString, std::function<void(QByteArray& byte)>> callMap;
};

#endif // HTTPNETWORK_H
