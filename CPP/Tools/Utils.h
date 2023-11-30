#pragma once

#include <qstring.h>
#include <QFile>
#include <QDir>
#include <functional>
#include <QNetworkInterface>

class Utils
{
public:
	static void HmacSha1(QString& result, QByteArray key, QByteArray baseString);

    static void SaveFile(QString FilePath, const char* data);
    static QString LoadFile(QString FilePath);
	static void Split(std::vector<std::string>& result, std::string str, std::string pattern);

	static std::string StringJoin(std::vector<std::string> result, std::string str);
	static std::string StringJoin(std::vector<int> result, std::string str);
	static int BinaryCount(int i);
	static void MaskToTrack(std::vector<int>& result, int mask);
	static int TrackToMask(const std::vector<int>& trackId);
	static QWidget* GetTopWidget(QWidget* self);

	static QString GetMac();

#ifdef Q_OS_WIN
	static bool GetVisualSystem();
#endif
	static long long GetRandDataID();

	static QStringList GetFileList(QString s);
};
