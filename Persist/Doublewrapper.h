#pragma once
//////////////////////////////////////////////////////////////////////////
// DoubleWrapper.h - DoubleWrapper class is Wrapper type of double
// Ver 1.0                                                              
// Application: Project #1  key/value pair in-memory database            
// Language:    C++, Visual Studio 2015                                 
// Platform:    Macbook pro, Core-i7, Windows 10                 
// Author:      Zezhong Li, SUID:903800321                            
// Reference:   Jim Fawcett, CST 4-187, Syracuse University			    
//              (315) 443-3948, jfawcett@twcny.rr.com				    
//////////////////////////////////////////////////////////////////////////

#include "../Persist/Persist.h"
#include "../Serialize/Convert.h"
#include "../Utilities/Utilities.h"

/////////////////////////////////////////////////////////////////////
// DoubleWrapper class
// Wrapper of double type used in Elemnt<Data>
//
class DoubleWrapper : public IPersist<double>
{
public:
	DoubleWrapper(double d = 0) : d_(d) {}
	DoubleWrapper& operator=(const double& d);
	Xml save();
	static DoubleWrapper fromXml(std::string xml);
	void restore(const Xml& xml);
	operator double();
private:
	double d_;
};
//----< assignment overload >----------------------------------------

DoubleWrapper& DoubleWrapper::operator=(const double& d)
{
	d_ = d;
	return *this;
}

/*----< overload insertion operator for std::string properties >---*/

std::ostream& operator<<(std::ostream& out, Property<DoubleWrapper>& p)
{
	DoubleWrapper temp = p.getValue();
	try {
		out << static_cast<double>(temp);
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  exception:\n  " << ex.what() << "\n";
	}
	return out;
}

//----< saves instance state as XML string >-------------------------

inline DoubleWrapper::Xml DoubleWrapper::save()
{
	return "<DoubleWrapper>" + Convert<double>::toString(d_) + "</DoubleWrapper>";
}
inline DoubleWrapper DoubleWrapper::fromXml(std::string xml)
{
	using SPtr = std::shared_ptr<AbstractXmlElement>;
	XmlDocument doc(xml, XmlDocument::str);
	std::vector<SPtr> desc = doc.descendents("DoubleWrapper").select();
	if (desc[0]->children().size() > 0) {
		std::string value = desc[0]->children()[0]->value();
		value = trim(value);
		double d = Convert<double>::fromString(value);
		return DoubleWrapper(d);
	}
	return NULL;
}
//---< restores instance state from XML string >---------------------

inline void DoubleWrapper::restore(const Xml& xml)
{
	size_t posStart = xml.find_first_of(">") + 1;
	size_t posEnd = xml.find_last_of("</");
	std::string bodyString = xml.substr(posStart, posEnd - posStart - 1);
	d_ = Convert<double>::fromString(bodyString);
}
//----< cast operator returns double member >------------------------

inline DoubleWrapper::operator double()
{
	return d_;
}