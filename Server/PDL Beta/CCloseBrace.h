#pragma once

#include "HandlerBase.h"

class CCloseBrace : HandlerBase {
public:
	REGIST_HANDLE(HandlerType::CloseBrace, CCloseBrace);
	virtual void Do(int i, string* packet_type, ofstream& fout, MACRO* macro, vector<node_struct>* node_vec, vector<type_struct>* class_var, vector<list_struct>* list_var);
};