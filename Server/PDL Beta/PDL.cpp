#include "Markup.h"
#include "Macro.h"

vector<node_struct> node_vec;

void recursive(CMarkup xml, int depth, string parent, string parentClass)	// xml을 돌면서 node에 대한 정보를 저장하는 재귀함수
{
	int findElemIndex = 0;
	while (xml.FindElem())
	{
		node_struct node;
		int index = 0;
		string str_parent, str_parentClass;
		node.type = xml.GetTagName().c_str();
		node.depth = depth;
		node.parent = parent;
		node.parentClass = parentClass;

		while (true)
		{
			var_struct var;
			var.attrib = xml.GetAttribName(index).c_str();
			if (var.attrib == "")
				break;
			var.value = xml.GetAttrib(var.attrib).c_str();
			if (var.attrib == "name") {
				str_parent = var.value;
			}
			if (var.attrib == "class") {
				str_parentClass = var.value;
			}
			node.var_vec.push_back(var);
			index++;
		}

		node_vec.push_back(node);

		if (xml.IntoElem())
		{
			recursive(xml, depth + 1, str_parent, str_parentClass);
			xml.OutOfElem();

			if (node.type == "Packet" || node.type == "List") {
				node_struct closeClassBrace;
				closeClassBrace.type = "CloseClassBrace";
				closeClassBrace.depth = depth;
				closeClassBrace.parent = parent;
				closeClassBrace.parentClass = parentClass;
				closeClassBrace.close = node.type;
				node_vec.push_back(closeClassBrace);
			}

			if (node.type == "List") {
				node_struct list;
				var_struct list_var, list_var2;
				list.type = "List_Var";
				list.depth = depth;
				list_var.attrib = "name";
				list_var.value = xml.GetAttrib("name").c_str();
				list.var_vec.push_back(list_var);
				list_var2.attrib = "type";
				list_var2.value += "vector<";
				list_var2.value += xml.GetAttrib("class").c_str();
				list_var2.value += ">";
				list.var_vec.push_back(list_var2);
				node_vec.push_back(list);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		printf("실행 예시 : PDL.exe 매개변수1(XML의 경로) 매개변수2(저장될 Header의 경로)\n");
		return 0;
	}
	macro::MACRO *macro = macro::MACRO::getInstance();
	ofstream fout;
	CMarkup xml;
	int depth = 0, prev_depth = 0, diff_depth;
	bool flag = true;
	string var_name, type_name, class_name, from, packet_type, prev_type;
	vector<type_struct> class_var;
	vector<list_struct> list_var;
	node_struct closeBrace;

	fout.open(argv[2], ios::out);
	xml.Load(argv[1]);
	//fout.open("PDL.h", ios::out);
	//xml.Load("PDL.xml");
	xml.FindElem("PDL");
	printf("%s %s %s\n\n", xml.GetTagName().c_str(), xml.GetAttribName(0).c_str(), xml.GetAttrib(xml.GetAttribName(0)).c_str());
	fout << macro->makeHeader("iostream");
	fout << macro->makeHeader("vector");
	fout << macro->makeString("using namespace std;\n");
	fout << macro->makeNameSpace(xml.GetTagName().c_str());
	xml.IntoElem(); depth++;

	recursive(xml, depth, "PDL", "ROOT");

	closeBrace.type = "CloseBrace";
	node_vec.push_back(closeBrace);

	// 여기까지가 node_vec에 pdl.xml의 모든 노드에 대한 정보를 담음

	map<string, int> type_num;
	type_num.insert(pair<string, int>(string("Packet"), 0));
	type_num.insert(pair<string, int>(string("Int"), 1));
	type_num.insert(pair<string, int>(string("Long"), 2));
	type_num.insert(pair<string, int>(string("Bool"), 3));
	type_num.insert(pair<string, int>(string("String"), 4));
	type_num.insert(pair<string, int>(string("List"), 5));
	type_num.insert(pair<string, int>(string("List_Var"), 6));
	type_num.insert(pair<string, int>(string("CloseClassBrace"), 7));
	type_num.insert(pair<string, int>(string("CloseBrace"), 8));

	for (int i = 0; i < node_vec.size(); i++)
	{
		for (int j = 0; j < node_vec.at(i).depth; j++) fout << macro->makeTab();
		type_struct tmp;
		list_struct list_content;
		tmp.depth = node_vec.at(i).depth;
		switch (type_num[node_vec.at(i).type])
		{
		case Packet:
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "class")
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

			for (int j = 0; j < node_vec.at(i).depth; j++) fout << macro->makeTab();
			fout << macro->makePublic();

			break;
		case Int:
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "name")
				{
					var_name = node_vec.at(i).var_vec.at(j).value;
					tmp.type = "_int32"; tmp.name = var_name;
					tmp.parent = node_vec.at(i).parent;
					class_var.push_back(tmp);
				}
			}
			fout << macro->makeVariable("_int32", var_name);
			break;
		case Long:
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "name")
				{
					var_name = node_vec.at(i).var_vec.at(j).value;
					tmp.type = "_int64"; tmp.name = var_name;
					tmp.parent = node_vec.at(i).parent;
					class_var.push_back(tmp);
				}
			}
			fout << macro->makeVariable("_int64", var_name);
			break;
		case Bool:
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "name")
				{
					var_name = node_vec.at(i).var_vec.at(j).value;
					tmp.type = "bool"; tmp.name = var_name;
					tmp.parent = node_vec.at(i).parent;
					class_var.push_back(tmp);
				}
			}
			fout << macro->makeVariable("bool", var_name);
			break;
		case String:
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "name")
				{
					var_name = node_vec.at(i).var_vec.at(j).value;
					tmp.type = "string"; tmp.name = var_name;
					tmp.parent = node_vec.at(i).parent;
					class_var.push_back(tmp);
				}
			}
			fout << macro->makeVariable("string", var_name);
			break;
		case List:
			if (class_var.size() != 0) {
				tmp.type = "open";
				tmp.name = "openBrace";
				tmp.parentClass = node_vec.at(i).parentClass;
				tmp.depth = node_vec.at(i).depth;
				class_var.push_back(tmp);
			}


			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "class")
					class_name = node_vec.at(i).var_vec.at(j).value;
				else if (node_vec.at(i).var_vec.at(j).attrib == "name")
					var_name = node_vec.at(i).var_vec.at(j).value;
			}
			fout << macro->makeClass(class_name);



			for (int j = 0; j < node_vec.at(i).depth; j++) fout << macro->makeTab();
			fout << macro->makePublic();

			list_content.className = class_name;
			list_content.name = var_name;
			list_content.depth = node_vec.at(i).depth;
			list_content.parent = node_vec.at(i).parent;
			list_content.parentClass = node_vec.at(i).parentClass;
			list_var.push_back(list_content);

			break;
		case List_Var:
			for (int j = 0; j < node_vec.at(i).var_vec.size(); j++)
			{
				if (node_vec.at(i).var_vec.at(j).attrib == "name")
					var_name = node_vec.at(i).var_vec.at(j).value;
				else if (node_vec.at(i).var_vec.at(j).attrib == "type")
					type_name = node_vec.at(i).var_vec.at(j).value;
			}
			fout << macro->makeVariable(type_name, var_name);
			break;
		case CloseClassBrace:
			if (node_vec.at(i).close == "Packet") {
				if (class_var.size() != 0)
				{
					// GetStreamLength & Serialize & Parsing Method 추가 부분
					// 해당 각 변수들은 class_var 벡터에 들어가있음
					if (packet_type == "write" || packet_type == "both")
					{
						fout << macro->makeGetStreamLength(tmp.depth + 1, class_var, list_var);
						fout << macro->makeSerialize(tmp.depth + 1, class_var, list_var);
					}
					if (packet_type == "read" || packet_type == "both")
					{
						fout << macro->makeParsing(tmp.depth + 1, class_var, list_var);
					}
					class_var.clear();
					list_var.clear();
					for (int j = 0; j < node_vec.at(i).depth; j++) fout << macro->makeTab();

				}
			}
			else if (node_vec.at(i).close == "List") {
				tmp.type = "close";
				tmp.name = "closeBrace";
				tmp.parentClass = node_vec.at(i).parentClass;
				tmp.depth = node_vec.at(i).depth;
				class_var.push_back(tmp);
			}
			fout << macro->makeClassCloseBrace();
			break;
		case CloseBrace:
			fout << macro->makeCloseBrace();
			break;
		}
	}
	fout.close();
}
