using UnityEngine;
using System.Collections;
using System;
using System.Xml;

public class XMLManager : MonoBehaviour{
	public string _fileName = "Book1";
	XmlNodeList Vector_Table;
	
	void Start(){
		Xml_Load(_fileName);
		CreateObject();
	}
	void Xml_Load(string Filename){
		TextAsset tA = (TextAsset) Resources.Load("XML/"+Filename);
		XmlDocument xd = new XmlDocument();
		xd.LoadXml(tA.text);
		
		XmlNodeList Hp_Table = xd.GetElementsByTagName("HP");
		int hp = int.Parse(Hp_Table [0].InnerText);
		Vector_Table = xd.GetElementsByTagName("VECTOR");
		
		Debug.Log(hp);
		
		XmlNodeList nodes = xd.SelectNodes("UnitSet/Unit");
		
		string s = "";
		foreach ( XmlNode node in nodes){
			Debug.Log("Name : " + node.SelectSingleNode("Name").InnerText);
			Debug.Log("HP : " + node.SelectSingleNode("HP").InnerText);
			Debug.Log("ATK : " + node.SelectSingleNode("ATK").InnerText);
			Debug.Log("DEF : " + node.SelectSingleNode("DEF").InnerText);
			Debug.Log("EVD : " + node.SelectSingleNode("EVD").InnerText);
		}
		
	}
	void CreateObject(){
		string s = Vector_Table[0].InnerText;
		ObjectManager om = new ObjectManager(s);
	}
}
