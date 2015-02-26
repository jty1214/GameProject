#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

enum HandlerType { BEGIN = -1, Packet, Int, Long, Bool, String, List, List_Var, CloseClassBrace, CloseBrace, END };

typedef struct type_struct {	// node 정보에 대한 구조체
	string type;
	string name;
	string parent;
	string parentClass;
	int depth;
}type_struct;

typedef struct var_struct {		// 각 노드에 대한 속성 구조체
	string attrib;
	string value;
}var_struct;

typedef struct node_struct {	// node 정보에 대한 구조체
	string type;
	int depth;
	vector<var_struct> var_vec;
	string parent;
	string parentClass;
	string close;
}node_struct;

typedef struct list_struct {
	string className;
	string name;
	int depth;
	string parent;
	string parentClass;
}list_struct;

class MACRO
{
public:
	string makeHeader(string name) {
		return "#include <" + name + ">\n";
	}

	string makeString(string str) {
		return str;
	}

	string makeNameSpace(string nsName) { // PDL 노드를 만났을 경우
		string str_ns;
		str_ns = "namespace " + nsName + "\n{\n";
		return str_ns;
	}

	string makeClass(string className) { // PACKET 노드를 만났을 경우
		string str_class;
		str_class = "class " + className + " {\n";
		return str_class;
	}

	string makeVariable(string primitiveDataType, string varName) { // VAR 노드를 만났을 경우
		string str_var;
		str_var = primitiveDataType + " " + varName + ";\n";
		return str_var;
	}

	string makeVariable(string primitiveDataType, string varName, string value) { // 값이 있는 변수 추가시
		string str_var;
		str_var = primitiveDataType + " " + varName + " = " + value + ";\n";
		return str_var;
	}

	string makeConstructor(string className) { // 생성자
		string str_constructor;
		str_constructor = className + "() {}\n";
		return str_constructor;
	}

	string makeDestructor(string className) { // 소멸자
		string str_Destructor;
		str_Destructor = className + "() {}\n";
		return str_Destructor;
	}

	string makeSetter(string primitiveDataType, string varName) { // Setter 생성
		string str_setter;
		str_setter = "void set_" + varName + "(" + primitiveDataType + "&& " + varName + ") {\n";
		str_setter += "this->" + varName + " = " + varName + ";\n\t\t}\n";
		return str_setter;
	}

	string makeGetter(string primitiveDataType, string varName) { // Getter 생성
		string str_getter;
		str_getter = primitiveDataType + "& get_" + varName + "() {\n";
		str_getter += "return " + varName + ";\n\t\t}\n";
		return str_getter;
	}

	string makeGetStreamLength(int depth, vector<type_struct> class_var, vector<list_struct> list_var) {
		string str_gsl = "\n", cmp_parent;
		int index = 0, cnt = 0, cmp_depth;
		for (int i = 0; i < depth; i++) str_gsl += "\t";
		str_gsl += "_int32 GetStreamLength() {\n";
		for (int i = 0; i < depth + 1; i++) str_gsl += "\t";
		str_gsl += "_int32 size=0;\n";
		if (list_var.size() == 0)
		{
			for (int i = 0; i < class_var.size(); i++)
			{
				for (int j = 0; j < depth; j++) str_gsl += "\t";
				if (class_var.at(i).type == "string")
				{
					str_gsl += "\tsize += sizeof(_int32);\n";
					for (int j = 0; j < depth + 1; j++) str_gsl += "\t";
					str_gsl += "size += (sizeof(char)*";
					str_gsl += class_var.at(i).name;
					str_gsl += ".length());\n";
				}
				else if (class_var.at(i).type == "close")
				{
					str_gsl += "}\n";
				}
				else
				{
					str_gsl += "\tsize += sizeof(";
					str_gsl += class_var.at(i).type;
					str_gsl += ");\n";
				}
			}
		}
		else
		{
			for (int i = 0; i < list_var.size(); i++)
			{
				string list_str;
				int idx = i;
				for (int j = i; j > 0; j--) {
					if (list_var.at(idx).parent == list_var.at(j - 1).name) {
						list_str.insert(0, list_var.at(j - 1).name + ".at(" + list_var.at(j - 1).name + "i).");
						idx--;
					}
				}
				list_str += list_var.at(i).name;


				for (int j = 0; j < depth + i + 1 - cnt; j++) str_gsl += "\t";
				str_gsl += "size += sizeof(_int32);\n";
				for (int j = 0; j < depth + i + 1 - cnt; j++) str_gsl += "\t";
				str_gsl += "for(_int32 " + list_var.at(i).name + "i=0;" + list_var.at(i).name + "i<";
				str_gsl += list_str + ".size();" + list_var.at(i).name + "i++) {\n";

				for (int j = index; j < class_var.size(); j++, index++)
				{
					if (class_var.at(j).type == "open")
					{
						index++;
						break;
					}

					for (int k = 0; k < depth + i + 1 - cnt; k++) str_gsl += "\t";
					if (class_var.at(j).type == "string")
					{
						string var_str;
						int flag;
						for (flag = i; flag>0; flag--) {
							if (list_var.at(flag).name == class_var.at(j).parent)
								break;
						}
						for (int k = i; k > 0; k--) {
							if (list_var.at(flag).parent == list_var.at(k - 1).name) {
								var_str.insert(0, list_var.at(k - 1).name + ".at(" + list_var.at(k - 1).name + "i).");
								flag--;
							}
						}
						var_str += class_var.at(j).parent + ".at(" + class_var.at(j).parent + "i)." + class_var.at(j).name;

						str_gsl += "\tsize += sizeof(_int32);\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_gsl += "\t";
						str_gsl += "size += (sizeof(char)*";
						str_gsl += var_str + ".length());\n";
					}
					else if (class_var.at(j).type == "close")
					{
						str_gsl += "}\n";
						cnt++;
					}
					else
					{
						str_gsl += "\tsize += sizeof(";
						str_gsl += class_var.at(j).type;
						str_gsl += ");\n";
					}
				}
			}
		}
		for (int i = 0; i < depth + 1; i++) str_gsl += "\t";
		str_gsl += "return size;\n";
		for (int i = 0; i < depth; i++) str_gsl += "\t";
		str_gsl += "}\n";
		return str_gsl;
	}

	string makeSerialize(int depth, vector<type_struct> class_var, vector<list_struct> list_var) {
		string str_serialize = "\n", cmp_parent;
		int index = 0, cnt = 0, cmp_depth;
		for (int i = 0; i < depth; i++) str_serialize += "\t";
		str_serialize += "void Serialize(void* byteStream) {\n";
		for (int i = 0; i < depth + 1; i++) str_serialize += "\t";
		str_serialize += "char* ptr = (char*)byteStream;\n";

		if (list_var.size() == 0)
		{
			for (int i = 0; i < class_var.size(); i++) {
				for (int j = 0; j < depth + 1; j++) str_serialize += "\t";

				if (class_var.at(i).type == "string")
				{
					str_serialize += "int " + class_var.at(i).name + "Length = " + class_var.at(i).name + ".length();\n";
					for (int j = 0; j < depth + 1; j++) str_serialize += "\t";
					str_serialize += "memcpy(ptr, (void *)(&";
					str_serialize += class_var.at(i).name + "Length), sizeof(_int32));\n";
					for (int j = 0; j < depth + 1; j++) str_serialize += "\t";
					str_serialize += "ptr += sizeof(_int32);\n";
					for (int j = 0; j < depth + 1; j++) str_serialize += "\t";
					str_serialize += "for(_int32 i=0;i<" + class_var.at(i).name + "Length;i++) {\n";
					for (int j = 0; j < depth + 2; j++) str_serialize += "\t";
					str_serialize += "memcpy(ptr, (void *)(&";
					str_serialize += class_var.at(i).name;
					str_serialize += ".at(i)), sizeof(char));\n";
					for (int j = 0; j < depth + 2; j++) str_serialize += "\t";
					str_serialize += "ptr += sizeof(char);\n";
					for (int j = 0; j < depth + 1; j++) str_serialize += "\t";
					str_serialize += "}\n";
				}
				else if (class_var.at(i).type == "close")
				{
					str_serialize += "}\n";
				}
				else
				{
					str_serialize += "memcpy(ptr, (void *)(&";
					str_serialize += class_var.at(i).name;
					str_serialize += "), sizeof(";
					str_serialize += class_var.at(i).name;
					str_serialize += "));\n";
					for (int j = 0; j < depth + 1; j++) str_serialize += "\t";
					str_serialize += "ptr += sizeof(";
					str_serialize += class_var.at(i).name;
					str_serialize += ");\n";
				}
			}
		}
		else {
			for (int i = 0; i < list_var.size(); i++)
			{
				string list_str;
				int idx = i;
				for (int j = i; j > 0; j--) {
					if (list_var.at(idx).parent == list_var.at(j - 1).name) {
						list_str.insert(0, list_var.at(j - 1).name + ".at(" + list_var.at(j - 1).name + "i).");
						idx--;
					}
				}
				list_str += list_var.at(i).name;


				for (int j = 0; j < depth + i + 1 - cnt; j++) str_serialize += "\t"; // 리스트의 개수
				str_serialize += "int " + list_var.at(i).name + "Size = " + list_str + ".size();\n";
				for (int j = 0; j < depth + i + 1 - cnt; j++) str_serialize += "\t"; // 리스트의 개수
				str_serialize += "memcpy(ptr, (void *)(&";
				str_serialize += list_var.at(i).name + "Size), sizeof(";
				str_serialize += list_var.at(i).name + "Size));\n";
				for (int j = 0; j < depth + i + 1 - cnt; j++) str_serialize += "\t";
				str_serialize += "ptr += sizeof(";
				str_serialize += list_var.at(i).name + "Size);\n";
				for (int j = 0; j < depth + i + 1 - cnt; j++) str_serialize += "\t";
				str_serialize += "for(_int32 " + list_var.at(i).name + "i=0;" + list_var.at(i).name +
					"i<" + list_var.at(i).name + "Size;" + list_var.at(i).name + "i++) {\n";

				for (int j = index; j < class_var.size(); j++, index++)
				{
					if (class_var.at(j).type == "open")
					{
						index++;
						break;
					}

					string var_str;
					int flag;
					for (flag = i; flag>0; flag--) {
						if (list_var.at(flag).name == class_var.at(j).parent)
							break;
					}
					for (int k = i; k > 0; k--) {
						if (list_var.at(flag).parent == list_var.at(k - 1).name) {
							var_str.insert(0, list_var.at(k - 1).name + ".at(" + list_var.at(k - 1).name + "i).");
							flag--;
						}
					}
					var_str += class_var.at(j).parent + ".at(" + class_var.at(j).parent + "i)." + class_var.at(j).name;

					for (int k = 0; k < depth + i + 1 - cnt; k++) str_serialize += "\t";
					if (class_var.at(j).type == "string")
					{
						str_serialize += "\tint " + class_var.at(j).name + "Length = " + var_str + ".length();\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_serialize += "\t";
						str_serialize += "memcpy(ptr, (void *)(&";
						str_serialize += class_var.at(j).name + "Length), sizeof(_int32));\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_serialize += "\t";
						str_serialize += "ptr += sizeof(_int32);\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_serialize += "\t";
						str_serialize += "for(_int32 i=0;i<" + class_var.at(j).name + "Length;i++) {\n";
						for (int k = 0; k < depth + i + 3 - cnt; k++) str_serialize += "\t";
						str_serialize += "memcpy(ptr, (void *)(&";
						str_serialize += var_str;// class_var.at(j).name;
						str_serialize += ".at(i)), sizeof(char));\n";
						for (int k = 0; k < depth + i + 3 - cnt; k++) str_serialize += "\t";
						str_serialize += "ptr += sizeof(char);\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_serialize += "\t";
						str_serialize += "}\n";
					}
					else if (class_var.at(j).type == "close")
					{
						str_serialize += "}\n";
						cnt++;
					}
					else
					{
						str_serialize += "\tmemcpy(ptr, (void *)(&";
						str_serialize += var_str;// class_var.at(j).name;
						str_serialize += "), sizeof(";
						str_serialize += var_str;// class_var.at(j).name;
						str_serialize += "));\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_serialize += "\t";
						str_serialize += "ptr += sizeof(";
						str_serialize += var_str;// class_var.at(j).name;
						str_serialize += ");\n";
					}
				}
			}
		}
		for (int i = 0; i < depth; i++) str_serialize += "\t";
		str_serialize += "}\n";
		return str_serialize;
	}

	string makeParsing(int depth, vector<type_struct> class_var, vector<list_struct> list_var) {
		string str_parsing = "\n", cmp_parent;
		vector<int> close_order;
		int index = 0, cnt = 0, cmp_depth;
		for (int i = 0; i < depth; i++) str_parsing += "\t";
		str_parsing += "void Parsing(void* byteStream) {\n";
		for (int i = 0; i < depth + 1; i++) str_parsing += "\t";
		str_parsing += "_int32 index = 0, str_len;\n";
		for (int i = 0; i < depth + 1; i++) str_parsing += "\t";
		str_parsing += "char *str;\n";

		if (list_var.size() == 0)
		{
			for (int i = 0; i < class_var.size(); i++) {
				for (int j = 0; j < depth + 1; j++) str_parsing += "\t";

				if (class_var.at(i).type == "string")
				{
					str_parsing += "memcpy(&str_len, (char *)byteStream + index, sizeof(_int32));\n";
					for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
					str_parsing += "index += sizeof(str_len);\n";
					for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
					str_parsing += "str = new char[str_len+1];\n";
					for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
					str_parsing += "for(_int32 i=0;i<str_len;i++) {\n";
					for (int j = 0; j < depth + 2; j++) str_parsing += "\t";
					str_parsing += "memcpy(str+i, (char *)byteStream + index, sizeof(char));\n";
					for (int j = 0; j < depth + 2; j++) str_parsing += "\t";
					str_parsing += "index += sizeof(char);\n";
					for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
					str_parsing += "}\n";
					for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
					str_parsing += "str[str_len] = \'\\0\';\n";
					for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
					str_parsing += class_var.at(i).name + " = string(str);\n";
					for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
					str_parsing += "delete str;\n";
				}
				else if (class_var.at(i).type == "close")
				{
					str_parsing += "}\n";
				}
				else
				{
					str_parsing += "memcpy(&";
					str_parsing += class_var.at(i).name;
					str_parsing += ", (char *)byteStream + index, sizeof(";
					str_parsing += class_var.at(i).type;
					str_parsing += "));\n";
					for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
					str_parsing += "index += sizeof(";
					str_parsing += class_var.at(i).name;
					str_parsing += ");\n";
				}
			}
		}
		else {
			for (int i = 0; i < list_var.size(); i++)
			{
				close_order.push_back(i);
				for (int j = 0; j < depth + i + 1 - cnt; j++) str_parsing += "\t"; // 리스트의 개수
				str_parsing += "_int32 " + list_var.at(i).name + "Length;\n";
				for (int j = 0; j < depth + i + 1 - cnt; j++) str_parsing += "\t";
				str_parsing += "memcpy(&" + list_var.at(i).name + "Length, (char *)byteStream + index, sizeof(_int32));\n";
				for (int j = 0; j < depth + i + 1 - cnt; j++) str_parsing += "\t";
				str_parsing += "index += sizeof(" + list_var.at(i).name + "Length);\n";
				for (int j = 0; j < depth + i + 1 - cnt; j++) str_parsing += "\t";
				str_parsing += "for(_int32 " + list_var.at(i).name + "i=0;" + list_var.at(i).name +
					"i<" + list_var.at(i).name + "Length;" + list_var.at(i).name + "i++) {\n";
				for (int j = 0; j < depth + i + 2 - cnt; j++) str_parsing += "\t";

				for (int j = 0; j <= i; j++) {
					str_parsing += list_var.at(j).className;
					if (list_var.at(j).className == list_var.at(i).parentClass) {
						str_parsing += "::" + list_var.at(i).className;
						break;
					}
					else if (i != 0) {
						str_parsing += "::";
					}
				}
				str_parsing += " " + list_var.at(i).name + "it;\n";

				for (int j = index; j < class_var.size(); j++, index++)
				{
					if (class_var.at(j).type == "open")
					{
						index++;
						break;
					}

					string var_str;
					int flag;
					for (flag = i; flag>0; flag--) {
						if (list_var.at(flag).name == class_var.at(j).parent)
							break;
					}
					for (int k = i; k > 0; k--) {
						if (list_var.at(flag).parent == list_var.at(k - 1).name) {
							var_str.insert(0, list_var.at(k - 1).name + ".at(" + list_var.at(k - 1).name + "i).");
							flag--;
						}
					}
					var_str += class_var.at(j).parent + ".at(" + class_var.at(j).parent + "i)." + class_var.at(j).name;


					for (int k = 0; k < depth + i + 1 - cnt; k++) str_parsing += "\t";
					if (class_var.at(j).type == "string")
					{
						str_parsing += "\tmemcpy(&str_len, (char *)byteStream + index, sizeof(_int32));\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
						str_parsing += "index += sizeof(str_len);\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
						str_parsing += "str = new char[str_len+1];\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
						str_parsing += "for(_int32 i=0;i<str_len;i++) {\n";
						for (int k = 0; k < depth + i + 3 - cnt; k++) str_parsing += "\t";
						str_parsing += "memcpy(str+i, (char *)byteStream + index, sizeof(char));\n";
						for (int k = 0; k < depth + i + 3 - cnt; k++) str_parsing += "\t";
						str_parsing += "index += sizeof(char);\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
						str_parsing += "}\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
						str_parsing += "str[str_len] = \'\\0\';\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
						str_parsing += var_str + " = string(str);\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
						str_parsing += "delete str;\n";
					}
					else if (class_var.at(j).type == "close")
					{
						int close = close_order.at(close_order.size() - 1);
						close_order.pop_back();
						if (close == 0)
							str_parsing += "\t" + list_var.at(close).name + ".push_back(" + list_var.at(close).name + "it);\n";
						else
							str_parsing += "\t" + list_var.at(close).parent + "it." + list_var.at(close).name + ".push_back(" + list_var.at(close).name + "it);\n";
						for (int k = 0; k < depth + i + 1 - cnt; k++) str_parsing += "\t";
						str_parsing += "}\n";
						cnt++;
					}
					else
					{
						str_parsing += "\tmemcpy(&";
						str_parsing += var_str;//class_var.at(j).name;
						str_parsing += ", (char *)byteStream + index, sizeof(";
						str_parsing += class_var.at(j).type;
						str_parsing += "));\n";
						for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
						str_parsing += "index += sizeof(";
						str_parsing += var_str;// class_var.at(j).name;
						str_parsing += ");\n";
					}
				}
			}
		}
		for (int i = 0; i < depth; i++) str_parsing += "\t";
		str_parsing += "}\n";
		return str_parsing;
	}

	string makePublic() {
		return "public:\n";
	}

	string makeProtected() {
		return "protected:\n";
	}

	string makePrivate() {
		return "private:\n";
	}
	string makeCloseBrace() {
		return "}\n";
	}
	string makeClassCloseBrace() {
		return "};\n";
	}
	string makeTab() {
		return "\t";
	}
};
