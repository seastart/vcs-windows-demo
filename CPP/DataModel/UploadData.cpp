#include "UploadData.h"

namespace UploadData {

	Fileinfo::Fileinfo() :
		_size(0),
		_created_at(0),
		_updated_at(0),
		_expire_at(0)
	{}

	void Fileinfo::Load(QJsonObject obj) {
		if (!obj.isEmpty())
		{
			JsonUtil::GetValue(obj, QString::fromLocal8Bit("id"), _id);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("name"), _name);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("url"), _url);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("account_id"), _account_id);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("size"), _size);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("created_at"), _created_at);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("updated_at"), _updated_at);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("expire_at"), _expire_at);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("path"), _path);
			JsonUtil::GetValue(obj, QString::fromLocal8Bit("key"), _key);
		}
	}

	Token::Token() :
		_success_action_status(0)
	{}

	void Token::Load(QJsonObject obj) {
		if (!obj.isEmpty())
		{
			JsonUtil::GetValue(obj, QString::fromLocal8Bit("url"), _url);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("AWSAccessKeyId"), _AWSAccessKeyId);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("acl"), _acl);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("success_action_status"), _success_action_status);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("Policy"), _Policy);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("Signature"), _Signature);

			JsonUtil::GetValue(obj, QString::fromLocal8Bit("key"), _key);
		}
	}

	Data::Data() :
		_finished(false)
	{}

	void Data::Load(QJsonObject obj) {
		if (!obj.isEmpty())
		{
			JsonUtil::GetValue(obj, QString::fromLocal8Bit("finished"), _finished);

			_token.Load(obj.value(QString::fromLocal8Bit("token")).toObject());
			_fileinfo.Load(obj.value(QString::fromLocal8Bit("fileinfo")).toObject());
		}
	}

	UploadData::UploadData() :
		_code(0)
	{}

	void UploadData::Load(QJsonObject obj) {

		if (!obj.isEmpty())
		{
			JsonUtil::GetValue(obj, QString::fromLocal8Bit("code"), _code);

			_data.Load(obj.value(QString::fromLocal8Bit("data")).toObject());
		}
	}
} // namespace UploadData
