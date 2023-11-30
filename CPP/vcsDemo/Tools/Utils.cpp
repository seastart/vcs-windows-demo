#include "Utils.h"
#include <QCryptographicHash>
#include <QWidget>

#include <QDir>
#include <QDebug>
#include <string>
#ifdef Q_OS_WIN
#include <windows.h>
#else
#include <math.h>
#endif

void Utils::HmacSha1(QString& result, QByteArray key, QByteArray baseString)
{
    int blockSize = 64;

    if (key.length() > blockSize) {
		key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
	}

    QByteArray innerPadding(blockSize, char(0x36));
    QByteArray outerPadding(blockSize, char(0x5c));


	for (int i = 0; i < key.length(); i++) {
        innerPadding[i] = innerPadding[i] ^ key.at(i);
        outerPadding[i] = outerPadding[i] ^ key.at(i);
	}

	QByteArray total = outerPadding;
	QByteArray part = innerPadding;
	part.append(baseString);
	total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
	QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
	result = hashed.toHex();
}

void Utils::Split(std::vector<std::string>& result, std::string str, std::string pattern)
{
	if (str.empty())
	{
		return;
	}

	std::string::size_type pos;
    str += pattern;
	std::string::size_type size = str.size();

	for (size_t i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
}

std::string Utils::StringJoin(std::vector<std::string> result, std::string str)
{
	std::string ret_s = "";
	for (size_t i = 0; i < result.size(); i++)
	{
		ret_s += result[i] + str;
	}
	return ret_s;
}

std::string Utils::StringJoin(std::vector<int> result, std::string str)
{
	std::string ret_s = "";
	for (size_t i = 0; i < result.size(); i++)
	{
		ret_s += std::to_string(result[i]) + str;
	}
	return ret_s;
}

int Utils::BinaryCount(int i)
{
	int j = 0;

	while (i)
	{
		j++;

		int a = i - 1;

		i = i & a;
	}
	return j;
}

void Utils::MaskToTrack(std::vector<int>& result, int mask)
{
	int track = log2(mask);

	if (BinaryCount(mask) == 1)
	{
		result.push_back(track);
	}
	else
	{
		int number = 1;

		for (size_t i = 0; i <= track; i++)
		{
			if ((mask & number) > 0)
			{
				result.push_back(i);
			}
			number = number << 1;
		}
	}
}

int Utils::TrackToMask(const std::vector<int>& trackId)
{
	int mask = 0;

	for (int item : trackId)
	{
		int mask_item = (int)pow(2, item);
		mask = mask | mask_item;
	}

	return mask;
}

QWidget* Utils::GetTopWidget(QWidget* self)
{
	while (self->parentWidget())
	{
		self = self->parentWidget();
	}

	return self;
}

QString Utils::GetMac()
{
    QString msc = "";
	auto interfaces = QNetworkInterface::allInterfaces();
	for (int i = 0; i < interfaces.length(); i++) {
        msc = interfaces[i].hardwareAddress();
		if (interfaces[i].isValid()
			&& (interfaces[i].flags() & QNetworkInterface::IsUp)
			&& (interfaces[i].flags() & QNetworkInterface::IsRunning)
			&& !(interfaces[i].flags() & QNetworkInterface::IsLoopBack))
		{
			return interfaces[i].hardwareAddress();
		}
	}
    return msc;
}
#ifdef Q_OS_WIN
DWORD __forceinline IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
{
	CONTEXT* ctx = ep->ContextRecord;
	ctx->Ebx = -1;
	ctx->Eip += 4;
	return EXCEPTION_CONTINUE_EXECUTION;
}
bool IsInsideVPC()
{
	bool rc = false;
	__try
	{
		_asm push ebx
        _asm mov ebx, 0
        _asm mov eax, 1
		_asm __emit 0Fh
		_asm __emit 3Fh
		_asm __emit 07h
		_asm __emit 0Bh
		_asm test ebx, ebx
		_asm setz[rc]
			_asm pop ebx
    }
	__except (IsInsideVPC_exceptionFilter(GetExceptionInformation()))
	{
	}

	return rc;
}
bool IsInsideVMWare()
{
	bool rc = true;

	__try
	{
		__asm
		{
			push edx
			push ecx
			push ebx
			mov eax, 'VMXh'
			mov ebx, 0
			mov ecx, 10
			mov edx, 'VX'
			in eax, dx
			cmp ebx, 'VMXh'
			setz[rc]
			pop ebx
			pop ecx
			pop edx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		rc = false;
	}

	return rc;
}
int CheckVPC()
{
	/*if (IsInsideVPC())
	MessageBox(NULL, "你在虚拟电脑Microsoft Virtual PC中!", "提示", MB_OK | MB_ICONINFORMATION);
	else if (IsInsideVMWare())
	MessageBox(NULL, "你在虚拟电脑VMWare中!", "提示", MB_OK | MB_ICONINFORMATION);
	else
	MessageBox(NULL, "你在真实的电脑中!", "提示", MB_OK | MB_ICONINFORMATION);*/

	if (IsInsideVPC())
	{
		return 1;
	}
	else if (IsInsideVMWare())
	{
		return 1;
	}
	else
	{
		return 0;
	}

	return 0;
}


bool Utils::GetVisualSystem()
{
	return CheckVPC();
}
#endif
long long Utils::GetRandDataID()
{
	QString data = "0123456789";
	QString Rand = "";
	for (int i = 0; i < 13; i++)
	{
		Rand += data.at(qrand() % data.size());
	}
	return Rand.toLongLong();
}


QStringList Utils::GetFileList(QString s)
{
	QStringList ls;
	QDir dir(s);
	dir.setFilter(QDir::Files);
	QFileInfoList list = dir.entryInfoList();
	bool bIsDir;
	int i = 0;
	for (int i = 0; i < list.size(); i++)
	{
		QFileInfo fileInfo = list.at(i);
		if (fileInfo.fileName() == "." | fileInfo.fileName() == "..")
		{
			continue;
		}

		ls << fileInfo.filePath();
	}
	return ls;
}


void Utils::SaveFile(QString FileName, const char* data)
{
    if (FileName.isEmpty() == false) {
        QFile file;
        file.setFileName(FileName);
        bool isOK = file.open(QIODevice::WriteOnly);
        if (isOK == true) {
            file.write(data);
        }
    }
}

QString Utils::LoadFile(QString FilePath)
{
    QString filePath = FilePath;
    QString array;
    if (filePath.isEmpty() == false) {
        QFile file(filePath);
        bool isOK = file.open(QIODevice::ReadOnly);

        if (isOK == true) {
            QTextStream in(&file);
            in.setCodec("UTF-8");
            array = in.readAll();
        }
        file.close();
    }
    return array;
}
