#include "CapsData.h"
#ifdef Q_OS_WIN
#include <vcs.h>
#include <windows.h>
#include <WinUser.h>
#include "Tools/Utils.h"
#endif

CapsData::CapsData() :
	_desktop(0)
{}

void CapsData::Load(QJsonObject obj)
{
	JsonUtil::GetValue(obj, "ctx", _ctx);

	JsonUtil::GetValue(obj, "desktop", _desktop);

	JsonUtil::GetValue(obj, "hwnd", _hwnd);

	JsonUtil::GetValue(obj, "rect", _rect);
	QStringList sl = _rect.split(",");
	if (sl.size() == 4)
	{
		_q_rect.setX(sl[0].toInt());
		_q_rect.setY(sl[1].toInt());
		_q_rect.setWidth(sl[2].toInt());
		_q_rect.setHeight(sl[3].toInt());
	}
	JsonUtil::GetValue(obj, "title", _title);
}
