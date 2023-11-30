#ifndef UPLOADDATA_H_
#define UPLOADDATA_H_


#include "CJsonObject/JsonUtil.h"
namespace UploadData {

	class Fileinfo {
	public:
		Fileinfo();
		~Fileinfo() {}

		const QString& id() { return _id; }
		void set_id(const QString& id) {
			_id = id;
		}

		const QString& name() { return _name; }
		void set_name(const QString& name) {
			_name = name;
		}

		const QString& url() { return _url; }
		void set_url(const QString& url) {
			_url = url;
		}

		const QString& account_id() { return _account_id; }
		void set_account_id(const QString& account_id) {
			_account_id = account_id;
		}

		const int& size() { return _size; }
		void set_size(const int& size) {
			_size = size;
		}

		const int& created_at() { return _created_at; }
		void set_created_at(const int& created_at) {
			_created_at = created_at;
		}

		const int& updated_at() { return _updated_at; }
		void set_updated_at(const int& updated_at) {
			_updated_at = updated_at;
		}

		const int& expire_at() { return _expire_at; }
		void set_expire_at(const int& expire_at) {
			_expire_at = expire_at;
		}

		const QString& path() { return _path; }
		void set_path(const QString& path) {
			_path = path;
		}

		const QString& key() { return _key; }
		void set_key(const QString& key) {
			_key = key;
		}
		void Load(QJsonObject json);

	private:
		QString _id;
		QString _name;
		QString _url;
		QString _account_id;
		int _size;
		int _created_at;
		int _updated_at;
		int _expire_at;
		QString _path;
		QString _key;
	}; // class Fileinfo

	class Token {
	public:
		Token();
		~Token() {}

		const QString& url() { return _url; }
		void set_url(const QString& url) {
			_url = url;
		}

		const QString& AWSAccessKeyId() { return _AWSAccessKeyId; }
		void set_AWSAccessKeyId(const QString& AWSAccessKeyId) {
			_AWSAccessKeyId = AWSAccessKeyId;
		}

		const QString& acl() { return _acl; }
		void set_acl(const QString& acl) {
			_acl = acl;
		}

		const int& success_action_status() { return _success_action_status; }
		void set_success_action_status(const int& success_action_status) {
			_success_action_status = success_action_status;
		}

		const QString& Policy() { return _Policy; }
		void set_Policy(const QString& Policy) {
			_Policy = Policy;
		}

		const QString& Signature() { return _Signature; }
		void set_Signature(const QString& Signature) {
			_Signature = Signature;
		}

		const QString& key() { return _key; }
		void set_key(const QString& key) {
			_key = key;
		}

		void Load(QJsonObject json);

	private:
		QString _url;
		QString _AWSAccessKeyId;
		QString _acl;
		int _success_action_status;
		QString _Policy;
		QString _Signature;
		QString _key;
	}; // class Token

	class Data {
	public:
		Data();
		~Data() {}

		Fileinfo& fileinfo() { return _fileinfo; }
		void set_fileinfo(const Fileinfo& fileinfo) {
			_fileinfo = fileinfo;
		}

		const bool& finished() { return _finished; }
		void set_finished(const bool& finished) {
			_finished = finished;
		}

		Token& token() { return _token; }
		void set_token(const Token& token) {
			_token = token;
		}

		void Load(QJsonObject json);

	private:
		Fileinfo _fileinfo;
		bool _finished;
		Token _token;
	}; // class Data

	class UploadData {
	public:
		UploadData();
		~UploadData() {}

		const int& code() { return _code; }
		void set_code(const int& code) {
			_code = code;
		}

		Data& data() { return _data; }
		void set_data(const Data& data) {
			_data = data;
		}

		void Load(QJsonObject obj);

	private:
		int _code;
		Data _data;
	}; // class UploadData

} // namespace UploadData
#endif // UPLOADDATA_H_
