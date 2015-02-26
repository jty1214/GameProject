#pragma once

#include "CList_Var.h"

DEFINE_HANDLE(HandlerType::List_Var, CList_Var);

void CList_Var::Do(int i, string* packet_type, ofstream& fout, MACRO* macro, vector<node_struct>* node_vec, vector<type_struct>* class_var, vector<list_struct>* list_var) {
	string var_name, type_name;
	for (int j = 0; j < node_vec->at(i).var_vec.size(); j++)
	{
		if (node_vec->at(i).var_vec.at(j).attrib == "name")
			var_name = node_vec->at(i).var_vec.at(j).value;
		else if (node_vec->at(i).var_vec.at(j).attrib == "type")
			type_name = node_vec->at(i).var_vec.at(j).value;
	}
	fout << macro->makeVariable(type_name, var_name).c_str();
}