#pragma once

#include "Macro.h"

#define DEFINE_HANDLE( Type, TypeName ) \
	TypeName TypeName_Type; \

#define REGIST_HANDLE( Type, TypeName ) \
	TypeName() \
	{\
	eType = Type; \
	HandlerBase::pHandlerMap[Type] = this; \
	}

class HandlerBase
{
protected:
	HandlerType eType;
private:
	static bool isTypeValid(int eType);
public:
	static HandlerBase* find(int eType);
	virtual void Do(int i, string* packet_type, ofstream& fout, MACRO* macro, vector<node_struct>* node_vec, vector<type_struct>* class_var, vector<list_struct>* list_var) = 0;
	static HandlerBase* pHandlerMap[END];
};