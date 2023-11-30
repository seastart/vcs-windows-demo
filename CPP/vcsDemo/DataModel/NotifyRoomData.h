#ifndef NOTIFYROOMDATA_H_
#define NOTIFYROOMDATA_H_

#include "CJsonObject/JsonUtil.h"

class NotifyRoomData {
public:
	NotifyRoomData();
	~NotifyRoomData() {}

	const int& astate() { return _astate; }
	void set_astate(const int& astate) {
		_astate = astate;
	}

	const QString& id() { return _id; }
	void set_id(const QString& id) {
		_id = id;
	}

	const QString& sdk_no() { return _sdk_no; }
	void set_sdk_no(const QString& sdk_no) {
		_sdk_no = sdk_no;
	}

	const QString& sharing_acc_id() { return _sharing_acc_id; }
	void set_sharing_acc_id(const QString& sharing_acc_id) {
		_sharing_acc_id = sharing_acc_id;
	}

	const QString& sharing_pic_url() { return _sharing_pic_url; }
	void set_sharing_pic_url(const QString& sharing_pic_url) {
		_sharing_pic_url = sharing_pic_url;
	}

	const QString& sharing_sdkno() { return _sharing_sdkno; }
	void set_sharing_sdkno(const QString& sharing_sdkno) {
		_sharing_sdkno = sharing_sdkno;
	}

	const int& sharing_type() { return _sharing_type; }
	void set_sharing_type(const int& sharing_type) {
		_sharing_type = sharing_type;
	}

	const int& state() { return _state; }
	void set_state(const int& state) {
		_state = state;
	}

	const int& type() { return _type; }
	void set_type(const int& type) {
		_type = type;
	}

	const int& vstate() { return _vstate; }
	void set_vstate(const int& vstate) {
		_vstate = vstate;
	}

	const bool& wb() { return _wb; }
	void set_wb(const bool& wb) {
		_wb = wb;
	}

	const QString& sharing_stream_id() { return _sharing_stream_id; }
	void set_sharing_stream_id(const int& sharing_stream_id) {
		_sharing_stream_id = sharing_stream_id;
	}

	const bool& watermark() { return _watermark; }
	void set_watermark(const bool& watermark) {
		_watermark = watermark;
	}

	const bool& locked() { return _locked; }
	void set_locked(const bool& locked) {
		_locked = locked;
	}

	const QString& sharing_relative_pic_url() { return _sharing_relative_pic_url; }
	void set_sharing_relative_pic_url(const QString& s) {
		_sharing_relative_pic_url = s;
	}

    const int& relieve_astate() { return _relieve_astate; }
    void set_relieve_astate(const int& s) {
        _relieve_astate = s;
    }


	void Load(QJsonObject obj);

private:
	int _astate;
	QString _id;
	QString _sdk_no;
	QString _sharing_acc_id;
	QString _sharing_pic_url;
	QString _sharing_relative_pic_url;
	QString _sharing_sdkno;
	int _sharing_type;
	int _state;
	int _type;
	int _vstate;
	bool _wb;
	bool _watermark;
	bool _locked;
    int _relieve_astate;
	QString _sharing_stream_id;
};
#endif // NOTIFYROOMDATA_H_
