#pragma once

#include "CPacket.h"

DEFINE_HANDLE(HandlerType::Packet, CPacket);

void CPacket::Do(int i, string* packet_type, ofstream& fout, MACRO* macro, vector<node_struct>* node_vec, vector<type_struct>* class_var, vector<list_struct>* list_var) {
	string class_name, from;
	for (int j = 0; j < node_vec->at(i).var_vec.size(); j++)
	{
		if (node_vec->at(i).var_vec.at(j).attrib == "class")
			class_name = node_vec->at(i).var_vec.at(j).value;
		else if (node_vec->at(i).var_vec.at(j).attrib == "from")
			from = node_vec->at(i).var_vec.at(j).value;
	}
	if (from == "Client")
	{
		class_name += "_READ";
		*packet_type = "read";
	}
	else if (from == "Server")
	{
		class_name += "_WRITE";
		*packet_type = "write";
	}
	else
	{
		class_name += "_BOTH";
		*packet_type = "both";
	}
	fout << macro->makeClass(class_name).c_str();

	for (int j = 0; j < node_vec->at(i).depth; j++) fout << macro->makeTab().c_str();
	fout << macro->makePublic().c_str();
}