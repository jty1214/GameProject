#pragma once

#include "CCloseBrace.h"

DEFINE_HANDLE(HandlerType::CloseBrace, CCloseBrace);

void CCloseBrace::Do(int i, string* packet_type, ofstream& fout, MACRO* macro, vector<node_struct>* node_vec, vector<type_struct>* class_var, vector<list_struct>* list_var) {
	fout << macro->makeCloseBrace().c_str();
}