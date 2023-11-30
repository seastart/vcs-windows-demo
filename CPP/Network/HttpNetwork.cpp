#include "HttpNetwork.h"
#include "../Tools/Utils.h"
#include "../DataModel/UserData.h"


HttpNetwork* HttpNetwork::object = nullptr;

HttpNetwork::HttpNetwork()
{
    appid = "";
    appkey = "";
    passkey = "0a6430bcb7084269817813a06e905979";
	fileHost = "";
	host = "http://vcs.anyconf.cn:5000/vcs/";
	network = new QNetworkAccessManager(this);
	QObject::connect(network, SIGNAL(finished(QNetworkReply*)), this, SLOT(OnRequestComplete(QNetworkReply*)));
}

HttpNetwork* HttpNetwork::Get()
{
	if (HttpNetwork::object == nullptr) {
		HttpNetwork::object = new HttpNetwork();
	}
	return HttpNetwork::object;
}

void HttpNetwork::SetHost(QString inHost)
{
	if (inHost.size() < 10)
	{
		return;
	}

	host = inHost;
}

QString HttpNetwork::Host()
{
	return host;
}


const QString& HttpNetwork::Appid()
{
	return appid;
}

void HttpNetwork::SetAppid(QString id)
{
	this->appid = id;
}

void HttpNetwork::SetAppkey(QString id)
{
	this->appkey = id;
}

QString HttpNetwork::Appkey()
{
	return this->appkey;
}

void HttpNetwork::SetToken(QString token)
{
	this->token = token;
}
QString HttpNetwork::Token()
{
	return this->token;
}

void HttpNetwork::OnPost(
	const char* url,
	QMap<QString, QString>& value,
	std::function<void(QByteArray& byte)> function,
	bool haveHost)
{
	QString requestUrl;

	if (haveHost)
	{
		requestUrl = url;
	}
	else
	{
		requestUrl = Get()->Host() + url;
	}
	if (HttpNetwork::Get()->callMap.contains(requestUrl))
	{
		QString jsonNetError = QString::fromLocal8Bit("{\"code\":1714,\"msg\":\"操作被取消\"}");
		QByteArray byte = jsonNetError.toStdString().c_str();
		HttpNetwork::Get()->callMap[requestUrl](byte);
	}

	value.insert("appid", HttpNetwork::Get()->Appid());
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
		if (!postSignature.isEmpty())
		{
			postSignature += "&";
		}
		postSignature.append(msg);
	}
    qDebug()<<__func__<<url<<postSignature;
	QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	multiPart->setBoundary(QByteArray("WebKitFormBoundary"));
	for (auto it = value.begin(); it != value.end(); ++it) {
		if (it.key() == "appid")
		{
			continue;
		}
		QHttpPart valuePart;
		valuePart.setHeader(
			QNetworkRequest::ContentDispositionHeader,
			QVariant(QString("form-data; name=\"%1\"").arg(it.key())));

		valuePart.setBody(it.value().toUtf8());
		multiPart->append(valuePart);
	}



	QNetworkRequest request = Get()->CreateRequest(requestUrl, postSignature);
	request.setRawHeader("Content-Type", " multipart/form-data; boundary=WebKitFormBoundary");

	HttpNetwork::Get()->callMap[request.url().toString()] = function;

	QNetworkReply* reply = HttpNetwork::Get()->network->post(request, multiPart);
	multiPart->setParent(reply);
}

void HttpNetwork::OnUplodPost(
	const char* url,
	QMap<QString, QString>& value,
	std::function<void(QHttpMultiPart* part)> parameter,
	std::function<void(QByteArray& byte)> function,
	bool haveHost)
{
	std::string postValue;

	QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	multiPart->setBoundary(QByteArray("WebKitFormBoundary"));

	auto it = value.begin();

	for (; it != value.end(); ++it) {

		if (!it.value().size())
		{
			continue;
		}

		QHttpPart valuePart;

		valuePart.setHeader(
			QNetworkRequest::ContentDispositionHeader,
			QVariant(QString("form-data; name=\"%1\"").arg(it.key())));

		valuePart.setBody(it.value().toUtf8());

		multiPart->append(valuePart);
	}

	QString requestUrl;

	if (haveHost)
	{
		requestUrl = url;
	}
	else
	{
		requestUrl = Get()->Host() + url;
	}
	QNetworkRequest request = QNetworkRequest(QUrl(requestUrl));

	QSslConfiguration config = request.sslConfiguration();
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1SslV3);
	request.setSslConfiguration(config);

	request.setRawHeader("vcs-appid", Get()->Appid().toLocal8Bit());
	request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

	if (!Get()->Token().isEmpty())
	{
		request.setRawHeader("vcs-token", Get()->Token().toLocal8Bit());
	}

	request.setRawHeader("Content-Type", " multipart/form-data; boundary=WebKitFormBoundary");

	parameter(multiPart);

	HttpNetwork::Get()->callMap[request.url().toString()] = function;

	QNetworkReply* reply = HttpNetwork::Get()->network->post(request, multiPart);

	multiPart->setParent(reply);
}

void HttpNetwork::OnDownload(const char* url, std::function<void(QByteArray& byte)> function)
{
	QNetworkRequest request = QNetworkRequest(QUrl(url));

	QSslConfiguration config = request.sslConfiguration();
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1SslV3);
	request.setSslConfiguration(config);

	HttpNetwork::Get()->callMap[request.url().toString()] = function;

	HttpNetwork::Get()->network->get(request);
}

void HttpNetwork::ClearUrlPost(QString url)
{
	if (HttpNetwork::Get()->callMap.contains(url))
	{
		HttpNetwork::Get()->callMap.remove(url);
	}
}

QNetworkRequest HttpNetwork::CreateRequest(QString& urlString, QString signature)
{
	QNetworkRequest request = QNetworkRequest(QUrl(urlString));

	QSslConfiguration config = request.sslConfiguration();
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1SslV3);
	request.setSslConfiguration(config);

	QString sig;
	Utils::HmacSha1(sig, Get()->Appkey().toUtf8(), signature.toUtf8());
	request.setRawHeader("vcs-signature", sig.toUtf8());

	request.setRawHeader("vcs-appid", Get()->Appid().toUtf8());
	request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");


	if (!token.isEmpty())
	{
		request.setRawHeader("vcs-token", token.toLocal8Bit());
	}

	return request;
}

void HttpNetwork::OnRequestComplete(QNetworkReply* reply)
{
	QString key = reply->request().url().toString();
	if (!HttpNetwork::Get()->callMap.contains(key))
	{
		return;
	}

    QByteArray byte = reply->readAll();
	if (byte.isEmpty())
	{
		QString jsonNetError = QString::fromLocal8Bit("{\"code\":1713,\"msg\":\"没有连接上网络\"}");
		byte = jsonNetError.toStdString().c_str();
	}
	std::function<void(QByteArray& byte)> fun = HttpNetwork::Get()->callMap[key];

	if (fun)
	{
		fun(byte);
	}

	HttpNetwork::Get()->callMap.remove(key);
}
