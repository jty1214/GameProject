#pragma once

#include "CCloseClassBrace.h"

DEFINE_HANDLE(HandlerType::CloseClassBrace, CCloseClassBrace);

void CCloseClassBrace::Do(int i, string* packet_type, ofstream& fout, MACRO* macro, vector<node_struct>* node_vec, vector<type_struct>* class_var, vector<list_struct>* list_var) {
	type_struct tmp;
	if (node_vec->at(i).close == "Packet") {
		if (class_var->size() != 0)
		{
			// GetStreamLength & Serialize & Parsing Method 추가 부분
			// 해당 각 변수들은 class_var 벡터에 들어가있음
			if (*packet_type == "write" || *packet_type == "both")
			{
				fout << macro->makeGetStreamLength(node_vec->at(i).depth + 1, *class_var, *list_var).c_str();
				fout << macro->makeSerialize(node_vec->at(i).depth + 1, *class_var, *list_var).c_str();
			}
			if (*packet_type == "read" || *packet_type == "both")
			{
				fout << macro->makeParsing(node_vec->at(i).depth + 1, *class_var, *list_var).c_str();
			}
			class_var->clear();
			list_var->clear();
			for (int j = 0; j < node_vec->at(i).depth; j++) fout << macro->makeTab().c_str();

		}
	}
	else if (node_vec->at(i).close == "List") {
		tmp.type = "close";
		tmp.name = "closeBrace";
		tmp.parentClass = node_vec->at(i).parentClass;
		tmp.depth = node_vec->at(i).depth;
		class_var->push_back(tmp);
	}
	fout << macro->makeClassCloseBrace().c_str();
}