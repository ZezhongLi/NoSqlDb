
///////////////////////////////////////////////////////////////////////////////
// TestExec.cpp - Test method of functions and classes under NoSqlDb solution.
// Ver 1.2                                                              
// Application: Project #1  key/value pair in-memory database            
// Language:    C++, Visual Studio 2015                                 
// Platform:    Macbook pro, Core-i7, Windows 10                 
// Author:      Zezhong Li, SUID:903800321                            
// Reference:   Jim Fawcett, CST 4-187, Syracuse University			    
//              (315) 443-3948, jfawcett@twcny.rr.com				    
///////////////////////////////////////////////////////////////////////////////

#include <ctime>
#include <fstream>
#include <regex>
#include <cstdlib>
#include "../NoSqlDb/NoSqlDb.h"
#include "../Utilities/Utilities.h"
#include "../Persist/StringWrapper.h"
#include "../Persist/WidgetWrapper.h"
#include "../Persist/DoubleWrapper.h"
#include "../XmlDocument/XmlParser/XmlParser.h"


using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

static void testR2() {
	Title("\n Test Requirement 2");
	NoSqlDb<WidgetWrapper> db;
	Element<WidgetWrapper> elem3;
	elem3.name = "elem3-widget";
	elem3.category = "test2";
	elem3.timeDate = "2017-02-09 10:50:00";
	elem3.description = "This is a widgetwrapper element";
	Widget w;
	w.wint = 4900;
	w.wstr = "Widget-No1";
	elem3.data = WidgetWrapper(w);
	elem3.addChildByKey("key2");
	elem3.addChildByKey("key3");
	elem3.addChildByKey("key4");

	db.save("key1", elem3);
	std::cout.setf(std::ios::adjustfield, std::ios::left);
	std::cout << "\n  Display of key and Element:\n";
	Keys keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n    " << std::setw(11) << "key in db" << " : " << key << std::endl;
		std::cout << "\n    " << std::setw(11) << "value in db" << " : ";
		std::cout << db.value(key).show();
	}
}

static void testR3_Part1()
{
	Title("\n Test Requirement 3");
	subTitle("\n Addition Testing");
	NoSqlDb<StrData> db;
	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	std::cout << "\n  Testing with std::string type as data type in element";
	std::cout << "\n  Adding elem1, elem2, elem3 to db";
	Element<StrData> elem1;
	elem1.name = "elem1";
	elem1.category = "testR3_Part1";
	elem1.timeDate = "2017-02-06 12:43:24";
	elem1.data = "elem1's StrData";
	elem1.description = "test addition and deletion with Element<std::string>";
	elem1.addChildByKey("key2");
	db.save("key1", elem1);

	Element<StrData> elem2;
	elem2.name = "elem2";
	elem2.category = "testR3_Part1";
	elem2.timeDate = "2017-02-06 12:43:24";
	elem2.data = "elem2's StrData";
	elem2.description = "test addition and deletion with Element<std::string>";
	elem2.addChildByKey("key3");
	db.save("key2", elem2);

	Element<StrData> elem3;
	elem3.name = "elem3";
	elem3.category = "testR3_Part1";
	elem3.timeDate = "2017-02-06 12:43:24";
	elem3.data = "elem3's StrData";
	elem3.description = "test addition and deletion with Element<std::string>";
	db.save("key3", elem3);

	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";
	Keys keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}

	subTitle("\n Delete key/value pair testing");
	std::cout << "\n Delete key/value pairs (elem2, elem3) by key from NoSqlDb<std::string>";
	std::cout << "\n And show results in db";
	std::cout << "\n -----------------------------------------------\n";
	db.remove("key2");
	db.remove("key3");
	keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n";
}

static void testR3_Part2()
{
	std::cout << "\n  Creating and saving NoSqlDb elements with int data";
	std::cout << "\n  Testing with int type as data type in element";
	std::cout << "\n  Adding ielem1, ielem2, ielem3 to db";
	std::cout << "\n ----------------------------------------------------\n";

	NoSqlDb<intData> idb;

	Element<intData> ielem1;
	ielem1.name = "ielem1";
	ielem1.category = "testR3_Part2";
	ielem1.timeDate = "2017-02-06 12:43:24";
	ielem1.description = "test addition and deletion with Element<int>";
	ielem1.data = 1;
	idb.save(ielem1.name, ielem1);

	Element<intData> ielem2;
	ielem2.name = "ielem2";
	ielem2.category = "testR3_Part2";
	ielem2.timeDate = "2017-02-06 12:43:24";
	ielem2.description = "test addition and deletion with Element<int>";
	ielem2.data = 2;
	idb.save(ielem2.name, ielem2);

	Element<intData> ielem3;
	ielem3.name = "ielem3";
	ielem3.category = "testR3_Part2";
	ielem3.timeDate = "2017-02-06 12:43:24";
	ielem3.description = "test addition and deletion with Element<int>";
	ielem3.data = 3;
	idb.save(ielem3.name, ielem3);

	std::cout << "\n  Retrieving elements from NoSqlDb<int>";
	std::cout << "\n ---------------------------------------\n";

	Keys ikeys = idb.keys();
	for (Key key : ikeys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << idb.value(key).show();
	}
	std::cout << "\n\n";

	subTitle("\n Delete key/value pair testing");
	std::cout << "\n Delete key/value pairs (elem3) by key from NoSqlDb<int>";
	std::cout << "\n And show results in db";
	std::cout << "\n -----------------------------------------------\n";
	idb.remove(ielem3.name);
	ikeys = idb.keys();
	for (Key key : ikeys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << idb.value(key).show();
	}
	std::cout << "\n\n";
}

static void testR4()
{
	Title("\n Test Requirement 4");
	NoSqlDb<WidgetWrapper> db;
	for (int i = 1; i < 3; i++) {
		Element<WidgetWrapper> elem;
		elem.name = "elem" + std::to_string(i) + "";
		elem.category = "testR4";
		elem.timeDate = "2017-02-06 12:43:25";
		elem.description = "This is a widgetwrapper element";
		Widget w1; w1.wint = 3310; w1.wstr = "Widget-No" + std::to_string(i);
		elem.data = WidgetWrapper(w1);
		elem.addChildByKey("key" + std::to_string(i + 1));
		db.save("key" + std::to_string(i), elem);	
	}
	auto temp = db.value("key2");
	temp.removeChildByKey("key3");
	db.put("key2", temp);
	subTitle("Original Data in db");
	Keys keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n Modify name, category, timeDate, description, children"; 
	std::cout << "\n and property value of data in db";
	subTitle("Modified Data in db");
	auto e1 = db.value("key1");
	e1.name = "elem1-widget-modified-name";
	e1.category = "modified category";
	e1.description = "This is a modified description.";
	e1.timeDate = "2020-02-06 12:43:25";
	e1.removeChildByKey("key2");
	Widget newWidget; newWidget.wint = 8888; newWidget.wstr = "modified Widget";
	e1.data = WidgetWrapper(newWidget);
	db.put("key1", e1);
	auto e2 = db.value("key2");
	Widget aWidget; aWidget.wint = 3150; aWidget.wstr = "new Widget";
	e2.data = WidgetWrapper(newWidget);
	db.put("key2", e2);
	keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n";
}


static void testR5()
{
	Title("\n Test Requirement 5");
	NoSqlDb<DoubleWrapper> db;
	for (int i = 0; i < 10; i++)
	{
		Element<DoubleWrapper> delem;
		delem.name = "double element" + std::to_string(i);
		delem.category = "testR5";
		delem.timeDate = "2017-02-06 12:43:25";
		delem.data = 100 + i;
		delem.description = "This is an element for testR5";
		delem.addChildByKey("20");
		delem.addChildByKey("30");
		delem.addChildByKey("40");
		db.save("key" + std::to_string(i), delem);
	}
	std::cout << "\n Number of element in db : " << db.count();
	subTitle("Persist db to xml file");
	db.toXmlFile("testR5.xml");
	db.clear();
	subTitle("Clear db");
	std::cout << "\n Number of element in db : " << db.count();
	std::cout << db.count() << std::endl;
	subTitle("Restore db from xml file");
	std::string src = "testR5.xml";
	// restore form xml file
	db = NoSqlDb<DoubleWrapper>::fromXml("testR5.xml");
	std::cout << "\n Number of element in db : " << db.count() << std::endl;
	Element<DoubleWrapper> temp = db.value("key9");
	subTitle("Display element which key = 'key9' from restored DB");
	std::cout << temp.show() << std::endl;
}

void delay(int ms)
{
	time_t start = clock();
	while (difftime(start + ms, clock()) > 0);
}

static void testR6() 
{
	Title("\n Test Requirement 6");
	subTitle("Demonstration of scheduled save db to file");
	subTitle("Persist db to testR6.xml every 5 second");
	NoSqlDb<DoubleWrapper> db;
	for (int i = 0; i < 100; i++)
	{
		Element<DoubleWrapper> delem;
		delem.name = "double element " + std::to_string(i);
		delem.category = "testR5";
		delem.timeDate = "2017-02-06 12:43:25";
		delem.data = 100 + i;
		delem.description = "This is an element for testR5";
		delem.addChildByKey("20");
		delem.addChildByKey("30");
		delem.addChildByKey("40");
		db.save("key" + std::to_string(i), delem);
	}
	std::string file = "testR6.xml";
	for (int i = 5; i >= 0; i--)
	{
		std::cout << "\n Counting down : " + std::to_string(i);
		delay(1000);
	}
	db.toXmlFile(file);
	std::cout << "\n saved db to testR6.xml";
	for (int i = 5; i >= 0; i--)
	{
		std::cout << "\n Counting down : " + std::to_string(i);
		delay(1000);
		
	}
	db.toXmlFile(file);
	std::cout << "\n saved db to testR6.xml";
}


static void testR7_Part1()
{
	Title("\n Test Requirement 7");
	
	NoSqlDb<DoubleWrapper> db;
	for (int i = 0; i < 100; i++)
	{
		Element<DoubleWrapper> delem;
		delem.name = "double_element_name_" + std::to_string(i);
		delem.category = "testR7_Part1";
		delem.data = 100 + i;
		delem.description = "This is an element for testR7_Part1";
		if (i != 50) {
			delem.addChildByKey("key50");
		}
		if (i != 60) {
			delem.addChildByKey("key60");
		}
		if (i != 70) {
			delem.addChildByKey("key70");
		}
		db.save("key" + std::to_string(i), delem);
	}
	subTitle("\n Query the value of a specified key");
	subTitle("\n Display value of key : 'key20'");
	Element<DoubleWrapper> e = db.value("key20");
	std::cout << e.show() << std::endl;
	std::unordered_set<std::string> children = db.getChildrenByKey("key20");
	subTitle("\n Query the value of children of a specified key");
	subTitle("\n Display all children element of key : 'key20'");
	for (std::string ckey : children) {
		Element<DoubleWrapper> temp = db.value(ckey);
		std::cout << temp.show() << std::endl;
	}
}

static void testR7_Part2()
{
	NoSqlDb<DoubleWrapper> db;
	for (int i = 0; i < 100; i++)
	{
		Element<DoubleWrapper> delem;
		delem.name = "double_element_name_" + std::to_string(i);
		delem.category = "testR7_Part1";
		delem.data = 100 + i;
		delem.description = "This is an element for testR7_Part1";
		if (i != 50) {delem.addChildByKey("key50");}
		if (i != 60) {delem.addChildByKey("key60");}
		if (i != 70) {delem.addChildByKey("key70");}
		db.save("key" + std::to_string(i), delem);
	}
	subTitle("\n Test of query a set of keys matching specified pattern");
	subTitle(" Display keys match the pattern:  contains '5' in key");
	/* Pattern of  */
	std::unordered_set<std::string> set;
	std::function<bool(std::string)> func_key = [=](std::string key) {
		if (key.find("5") != std::string::npos) {
			return true;
		}
		return false;
	};
	set = db.keysWithPatternInKey(func_key);
	std::cout << std::endl;
	for (auto ckey : set) {
		std::cout << ckey << "; ";
	}
	subTitle("\n Test of query a set of keys corresponds to element that have item name contains pattern");
	subTitle("\n Display keys that item name contains '9'");
	std::function<bool(Element<DoubleWrapper>)> func_name = [=](Element<DoubleWrapper> e) {
		std::string name = e.name;
		if (name.find("9") != std::string::npos) { return true; }
		return false;
	};
	set = db.keysWithPatternInElem(func_name);
	std::cout << std::endl;
	for (auto ckey : set) {
		std::cout << ckey << "; ";
	}
}

static void testR7_Part3()
{
	std::unordered_set<std::string> set;
	NoSqlDb<DoubleWrapper> db;
	for (int i = 0; i < 100; i++) {
		Element<DoubleWrapper> delem;
		delem.name = "double element" + std::to_string(i);
		delem.category = "testR7_Part3";
		delem.data = 100 + i;
		delem.description = "This is an element for testR7_Part3";
		if (i != 50) {delem.addChildByKey("50");}
		if (i != 60) {delem.addChildByKey("60");}
		if (i != 70) {delem.addChildByKey("70");}
		db.save(std::to_string(i), delem);
	}
	subTitle("\n Test of query a set of keys of element whose category name contains a specified string");
	subTitle(" Category with pattern contains 'test'");
	std::function<bool(Element<DoubleWrapper>)> func_obj = [=](Element<DoubleWrapper> e) {
		std::string category = e.category;
		if (category.find("test") != std::string::npos) {
			return true;
		}
		return false;
	};
	set = db.keysWithPatternInElem(func_obj);
	std::cout << std::endl;
	for (auto ckey : set) {
		std::cout << ckey << "; ";
	}
	subTitle("\n Test of query a set of keys corresponds element that has data value matching requirement");
	subTitle(" Display keys of elments which data value between 120 ~ 130");
	std::function<bool(Element<DoubleWrapper>)> func_data = [=](Element<DoubleWrapper> e) {
		double datav = e.data.getValue();
		if (datav < 130 && datav >= 120) { return true; }
		return false;
	};
	set = db.keysWithPatternInElem(func_data);
	std::cout << std::endl;
	for (auto ckey : set) {
		std::cout << ckey << "; ";
	}
}

static void testR7_Part4()
{
	NoSqlDb<DoubleWrapper> db;
	for (int i = 0; i < 10; i++) {
		Element<DoubleWrapper> delem;
		delem.name = "double element" + std::to_string(i);
		delem.timeDate = "2017-01-08 08:40:20";
		delem.category = "testR7_Part4";
		delem.data = 10 + i;
		delem.description = "This is an element for testR7_Part4";
		db.save("key" + std::to_string(i + 10), delem);
	}
	for (int i = 0; i < 10; i++) {
		Element<DoubleWrapper> delem;
		delem.name = "double element" + std::to_string(i);
		delem.timeDate = "2017-02-07 08:40:20";;
		delem.category = "testR7_Part4";
		delem.data = 100 + i;
		delem.description = "This is an element for testR7_Part4";
		db.save("key" + std::to_string(i + 100), delem);
	}
	for (int i = 0; i < 10; i++) {
		Element<DoubleWrapper> delem;
		delem.name = "double element" + std::to_string(i);
		delem.timeDate = "2017-03-10 12:40:20";;
		delem.category = "testR7_Part4";
		delem.data = 1000 + i;
		delem.description = "This is an element for testR7_Part4";
		db.save("key" + std::to_string(i + 1000), delem);
	}

	subTitle("\n Test of query of element's dateTime in period");
	subTitle(" Display keys of elments which timedate between 2017-02-07 to now :");
	
	std::unordered_set<std::string> set;
	std::string interval1 = "2017-01-30 12:00:00";
	//std::string interval2 = "2017-03-10 12:00:00";
	set = db.keysBetweenIntervals(interval1);
	std::cout << std::endl;
	for (auto ckey : set) {
		std::cout << ckey << "; ";
	}
}

static void testR8()
{
	Title("\n Test of Requirement 8");
	subTitle(" Test of compound query");
	NoSqlDb<DoubleWrapper> db;
	for (int i = 0; i < 100; i++) {
		Element<DoubleWrapper> delem;
		delem.name = "double element" + std::to_string(i);
		delem.timeDate = "2017-01-08 08:40:20";
		delem.category = "testR7_Part4";
		delem.data = 10 + i;
		delem.description = "This is an element for testR7_Part4";
		db.save("key" + std::to_string(i), delem);
	}
	subTitle("\n Display keys that item name contains '9'");
	std::unordered_set<std::string> set;
	std::function<bool(Element<DoubleWrapper>)> func_name9 = [=](Element<DoubleWrapper> e) {
		std::string name = e.name;
		if (name.find("9") != std::string::npos) { return true; }
		return false;
	};
	set = db.keysWithPatternInElem(func_name9);
	std::cout << std::endl;
	for (auto ckey : set) {
		std::cout << ckey << "; ";
	}
	subTitle("\n Query item name contains '5' based on returned set with item name contains '9'");
	NoSqlDb<DoubleWrapper> subDb = db.subDbOfKeys(set);
	std::function<bool(Element<DoubleWrapper>)> func_name5 = [=](Element<DoubleWrapper> e) {
		std::string name = e.name;
		if (name.find("5") != std::string::npos) { return true; }
		return false;
	};
	set = subDb.keysWithPatternInElem(func_name5);
	subTitle("\n Display keys that item name contains '9' and '5'");
	std::cout << std::endl;
	for (auto ckey : set) {
		std::cout << ckey << "; ";
	}
}

std::function<bool(std::string)> func_key3 = [=](std::string key) {
	if (key.find("3") != std::string::npos) {
		return true;
	}
	return false;
};

std::function<bool(std::string)> func_key5 = [=](std::string key) {
	if (key.find("5") != std::string::npos) {
		return true;
	}
	return false;
};

std::function<bool(std::string)> func_key7 = [=](std::string key) {
	if (key.find("7") != std::string::npos) {
		return true;
	}
	return false;
};

std::function<bool(Element<DoubleWrapper>)> func_name3 = [=](Element<DoubleWrapper> e) {
	std::string name = e.name;
	if (name.find("3") != std::string::npos) { return true; }
	return false;
};

std::function<bool(Element<DoubleWrapper>)> func_name5 = [=](Element<DoubleWrapper> e) {
	std::string name = e.name;
	if (name.find("5") != std::string::npos) { return true; }
	return false;
};

std::function<bool(Element<DoubleWrapper>)> func_name7 = [=](Element<DoubleWrapper> e) {
	std::string name = e.name;
	if (name.find("7") != std::string::npos) { return true; }
	return false;
};

static void testR9()
{
	Title("\n Test of Requirement 9");
	subTitle("\n Union of sets");
	NoSqlDb<DoubleWrapper> db;
	for (int i = 0; i < 100; i++) {
		Element<DoubleWrapper> delem;
		delem.name = "double element" + std::to_string(i);
		delem.timeDate = "2017-01-08 08:40:20";
		delem.category = "testR7_Part4";
		delem.data = 10 + i;
		delem.description = "This is an element for testR7_Part4";
		db.save("key" + std::to_string(i), delem);
	}
	
	std::unordered_set<std::string> set3 = db.keysWithPatternInKey(func_key3);
	subTitle("\n Display keys that name contains '3'");
	std::cout << std::endl;
	for (auto ckey : set3) {
		std::cout << ckey << "; ";
	}
	
	std::unordered_set<std::string> set5 = db.keysWithPatternInKey(func_key5);
	subTitle("\n Display keys that name contains '5'");
	std::cout << std::endl;
	for (auto ckey : set5) {
		std::cout << ckey << "; ";
	}
	
	std::unordered_set<std::string> set7 = db.keysWithPatternInKey(func_key7);
	subTitle("\n Display keys that name contains '7'");
	std::cout << std::endl;
	for (auto ckey : set7) {
		std::cout << ckey << "; ";
	}
	std::vector<std::unordered_set<std::string>> vec;
	vec.push_back(set3); vec.push_back(set5); vec.push_back(set7);
	std::unordered_set<std::string> set = db.unionOfSets(vec);
	subTitle("\n Union keys which name contains '3', '5', '7'");
	subTitle("\n Display keys that name contains '3', '5', '7'");
	std::cout << std::endl;
	for (auto ckey : set) {
		std::cout << ckey << "; ";
	}
}

static void testR10()
{
	using namespace std;
	Title("\n Test of Requirement 10");
	subTitle("\n Display of Project Dependency using Xml reading from 'Structure.xml'");
	fstream fIn;
	fIn.open("Structure.xml", ios::in);
	cout << endl;
	if (fIn.is_open())
	{
		string s;
		while (getline(fIn, s))
		{
			cout << s << endl;
			// Tokenize s here into columns (probably on spaces)
		}
		fIn.close();
	}
	else
		cout << "Error opening file " << errno << endl;
}

static void testR12()
{
	using namespace std;
	Title("\n Test of Requirement 10");
	subTitle("\n Regular expression matching");
	NoSqlDb<DoubleWrapper> db;
	for (int i = 0; i < 100; i++) {
		Element<DoubleWrapper> delem;
		delem.name = "double_element_" + std::to_string(i);
		delem.timeDate = "2017-01-08 08:40:20";
		delem.category = "testR7_Part4";
		delem.data = 10 + i;
		delem.description = "This is an element for testR7_Part4";
		db.save(std::to_string(i), delem);
	}
	for (int i = 0; i < 100; i++) {
		Element<DoubleWrapper> delem;
		delem.name = "double_" + std::to_string(i);
		delem.timeDate = "2017-01-08 08:40:20";
		delem.category = "testR7_Part4";
		delem.data = 100 + i;
		delem.description = "This is an element for testR7_Part4";
		db.save(std::to_string(i), delem);
	}
	subTitle("\n Find keys of elements whose name meet Regex '(double_element_)(.*)'");
	std::function<bool(Element<DoubleWrapper>)> func_nameReg = [=](Element<DoubleWrapper> e) {
		std::string name = e.name;
		if (std::regex_match(name, std::regex("(double_element_8)(.*)")))
			return true;
		return false;
	};
	std::cout << endl;
	std::unordered_set<std::string> set = db.keysWithPatternInElem(func_nameReg);
	std::cout << "\n Number of keys in db : " << db.count();
	std::cout << "\n Number of keys found match the pattern : " << set.size();
	subTitle("Display Keys found matching expression");
	std::cout << "\n";
	for (auto key : set) {
		std::cout << key << "; ";
	}
	std::cout << "\n\n";
}

int main()
{
	testR2();
	testR3_Part1();
	testR3_Part2();
	testR4();
	testR5();
	testR6();
	testR7_Part1();
	testR7_Part2();
	testR7_Part3();
	testR7_Part4();
	testR8();
	testR9();
	testR10();
	testR12();
	std::cout << "\n		End of demostration\n";
	std::cin.get();
	return 0;
}