#pragma once

#include <vector>
#include <string>
#include <memory>
#include "CJsonObject/JsonUtil.h"

#define DEFAULTDEVICE QString::fromLocal8Bit("系统默认")

class DeviceBase
{
public:
	DeviceBase() { name = ""; def = false; }

	QString GetName() { return name; }
    QString GetDevId() { return devId; }
	void SetName(QString name) { this->name = name; }


	bool GetDef() { return def; }

	virtual bool Load(QJsonObject obj);
protected:
	QString name;
    QString devId;
	bool def;
};

class Resolution
{
public:
	void SetWidth(int iWidth) {
		m_iWidth = iWidth;
	}
	int GetWidth() {
		return m_iWidth;
	}

	void SetHeight(int iHeight) {
		m_iHeight = iHeight;
	}
	int GetHeight() {
		return m_iHeight;
	}


	void SetType(int t) {
		m_type = t;
	}
	int GetType() {
		return m_type;
	}

	void ResolutionLoad(QJsonObject obj);
private:
	int m_iWidth;
	int m_iHeight;
	int m_type;
};

class VideoDevice : public DeviceBase
{
public:
	Resolution GetResolution(size_t idx)
	{
		size_t i = idx;
        if (idx < 0 || idx >= resolutions.size())
		{
			i = resolutions.size() - 1;
		}
		return resolutions[i];
	}

	size_t GetResolutionCount()
	{
		return resolutions.size();
	}
public:
	bool Load(QJsonObject arr) override;
private:
	QList<Resolution> resolutions;
};


class VideoDeviceList
{
public:
	VideoDeviceList()
	{
		conflict = false;
		hasDevice = false;
	}

	VideoDevice GetDevice(int index) {
		if (devices.size() > index)
		{
			return devices[index];
		}
		return VideoDevice();
	}

	int GetDeviceSize()
	{
		return devices.size();
	}

	bool GetConflict() { return conflict; }

	bool HasVideoDevice() { return hasDevice; }

	bool DevContains(QString devName, VideoDevice& Res);

	void Load(QJsonObject obj);
private:
	QList<VideoDevice> devices;
	bool conflict;
	bool hasDevice;
};


class DeviceList
{
public:
	DeviceList()
	{
		conflict = true;
	}

	DeviceBase GetDevice(int index) {
		if (devices.size() > index)
		{
			return devices[index];
		}
		return DeviceBase();
	}

	int GetDeviceSize()
	{
		return devices.size();
	}

	bool DevContains(QString devName, DeviceBase& Res);

    void Load(QJsonObject obj,QString name = "");

	QString GetDevault();
private:
	QList<DeviceBase> devices;

	bool conflict;
};
