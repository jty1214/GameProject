#include <iostream>
using namespace std;

/* 사용법

	macro::MACRO *macro = macro::MACRO::getInstance();
	macro->이용하고자하는 함수();
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