#include "EnumDevice.h"
#include "Tools/Utils.h"
#include "RoomControl.h"
#include "CJsonObject/JsonUtil.h"

bool EnumDevice::Video(VideoDeviceList& devices)
{
	bool conflict = false;
    qDebug() << __func__;
	char* videoDevs = NULL;
	int size1 = 0;
	VCS_EnumVideoDevices2(&videoDevs, &size1);
    if (!size1)
	{
		return false;
	}
	qDebug() << __func__ << videoDevs;
	QString json = QString::fromLocal8Bit(videoDevs, size1);
	QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toStdString().c_str());
	QJsonObject obj = jsonDocument.object();

	devices.Load(obj);

	VCS_Freep((void**)&videoDevs);
    if (RoomControl::Get()->roomInfo.cameraName.isEmpty())
	{
		for (int i = 0; i < devices.GetDeviceSize(); i++)
		{
			VideoDevice vd = devices.GetDevice(i);
			if (vd.GetResolutionCount() > 0)
			{
				RoomControl::Get()->roomInfo.cameraName = vd.GetName();
				RoomControl::Get()->roomInfo.cameraResolution = 0;
				for (int j = 0; j < vd.GetResolutionCount(); j++)
				{
					Resolution r = vd.GetResolution(j);
                    if (r.GetWidth() == 640)
					{
						RoomControl::Get()->roomInfo.cameraResolution = j;
						return !conflict;
					}
				}
			}
		}
	}
	return !conflict;
}


void EnumDevice::Audio(DeviceList& devices)
{
    qDebug() << __func__;
	char* audioDevs = NULL;
	int size1 = 0;
    VCS_EnumAudioDevices2(&audioDevs, &size1);
	if (!size1)
	{
		return;
	}
	qDebug() << __func__ << audioDevs;
	QString json = QString::fromLocal8Bit(audioDevs, size1);
	QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toStdString().c_str());
	QJsonObject obj = jsonDocument.object();

	devices.Load(obj);

	VCS_Freep((void**)&audioDevs);
    if(RoomControl::Get()->roomInfo.microphoneName.isEmpty())
      {
          if(devices.GetDeviceSize() > 0)
          {
              DeviceBase vd = devices.GetDevice(0);
              RoomControl::Get()->roomInfo.microphoneName = vd.GetName();
          }
      }
}

void EnumDevice::Speaker(DeviceList& devices)
{
	qDebug() << __func__;
	char* speakerDevs = NULL;
	int size1 = 0;
	VCS_EnumSpeakerDevices2(&speakerDevs, &size1);
	if (!size1)
	{
		return;
    }
	qDebug() << __func__ << speakerDevs;
	QString json = QString::fromLocal8Bit(speakerDevs, size1);
	QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toStdString().c_str());
	QJsonObject obj = jsonDocument.object();


	devices.Load(obj);

	VCS_Freep((void**)&speakerDevs);
    if(RoomControl::Get()->roomInfo.speakerName.isEmpty())
    {
        if(devices.GetDeviceSize() > 0)
        {
            DeviceBase vd = devices.GetDevice(0);
            RoomControl::Get()->roomInfo.speakerName = vd.GetName();
        }
    }
}
