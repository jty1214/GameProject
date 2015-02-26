#pragma once

#include "HandlerBase.h"

class CList : HandlerBase {
public:
	REGIST_HANDLE(HandlerType::List, CList);
	virtual void Do(int i, string* packet_type, ofstream& fout, MACRO* macro, vector<node_struct>* node_vec, vector<type_struct>* class_var, vector<list_struct>* list_var);
};