#pragma once
//////////////////////////////////////////////////////////////////////////
// StringWrapper.h - StringWrapper class is Wrapper type of std::string
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
*	StringWrapper(const std::string& str = "") : str_(str) {}
*	StringWrapper& operator=(const std::string& s);  // covariant return type
*	Xml save();
*	void restore(const Xml& xml);
*	operator std::string();
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
* added method - std::ostream& operator<<(std::ostream& out, Property<StringWrapper>& p)
*/

#include "Persist.h"

/////////////////////////////////////////////////////////////////////
// StringWrapper class
// - wrapper classes implement the persistance interface
// - they almost certainly should be non-template classes
//   because they have to be type specific
//
class StringWrapper : public IPersist<std::string>
{
public:
	StringWrapper(const std::string& str = "") : str_(str) {}
	StringWrapper& operator=(const std::string& s);  // covariant return type
	Xml save();
	void restore(const Xml& xml);
	operator std::string();
private:
	std::string str_;
};
//----< assignment overload >----------------------------------------

StringWrapper& StringWrapper::operator=(const std::string& s)
{
	str_ = s;
	return *this;
}
//----< saves instance state as XML string >-------------------------

inline StringWrapper::Xml StringWrapper::save()
{
	return "<StringWrapper>" + str_ + "</StringWrapper>";
}

/*----< overload insertion operator for std::string properties >---*/

std::ostream& operator<<(std::ostream& out, Property<StringWrapper>& p)
{
	StringWrapper temp = p.getValue();
	try {
		out << static_cast<std::string>(temp);
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  exception:\n  " << ex.what() << "\n";
	}
	return out;
}

//---< restores instance state from XML string >---------------------

inline void StringWrapper::restore(const Xml& xml)
{
	size_t posStart = xml.find_first_of(">") + 1;
	size_t posEnd = xml.find_last_of("</");
	str_ = xml.substr(posStart, posEnd - posStart - 1);
}

//----< cast operator returns string member >------------------------

inline StringWrapper::operator std::string()
{
	return str_;
}