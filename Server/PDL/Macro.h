#include <iostream>
using namespace std;

/* ����

	macro::MACRO *macro = macro::MACRO::getInstance();
	macro->�̿��ϰ����ϴ� �Լ�();
	delete(macro);

*/


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

		string makeNameSpace(string nsName) { // PDL ��带 ������ ���
			string str_ns;
			str_ns = "namespace " + nsName + "\n{\n";
			return str_ns;
		}

		string makeClass(string className) { // PACKET ��带 ������ ���
			string str_class;
			str_class = "class " + className + " {\n";
			return str_class;
		}

		string makeVariable(string primitiveDataType, string varName) { // VAR ��带 ������ ���
			string str_var;
			str_var = primitiveDataType + " " + varName + ";\n";
			return str_var;
		}

		string makeVariable(string primitiveDataType, string varName, string value) { // ���� �ִ� ���� �߰���
			string str_var;
			str_var = primitiveDataType + " " + varName + " = " + value + ";\n";
			return str_var;
		}

		string makeConstructor(string className) { // ������
			string str_constructor;
			str_constructor = className + "() {}\n";
			return str_constructor;
		}

		string makeDestructor(string className) { // �Ҹ���
			string str_Destructor;
			str_Destructor = className + "() {}\n";
			return str_Destructor;
		}

		string makeSetter(string primitiveDataType, string varName) { // Setter ����
			string str_setter;
			str_setter = "void set_" + varName + "(" + primitiveDataType + "&& " + varName + ") {\n";
			str_setter += "this->" + varName + " = " + varName + ";\n\t\t}\n";
			return str_setter;
		}

		string makeGetter(string primitiveDataType, string varName) { // Getter ����
			string str_getter;
			str_getter = primitiveDataType + "& get_" + varName + "() {\n";
			str_getter += "return "+ varName + ";\n\t\t}\n";
			return str_getter;
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