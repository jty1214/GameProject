#pragma once

#include "CInt.h"

DEFINE_HANDLE(HandlerType::Int, CInt);

void CInt::Do(int i, string* packet_type, ofstream& fout, MACRO* macro, vector<node_struct>* node_vec, vector<type_struct>* class_var, vector<list_struct>* list_var) {
	string var_name;
	type_struct tmp;
	for (int j = 0; j < node_vec->at(i).var_vec.size(); j++)
	{
		if (node_vec->at(i).var_vec.at(j).attrib == "name")
		{
			var_name = node_vec->at(i).var_vec.at(j).value;
			tmp.type = "_int32"; tmp.name = var_name;
			tmp.parent = node_vec->at(i).parent;
			class_var->push_back(tmp);
		}
	}
	fout << macro->makeVariable("_int32", var_name).c_str();
}