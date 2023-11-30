#ifndef CAPSDATA_H_
#define CAPSDATA_H_

#include <QPainter>
#include "CJsonObject/JsonUtil.h"
class CapsData {
public:
	CapsData();
	~CapsData() {}

	const QString& ctx() { return _ctx; }
	void set_ctx(const QString& ctx) {
		_ctx = ctx;
	}

	const int& desktop() { return _desktop; }
	void set_desktop(const int& desktop) {
		_desktop = desktop;
	}

	const QString& hwnd() { return _hwnd; }
	void set_hwnd(const QString& hwnd) {
		_hwnd = hwnd;
	}

	const QString& rect() { return _rect; }
	void set_rect(const QString& rect) {
		_rect = rect;
	}

	const QString& title() { return _title; }
	void set_title(const QString& title) {
		_title = title;
	}

	const QRect& q_rect() { return _q_rect; }

	void Load(QJsonObject obj);
private:
	QString _ctx;
	int _desktop;
	QString _hwnd;
	QString _rect;
	QString _title;
	QPixmap _image;
	QRect _q_rect;
};
#ifdef Q_OS_WIN
#endif
#endif
