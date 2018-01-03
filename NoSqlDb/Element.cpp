#pragma once

//////////////////////////////////////////////////////////////////////////
// Element.h - Element class is value part of NoSqlDb in-memory database
// Ver 1.0                                                              
// Application: Project #1  key/value pair in-memory database            
// Language:    C++, Visual Studio 2015                                 
// Platform:    Macbook pro, Core-i7, Windows 10                 
// Author:      Zezhong Li, SUID:903800321                            
// Reference:   Jim Fawcett, CST 4-187, Syracuse University			    
//              (315) 443-3948, jfawcett@twcny.rr.com				    
//////////////////////////////////////////////////////////////////////////
/*
This file contains test of functions provided in Element.h,
Other tests can be found in TestExec.cpp.
*/

#ifdef TEST_ELEMENT



#include "Element.h"
#include "../Persist/Persist.h"
#include "../Utilities/Utilities.h"
#include "../Persist/Doublewrapper.h"
#include "../Persist/StringWrapper.h"
#include "../Persist/WidgetWrapper.h"


int main()
{

	Element<StringWrapper> elem1;
	elem1.name = "elem1-string";
	elem1.category = "test1";
	elem1.timeDate = "Feb 2, 2017 7:52 PM";
	elem1.description = "This is a stringwrapper element";
	elem1.data = StringWrapper("elem1's StrData");
	elem1.addChildByKey("schild1");
	elem1.addChildByKey("schild2");
	elem1.addChildByKey("schild3");

	Element<DoubleWrapper> elem2;
	elem2.name = "elem2-double";
	elem2.category = "test1";
	elem2.timeDate = "Feb 2, 2017 7:52 PM";
	elem2.description = "This is a doublewrapper element";
	elem2.data = DoubleWrapper(1.74747);
	elem2.addChildByKey("dchild1");
	elem2.addChildByKey("dchild2");
	elem2.addChildByKey("dchild3");

	Element<WidgetWrapper> elem3;
	elem3.name = "elem3-widget";
	elem3.category = "test2";
	elem3.description = "This is a widgetwrapper element";
	Widget w;
	w.wint = 4900;
	w.wstr = "Widget-No1";
	elem3.data = WidgetWrapper(w);
	elem3.addChildByKey("wchild1");
	elem3.addChildByKey("wchild2");
	elem3.addChildByKey("wchild3");

	Title("Test Element<Data>::show()");
	subTitle("\nTesting with Data is std::string");
	std::cout << "display of elem1:\n" << elem1.show();

	subTitle("\nTesting with Data is double");
	std::cout << "display of elem2:\n" << elem2.show();

	subTitle("\nTesting with Data is widget");
	std::cout << "display of elem2:\n" << elem3.show();

	Title("\nTest Element<Data>::toXml()");

	subTitle("Testing with Data is std::string");
	std::string xml = elem1.toXml();
	std::cout << "\n Xml saved for Element = " << xml;

	subTitle("\nTesting with Data is double");
	xml = elem2.toXml();
	std::cout << "\n Xml saved for Element = " << xml;

	subTitle("\nTesting with Data is Widget");
	xml = elem3.toXml();
	std::cout << "\n Xml saved for Element = " << xml;

	std::cout << std::endl;
	std::cout << std::endl;
}

#endif // TEST_ELEMENT


