#pragma once

#include "CList.h"

DEFINE_HANDLE(HandlerType::List, CList);

void CList::Do(int i, string* packet_type, ofstream& fout, MACRO* macro, vector<node_struct>* node_vec, vector<type_struct>* class_var, vector<list_struct>* list_var) {
	string class_name, var_name;
	type_struct tmp;
	list_struct list_content;

	if (class_var->size() != 0) {
		tmp.type = "open";
		tmp.name = "openBrace";
		tmp.parentClass = node_vec->at(i).parentClass;
		tmp.depth = node_vec->at(i).depth;
		class_var->push_back(tmp);
	}


	for (int j = 0; j < node_vec->at(i).var_vec.size(); j++)
	{
		if (node_vec->at(i).var_vec.at(j).attrib == "class")
			class_name = node_vec->at(i).var_vec.at(j).value;
		else if (node_vec->at(i).var_vec.at(j).attrib == "name")
			var_name = node_vec->at(i).var_vec.at(j).value;
	}
	fout << macro->makeClass(class_name).c_str();



	for (int j = 0; j < node_vec->at(i).depth; j++) fout << macro->makeTab().c_str();
	fout << macro->makePublic().c_str();

	list_content.className = class_name;
	list_content.name = var_name;
	list_content.depth = node_vec->at(i).depth;
	list_content.parent = node_vec->at(i).parent;
	list_content.parentClass = node_vec->at(i).parentClass;
	list_var->push_back(list_content);
}