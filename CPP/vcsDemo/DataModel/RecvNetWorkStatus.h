#pragma once

#include <QObject>
#include "CJsonObject/JsonUtil.h"
class RecvNetWorkStatus : public QObject
{
	Q_OBJECT
public:

	const int& audio() { return _audio; }
	void set_audio(const int& audio) {
		_audio = audio;
	}

	const int& video() { return _video; }
	void set_video(const int& video) {
		_video = video;
	}

	const int& comp() { return _comp; }
	void set_comp(const int& comp) {
		_comp = comp;
	}

	const int& losf() { return _losf; }
	void set_losf(const int& losf) {
		_losf = losf;
	}

	const double& lr1() { return _lr1; }
	void set_lr1(const double& lr1) {
		_lr1 = lr1;
	}

	const double& lr2() { return _lr2; }
	void set_lr2(const double& lr2) {
		_lr2 = lr2;
	}

	const int& recv() { return _recv; }
	void set_recv(const int& recv) {
		_recv = recv;
	}

	const QString& sdkno() { return _sdkno; }
	void set_sdkno(const QString& sdkno) {
		_sdkno = sdkno;
	}

	void Load(QJsonObject json);

private:
	int _audio;
	int _video;
	int _comp;
	int _losf;
	double _lr1;
	double _lr2;
	int _recv;
	QString _sdkno;
};
