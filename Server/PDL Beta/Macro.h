#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

enum { Packet, Int, Long, Bool, String, List, List_Var };

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
}node_struct;

typedef struct list_struct {
	string className;
	string name;
	int depth;
	string parent;
	string parentClass;
};

namespace macro
{
	class MACRO
	{
		MACRO() {}
		~MACRO() {}
		static MACRO* macroInstance;

	public:
		static MACRO* getInstance() { // Singletone Pattern
			if (macroInstance == NULL)
				macroInstance = new MACRO();
			return macroInstance;
		}

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
					for (int j = 0; j < depth + 1; j++) str_gsl += "\t";
					if (class_var.at(i).type != "string")
					{
						str_gsl += "size += sizeof(";
						str_gsl += class_var.at(i).type;
						str_gsl += ");\n";
					}
					else
					{
						str_gsl += "size += sizeof(_int32);\n";
						for (int j = 0; j < depth + 1; j++) str_gsl += "\t";
						str_gsl += "size += sizeof(";
						str_gsl += class_var.at(i).name;
						str_gsl += ");\n";
					}
				}
			}
			else
			{
				for (int i = 0; i < list_var.size(); i++)
				{
					if (class_var.at(index).parent == class_var.at(index + 1).parent)
					{
						for (int j = 0; j < depth + i + 1 - cnt; j++) str_gsl += "\t";
						str_gsl += "size += sizeof(_int32);\n";
						for (int j = 0; j < depth + i + 1 - cnt; j++) str_gsl += "\t";
						str_gsl += "for(_int32 " + list_var.at(i).name + "i;" + list_var.at(i).name
							+ "i<;" + list_var.at(i).name + ".size();" + list_var.at(i).name + "i++) {\n";

						cmp_parent = class_var.at(index).parent;
						cmp_depth = class_var.at(index).depth;
					}
					else {
						i--;
					}

					for (int j = index; j < class_var.size(); j++, index++)
					{
						if (cmp_depth == class_var.at(index).depth && cmp_parent == class_var.at(index).parent)
						{
							cmp_parent = class_var.at(index).parent;
							cmp_depth = class_var.at(index).depth;
							for (int k = 0; k < depth + i + 2 - cnt; k++) str_gsl += "\t";
							if (class_var.at(j).type != "string")
							{
								str_gsl += "size += sizeof(";
								str_gsl += class_var.at(j).type;
								str_gsl += ");\n";
							}
							else
							{
								str_gsl += "size += sizeof(_int32);\n";
								for (int k = 0; k < depth + i + 2 - cnt; k++) str_gsl += "\t";
								str_gsl += "size += sizeof(";
								str_gsl += class_var.at(j).name;
								str_gsl += ");\n";
							}
						}
						else if (cmp_depth > class_var.at(index).depth && cmp_parent != class_var.at(index).parent)
						{

							for (int k = 0; k < cmp_depth - class_var.at(index).depth; k++)
							{
								for (int l = 0; l < depth + i + 1 - cnt; l++) str_gsl += "\t";
								str_gsl += "}\n";
								cnt++;
							}

							for (int l = 0; l < depth + i + 2 - cnt; l++) str_gsl += "\t";
							if (class_var.at(j).type != "string")
							{
								str_gsl += "size += sizeof(";
								str_gsl += class_var.at(j).type;
								str_gsl += ");\n";
							}
							else
							{
								str_gsl += "size += sizeof(_int32);\n";
								for (int l = 0; l < depth + i + 2 - cnt; l++) str_gsl += "\t";
								str_gsl += "size += sizeof(";
								str_gsl += class_var.at(j).name;
								str_gsl += ");\n";
							}
							cmp_parent = class_var.at(index).parent;
							cmp_depth = class_var.at(index).depth;
							index++;

							break;
						}
						else
							break;
					}
				}
				for (int i = 0; i < list_var.size() - cnt; i++)
				{
					for (int j = 0; j < depth + list_var.size() - i - cnt; j++) str_gsl += "\t";
					str_gsl += "}\n";
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

					if (class_var.at(i).type != "string")
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
					else
					{
						str_serialize += "memcpy(ptr, (void *)(&sizeof(";
						str_serialize += class_var.at(i).name;
						str_serialize += ")), sizeof(_int32));\n";
						for (int j = 0; j < depth + 1; j++) str_serialize += "\t";
						str_serialize += "ptr += sizeof(_int32);\n";
						for (int j = 0; j < depth + 1; j++) str_serialize += "\t";
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
				cmp_depth = class_var.at(index).depth;
				cmp_parent = class_var.at(index).parent;
				for (int i = 0; i < list_var.size(); i++)
				{
					if (cmp_depth >= class_var.at(index).depth && cmp_parent != class_var.at(index).parent)
					{
						for (int j = 0; j <= cmp_depth - class_var.at(index).depth; j++)
						{
							for (int k = 0; k < depth + i - cnt; k++) str_serialize += "\t";
							str_serialize += "}\n";
							cnt++;
						}
					}

					if (class_var.at(index).parent == class_var.at(index + 1).parent)
					{
						for (int j = 0; j < depth + i + 1 - cnt; j++) str_serialize += "\t"; // 리스트의 개수
						str_serialize += "memcpy(ptr, (void *)(&";
						str_serialize += list_var.at(i).name;
						str_serialize += ".size()), sizeof(";
						str_serialize += list_var.at(i).name;
						str_serialize += ".size()));\n";
						for (int j = 0; j < depth + i + 1 - cnt; j++) str_serialize += "\t";
						str_serialize += "ptr += sizeof(";
						str_serialize += list_var.at(i).name;
						str_serialize += ");\n";
						for (int j = 0; j < depth + i + 1 - cnt; j++) str_serialize += "\t";
						str_serialize += "for(_int32 " + list_var.at(i).name + "i=0;" + list_var.at(i).name +
							"i<" + list_var.at(i).name + ".size();" + list_var.at(i).name + "i++) {\n";

						cmp_parent = class_var.at(index).parent;
						cmp_depth = class_var.at(index).depth;
					}
					else {
						i--;
					}

					for (int j = index; j < class_var.size(); j++, index++)
					{
						if (cmp_depth == class_var.at(index).depth && cmp_parent == class_var.at(index).parent)
						{
							cmp_parent = class_var.at(index).parent;
							cmp_depth = class_var.at(index).depth;
							for (int k = 0; k < depth + i + 2 - cnt; k++) str_serialize += "\t";
							if (class_var.at(j).type != "string")
							{
								str_serialize += "memcpy(ptr, (void *)(&";
								str_serialize += class_var.at(j).name;
								str_serialize += "), sizeof(";
								str_serialize += class_var.at(j).name;
								str_serialize += "));\n";
								for (int k = 0; k < depth + i + 2 - cnt; k++) str_serialize += "\t";
								str_serialize += "ptr += sizeof(";
								str_serialize += class_var.at(j).name;
								str_serialize += ");\n";
							}
							else
							{
								str_serialize += "memcpy(ptr, (void *)(&sizeof(";
								str_serialize += class_var.at(j).name;
								str_serialize += ")), sizeof(_int32));\n";
								for (int k = 0; k < depth + i + 2 - cnt; k++) str_serialize += "\t";
								str_serialize += "ptr += sizeof(_int32);\n";
								for (int k = 0; k < depth + i + 2 - cnt; k++) str_serialize += "\t";
								str_serialize += "memcpy(ptr, (void *)(&";
								str_serialize += class_var.at(j).name;
								str_serialize += "), sizeof(";
								str_serialize += class_var.at(j).name;
								str_serialize += "));\n";
								for (int k = 0; k < depth + i + 2 - cnt; k++) str_serialize += "\t";
								str_serialize += "ptr += sizeof(";
								str_serialize += class_var.at(j).name;
								str_serialize += ");\n";
							}
						}
						else if (cmp_depth > class_var.at(index).depth && cmp_parent != class_var.at(index).parent)
						{

							for (int k = 0; k < cmp_depth - class_var.at(index).depth; k++)
							{
								for (int l = 0; l < depth + i + 1 - cnt; l++) str_serialize += "\t";
								str_serialize += "}\n";
								cnt++;
							}

							for (int l = 0; l < depth + i + 2 - cnt; l++) str_serialize += "\t";
							if (class_var.at(j).type != "string")
							{
								str_serialize += "memcpy(ptr, (void *)(&";
								str_serialize += class_var.at(j).name;
								str_serialize += "), sizeof(";
								str_serialize += class_var.at(j).name;
								str_serialize += "));\n";
								for (int l = 0; l < depth + i + 2 - cnt; l++) str_serialize += "\t";
								str_serialize += "ptr += sizeof(";
								str_serialize += class_var.at(j).name;
								str_serialize += ");\n";
							}
							else
							{
								str_serialize += "memcpy(ptr, (void *)(&sizeof(";
								str_serialize += class_var.at(j).name;
								str_serialize += ")), sizeof(_int32));\n";
								for (int l = 0; l < depth + i + 2 - cnt; l++) str_serialize += "\t";
								str_serialize += "ptr += sizeof(_int32);\n";
								for (int l = 0; l < depth + i + 2 - cnt; l++) str_serialize += "\t";
								str_serialize += "memcpy(ptr, (void *)(&";
								str_serialize += class_var.at(j).name;
								str_serialize += "), sizeof(";
								str_serialize += class_var.at(j).name;
								str_serialize += "));\n";
								for (int l = 0; l < depth + i + 2 - cnt; l++) str_serialize += "\t";
								str_serialize += "ptr += sizeof(";
								str_serialize += class_var.at(j).name;
								str_serialize += ");\n";
							}
							cmp_parent = class_var.at(index).parent;
							cmp_depth = class_var.at(index).depth;
							index++;

							break;
						}
						else
							break;
					}
				}
				for (int i = 0; i < list_var.size() - cnt; i++)
				{
					for (int j = 0; j < depth + list_var.size() - i - cnt; j++) str_serialize += "\t";
					str_serialize += "}\n";
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

			if (list_var.size() == 0)
			{
				for (int i = 0; i < class_var.size(); i++) {
					for (int j = 0; j < depth + 1; j++) str_parsing += "\t";

					if (class_var.at(i).type != "string")
					{
						str_parsing += "memcpy(&";
						str_parsing += class_var.at(i).name;
						str_parsing += ", (" + class_var.at(i).type + " *)byteStream + index, sizeof(";
						str_parsing += class_var.at(i).type;
						str_parsing += "));\n";
						for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
						str_parsing += "index += sizeof(";
						str_parsing += class_var.at(i).name;
						str_parsing += ");\n";
					}
					else
					{
						str_parsing += "memcpy(&str_len, (_int32 *)byteStream + index, sizeof(_int32));\n";
						for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
						str_parsing += "index += sizeof(str_len);\n";
						for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
						str_parsing += "memcpy(&";
						str_parsing += class_var.at(i).name;
						str_parsing += ", (char *)byteStream + index, (sizeof(char)*str_len));\n";
						for (int j = 0; j < depth + 1; j++) str_parsing += "\t";
						str_parsing += "index += sizeof(";
						str_parsing += class_var.at(i).name;
						str_parsing += ");\n";
					}
				}
			}
			else {
				cmp_depth = class_var.at(index).depth;
				cmp_parent = class_var.at(index).parent;
				for (int i = 0; i < list_var.size(); i++)
				{
					if (cmp_depth >= class_var.at(index).depth && cmp_parent != class_var.at(index).parent)
					{
						int close = close_order.at(close_order.size() - 1);
						close_order.pop_back();
						for (int j = 0; j <= cmp_depth - class_var.at(index).depth; j++)
						{
							for (int k = 0; k < depth + i + 1 - cnt; k++) str_parsing += "\t";
							str_parsing += list_var.at(close).parent + "it." + list_var.at(close).name + ".push_back(" + list_var.at(close).name + "it);\n";
							for (int k = 0; k < depth + i - cnt; k++) str_parsing += "\t";
							str_parsing += "}\n";
							cnt++;
						}
					}

					if (class_var.at(index).parent == class_var.at(index + 1).parent)
					{
						close_order.push_back(i);
						for (int j = 0; j < depth + i + 1 - cnt; j++) str_parsing += "\t"; // 리스트의 개수
						str_parsing += "_int32 " + list_var.at(i).name + "Length;\n";
						for (int j = 0; j < depth + i + 1 - cnt; j++) str_parsing += "\t";
						str_parsing += "memcpy(&" + list_var.at(i).name + "Length, (_int32 *)byteStream + index, sizeof(_int32));\n";
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


						cmp_parent = class_var.at(index).parent;
						cmp_depth = class_var.at(index).depth;
					}
					else {
						i--;
					}

					for (int j = index; j < class_var.size(); j++, index++)
					{
						if (cmp_depth == class_var.at(index).depth && cmp_parent == class_var.at(index).parent)
						{
							cmp_parent = class_var.at(index).parent;
							cmp_depth = class_var.at(index).depth;
							for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
							if (class_var.at(j).type != "string")
							{
								str_parsing += "memcpy(&";
								str_parsing += class_var.at(j).name;
								str_parsing += ", (" + class_var.at(j).type + " *)byteStream + index, sizeof(";
								str_parsing += class_var.at(j).type;
								str_parsing += "));\n";
								for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
								str_parsing += "index += sizeof(";
								str_parsing += class_var.at(j).name;
								str_parsing += ");\n";
							}
							else
							{
								str_parsing += "memcpy(&str_len, (_int32 *)byteStream + index, sizeof(_int32));\n";
								for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
								str_parsing += "index += sizeof(str_len);\n";
								for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
								str_parsing += "memcpy(&";
								str_parsing += class_var.at(j).name;
								str_parsing += ", (char *)byteStream + index, (sizeof(char)*str_len));\n";
								for (int k = 0; k < depth + i + 2 - cnt; k++) str_parsing += "\t";
								str_parsing += "index += sizeof(";
								str_parsing += class_var.at(j).name;
								str_parsing += ");\n";
							}
						}
						else if (cmp_depth > class_var.at(index).depth && cmp_parent != class_var.at(index).parent)
						{
							int close = close_order.at(close_order.size() - 1);
							close_order.pop_back();

							for (int k = 0; k < cmp_depth - class_var.at(index).depth; k++)
							{
								for (int l = 0; l < depth + i + 2 - cnt; l++) str_parsing += "\t";
								str_parsing += list_var.at(close).parent + "it." + list_var.at(close).name + ".push_back(" + list_var.at(close).name + "it);\n";
								for (int l = 0; l < depth + i + 1 - cnt; l++) str_parsing += "\t";
								str_parsing += "}\n";
								cnt++;
							}

							for (int l = 0; l < depth + i + 2 - cnt; l++) str_parsing += "\t";
							if (class_var.at(j).type != "string")
							{
								str_parsing += "memcpy(&";
								str_parsing += class_var.at(j).name;
								str_parsing += ", (" + class_var.at(j).type + " *)byteStream + index, sizeof(";
								str_parsing += class_var.at(j).type;
								str_parsing += "));\n";
								for (int l = 0; l < depth + i + 2 - cnt; l++) str_parsing += "\t";
								str_parsing += "index += sizeof(";
								str_parsing += class_var.at(j).name;
								str_parsing += ");\n";
							}
							else
							{
								str_parsing += "memcpy(&str_len, (_int32 *)byteStream + index, sizeof(_int32));\n";
								for (int l = 0; l < depth + i + 2 - cnt; l++) str_parsing += "\t";
								str_parsing += "index += sizeof(str_len);\n";
								for (int l = 0; l < depth + i + 2 - cnt; l++) str_parsing += "\t";
								str_parsing += "memcpy(&";
								str_parsing += class_var.at(j).name;
								str_parsing += ", (char *)byteStream + index, (sizeof(char)*str_len));\n";
								for (int l = 0; l < depth + i + 2 - cnt; l++) str_parsing += "\t";
								str_parsing += "index += sizeof(";
								str_parsing += class_var.at(j).name;
								str_parsing += ");\n";
							}
							cmp_parent = class_var.at(index).parent;
							cmp_depth = class_var.at(index).depth;
							index++;

							break;
						}
						else
							break;
					}
				}
				for (int i = 0; i < list_var.size() - cnt; i++)
				{
					int close = close_order.at(close_order.size() - 1);
					close_order.pop_back();
					for (int j = 0; j < depth + list_var.size() - i - cnt + 1; j++) str_parsing += "\t";
					if (close != 0)
						str_parsing += list_var.at(close).parent + "it." + list_var.at(close).name + ".push_back(" + list_var.at(close).name + "it);\n";
					else
						str_parsing += list_var.at(close).name + ".push_back(" + list_var.at(close).name + "it);\n";

					for (int j = 0; j < depth + list_var.size() - i - cnt; j++) str_parsing += "\t";
					str_parsing += "}\n";
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

	MACRO *MACRO::macroInstance;
}