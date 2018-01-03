#pragma once
//////////////////////////////////////////////////////////////////////////
// WidgetWrapper.h - WidgetWrapper class is Wrapper type of Widget
// Ver 1.0                                                              
// Application: Project #1  key/value pair in-memory database            
// Language:    C++, Visual Studio 2015                                 
// Platform:    Macbook pro, Core-i7, Windows 10                 
// Author:      Zezhong Li, SUID:903800321                            
// Reference:   Jim Fawcett, CST 4-187, Syracuse University			    
//              (315) 443-3948, jfawcett@twcny.rr.com				    
//////////////////////////////////////////////////////////////////////////
/*
* Public Interface :
*= = == == == == == == == == == == == == == ==
*
*	WidgetWrapper() {};
*	WidgetWrapper(Widget widget) : widget_(widget) {}
*	WidgetWrapper& operator=(const Widget& widget);
*	Xml save();
*	void restore(const Xml& xml);
*	operator Widget();
*
*
*
* Required Files :
*= = == == == == == == == == == == == == ==
*	Persist.h
*
* Build Command :
*= = == == == == == == == == == == == == ==
*devenv NoSqlDb.sln / rebuild debug
*
* Maintenance History :
*= = == == == == == == == == == == == == ==
*ver 1.0 : 30 Jam 17
* -first release
*ver 1.1 : 08 Feb 17
* added method - std::ostream& operator<<(std::ostream& out, Property<WidgetWrapper>& p)
*/
#include "Persist.h"

/////////////////////////////////////////////////////////////////////
// Widget and WidgetWrapper classes
//
class Widget
{
public:
	Property<int> wint;
	Property<std::string> wstr;
};

class WidgetWrapper : public IPersist<Widget>
{
public:
	WidgetWrapper() {};
	WidgetWrapper(Widget widget) : widget_(widget) {}
	WidgetWrapper& operator=(const Widget& widget);
	Xml save();
	void restore(const Xml& xml);
	operator Widget();
private:
	Widget widget_;
};
//----< assignment operator overload >-------------------------------

WidgetWrapper& WidgetWrapper::operator=(const Widget& widget)
{
	widget_ = widget;
	return *this;
}


/*----< overload insertion operator for std::string properties >---*/

std::ostream& operator<<(std::ostream& out, Property<WidgetWrapper>& p)
{
	WidgetWrapper temp = p.getValue();

	try {
		out << "\n    Properties of Widget are:";
		out << "\n    wint = " << static_cast<Widget>(temp).wint;
		out << "\n    wstr = " << static_cast<Widget>(temp).wstr;
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  exception:\n  " << ex.what() << "\n";
	}
	return out;
}



using SPtr = std::shared_ptr<AbstractXmlElement>;

//----< saves instance state as XML string >-------------------------

inline WidgetWrapper::Xml WidgetWrapper::save()
{
	XmlDocument doc;

	// make and add root element to doc
	SPtr root = makeTaggedElement("WidgetWrapper");
	doc.docElement() = root;

	// make Property<int> wint element and add to root
	int wintValue = static_cast<Widget>(*this).wint;
	std::string wintStr = Convert<int>::toString(wintValue);
	SPtr pWintElem = makeTaggedElement("wint");
	pWintElem->addChild(makeTextElement(wintStr));
	root->addChild(pWintElem);

	// make Property<std::string> wstr element and add to root
	std::string wStr = static_cast<Widget>(*this).wstr;
	SPtr pWstrElem = makeTaggedElement("wstr");
	pWstrElem->addChild(makeTextElement(wStr));
	root->addChild(pWstrElem);
	return doc.toString();
}
//---< restores instance state from XML string >---------------------

inline void WidgetWrapper::restore(const Xml& xml)
{
	XmlDocument doc(xml);
	std::vector<SPtr> elems = doc.element("wint").select();
	std::string temp = elems[0]->children()[0]->value();
	widget_.wint = Convert<int>::fromString(temp);
	elems = doc.element("wstr").select();
	widget_.wstr = elems[0]->children()[0]->value();
}
//----< cast operator returns Widget member >------------------------

inline WidgetWrapper::operator Widget()
{
	return widget_;
}