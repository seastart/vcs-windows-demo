#pragma once
#include <vcs.h>

#include "VideoDevice.h"

class EnumDevice
{
public:
	static bool Video(VideoDeviceList& devices);

	static void Audio(DeviceList& devices);

	static void Speaker(DeviceList& devices);
};
