#include "Markup.h"
#include "Macro.h"
#include <fstream>
#include <vector>
#include <map>

enum { Packet, Int, Long, Bool, String, List };

typedef struct var_struct {		// 각 노드에 대한 속성 구조체
	string attrib;
	string value;
}var_struct;

typedef struct node_struct {	// node 정보에 대한 구조체
	string type;
	int depth;
	vector<var_struct> var_vec;	
}node_struct;

vector<node_struct> node_vec;

void recursive(CMarkup xml, int depth)	// xml을 돌면서 node에 대한 정보를 저장하는 재귀함수
{	
	int findElemIndex = 0;
	while (xml.FindElem())
	{		
		node_struct node;
		int index = 0;
		node.type = xml.GetTagName().c_str();
		node.depth = depth;
		
		while (true)
		{
			var_struct var;
			var.attrib = xml.GetAttribName(index).c_str();
			if (var.attrib == "")
				break;
			var.value = xml.GetAttrib(var.attrib).c_str();			
			node.var_vec.push_back(var);
			index++;
		}

		node_vec.push_back(node);
		
		if (xml.IntoElem())
		{
			recursive(xml, depth+1);
			xml.OutOfElem();
		}
	}
}

int main()
{
	macro::MACRO *macro = macro::MACRO::getInstance();	
	ofstream fout;
	CMarkup xml;
	int depth = 0, prev_depth = 0;
	bool flag = true;
	string var_name, class_name, from, packet_type, prev_type;

	
	fout.open("PDL.h", ios::out);
	xml.Load("PDL.xml");
	xml.FindElem("PDL");
	printf("%s %s %s\n\n", xml.GetTagName().c_str(), xml.GetAttribName(0).c_str(), xml.GetAttrib(xml.GetAttribName(0)).c_str());
	for (int i = 0; i < depth; i++) fout << macro->makeTab();
	fout << macro->makeNameSpace(xml.GetTagName().c_str());
	xml.IntoElem(); depth++;

	recursive(xml, depth);
	
	// 여기까지가 node_vec에 pdl.xml의 모든 노드에 대한 정보를 담음

	map<string, int> type_num;
	type_num.insert(pair<string, int>(string("Packet"), 0));
	type_num.insert(pair<string, int>(string("Int"), 1));
	type_num.insert(pair<string, int>(string("Long"), 2));
	type_num.insert(pair<string, int>(string("Bool"), 3));
	type_num.insert(pair<string, int>(string("String"), 4));
	type_num.insert(pair<string, int>(string("List"), 5));

	for (int i = 0; i < node_vec.size(); i++)
	{
		if (prev_depth - node_vec.at(i).depth >= 1 || (prev_type == "Packet" && node_vec.at(i).type == "Packet") || (prev_type == "List" && node_vec.at(i).type == "List")) {
			for (int j = prev_depth-1; j >= node_vec.at(i).depth; j--) {
				for (int k = 0; k < j; k++) fout << macro->makeTab();
				fout << macro->makeClassCloseBrace();
			}
		}
		prev_depth = node_vec.at(i).depth;
		prev_type = node_vec.at(i).type;

		for (int j = 0; j < node_vec.at(i).depth; j++) fout << macro->makeTab();
		
		switch (type_num[node_vec.at(i).type])
		{
		case Packet :
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "name")
					class_name = node_vec.at(i).var_vec.at(j).value;
				else if (node_vec.at(i).var_vec.at(j).attrib == "from")
					from = node_vec.at(i).var_vec.at(j).value;
			}
			if (from == "Client")
			{
				class_name += "_READ";
				packet_type = "read";
			}			
			else if (from == "Server")
			{
				class_name += "_WRITE";
				packet_type = "write";
			}
			else
			{
				class_name += "_BOTH";
				packet_type = "both";
			}
			fout << macro->makeClass(class_name);
			break;
		case Int :
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "name")
					var_name = node_vec.at(i).var_vec.at(j).value;
			}
			fout << macro->makeVariable("int", var_name);
			break;
		case Long :
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "name")
					var_name = node_vec.at(i).var_vec.at(j).value;
			}
			fout << macro->makeVariable("long", var_name);
			break;
		case Bool :
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "name")
					var_name = node_vec.at(i).var_vec.at(j).value;
			}
			fout << macro->makeVariable("bool", var_name);
			break;
		case String :
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "name")
					var_name = node_vec.at(i).var_vec.at(j).value;
			}
			fout << macro->makeVariable("string", var_name, "\"\"");
			break;
		case List :
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "class")
					class_name = node_vec.at(i).var_vec.at(j).value;
				else if (node_vec.at(i).var_vec.at(j).attrib == "name")
					var_name = node_vec.at(i).var_vec.at(j).value;
			}
			fout << macro->makeClass(class_name);
			break;
		}
		
	}
	
	for (int i = prev_depth - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) fout << macro->makeTab();
		fout << macro->makeClassCloseBrace();
	}
	
	
	fout << macro->makeCloseBrace();
	fout.close();
}
