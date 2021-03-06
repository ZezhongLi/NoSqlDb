#pragma once
/////////////////////////////////////////////////////////////////////
// PersistHelp.h - demo one way to persist objects to XML file     //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////
/*
* This package builds wrapper classes for strings, doubles, and Widgets.
* They provide the same functionality as the wrapped type, but also
* attach methods save() and restore() to persist the wrapped type.
*
* Package operations:
* -------------------
* This package contains:
* - IPersist interface - defines the methods needed to
*   serialize to XML and deserialize from XML
* - StringWrapper class that persists strings
* - DoubleWrapper class that persists doubles
* - Widget class with int and string properties
* - WidgetWrapper class that persits Widgets
*
* Required Files:
* ---------------
*   PersistHelp.h, PersistHelp.cpp,
*   Convert.h, Convert.cpp,
*   CppProperties.h, CppProperties.cpp,
*   XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp,
*  ---- required to build XmlDocument from file or string ----
*   XmlParser.h, XmlParser.cpp,
*   XmlElementParts.h, XmlElementParts.cpp,
*   ITokenizer.h, Tokenizer.h, Tokenizer.cpp,
*
* Build Instructions:
* -------------------
* - Uses XmlDocument, so build XmlDocument project as static library
*   after undefining its test stub
*/
#include <string>
#include <vector>
#include "../Serialize/Convert.h"
#include "../CppProperties/CppProperties.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"

using namespace XmlProcessing;

/////////////////////////////////////////////////////////////////////
// IPersist interface
// - declares methods Persistance Wrappers must use
//
template<typename T>
struct IPersist
{
	using Xml = std::string;

	virtual ~IPersist() {}
	virtual IPersist<T>& operator=(const T& t) = 0;
	virtual operator T() = 0;
	virtual Xml save() = 0;
	virtual void restore(const Xml& xml) = 0;
	std::string id() { return typeid(*this).name(); }
};






