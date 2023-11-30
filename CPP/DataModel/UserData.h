#ifndef USERDATA_H_
#define USERDATA_H_

#include "CJsonObject/JsonUtil.h"
#include "AccountInfo.h"
#include "DataModel/CorporationInfo.h"
#include "Reg.h"
class UserData
{
public:
	AccountInfo& account();
	QString token();
	CorporationInfo& corp();
	int corp_role();
	Reg& reg();

	void set_account(AccountInfo);
	void set_token(QString);
	void set_corp(CorporationInfo);
	void set_corp_role(int);
	void set_reg(Reg);

	void Load(QJsonObject obj);

	static void Save(QJsonObject obj);
	static UserData* Get();
private:
	AccountInfo _account;
	QString _token;
	CorporationInfo _corp;
	int _corp_role;
	Reg _reg;
	static UserData* _object;
};

#endif // USERDATA_H_
