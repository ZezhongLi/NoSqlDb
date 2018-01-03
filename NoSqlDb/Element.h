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
* Package Operations :
*== == == == == == == == == == == == == == == =
* This package provides functionalites to
*						build Element<Data> instance,
*						Edit of meta datas,
*						show current istance as string, and xml format.
*
* Public Interface :
*== == == == == == == == == == == == == == ==
*
*	Properties
*
*	Property<Name> name;					    // metadata
*	Property<Category> category;			    // metadata
*	Property<TimeDate> timeDate;			    // metadata
*	Property<Description> description;			// metadata
*	Property<Data> data;                        // data
*
*	std::string show();
*	std::string toXml();
*	static Element<Data> fromXml(std::string xml);
*	bool addChildByKey(std::string);
*	bool removeChildByKey(std::string);
*	std::unordered_set<Key> getChildren();
*
*
*
* Required Files :
*== == == == == == == == == == == == == ==
*	XmlDocument.h, XmlElement.h, Convert.h, CppProperties.h
*	API in std library: <iomanip>, <unordered_set>
*
* Build Command :
*== == == == == == == == == == == == == ==
* devenv NoSqlDb.sln / rebuild debug
*
* Maintenance History :
*== == == == == == == == == == == == == ==
* ver 1.0 : 08 Feb 17
* -first release
*/
#include <unordered_set>
#include <iomanip>
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../Serialize/Convert.h"
#include "../CppProperties/CppProperties.h"

/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair
// - it needs to store child data, something for you to implement
//
template<typename Data>
class Element
{
public:
	/* Alias */
	using Key = std::string;
	using Name = std::string;
	using Category = std::string;
	using TimeDate = std::string;
	using Description = std::string;
	using Children = std::unordered_set<Key>;

	/* Properties */
	Property<Name> name;					    // metadata
	Property<Category> category;			    // metadata
	Property<TimeDate> timeDate;			    // metadata
	Property<Description> description;			// metadata
	Property<Data> data;                        // data

	/* Operations */
	std::string show();
	std::string toXml();
	static Element<Data> fromXml(std::string xml);
	bool addChildByKey(std::string);
	bool removeChildByKey(std::string);
	std::unordered_set<Key> getChildren();
private:
	std::unordered_set<Key> children;							// relationships
};


/*
Description:	Describe current element with an std::string instance.
Return type:	std::string - The description of this instance.
*/
template<typename Data>
std::string Element<Data>::show()
{

	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out << "\n    " << std::setw(11) << "name" << " : " << name;
	out << "\n    " << std::setw(11) << "category" << " : " << category;
	out << "\n    " << std::setw(11) << "timeDate" << " : " << timeDate;
	out << "\n    " << std::setw(11) << "description" << " : " << description << std::endl;
	out << "\n    " << std::setw(11) << "data" << " : " << data << std::endl;
	int i = 0;
	out << "\n    " << std::setw(11) << "children's key" << " : ";
	if (children.size() == 0) {
		out << "\n		no children";
	}
	else {
		for (auto akey : children)
		{
			++i;
			out << "\n		" << "child " << i << " : " << akey;
		}
	}
	out << "\n";
	return out.str();
}

/*
Description:	Describe current element with xml string
Return type:	std::string - The description of this instance.
*/
template<typename Data>
std::string Element<Data>::toXml()
{
	using namespace XmlProcessing;
	using SPtr = std::shared_ptr<AbstractXmlElement>;

	std::string xml;
	XmlDocument doc;
	SPtr pRoot = makeTaggedElement("Element");
	doc.docElement() = pRoot;

	// make Property<Name> name element and add to root
	SPtr pNameElem = makeTaggedElement("Name");
	pRoot->addChild(pNameElem);
	SPtr pTextElem = makeTextElement(name);
	pNameElem->addChild(pTextElem);

	// make Property<Category> category element and add to root
	SPtr pCategoryElem = makeTaggedElement("Category");
	pRoot->addChild(pCategoryElem);
	pTextElem = makeTextElement(category);
	pCategoryElem->addChild(pTextElem);

	// make Property<TimeDate> timeDate element and add to root
	SPtr pTimeElem = makeTaggedElement("TimeDate");
	pRoot->addChild(pTimeElem);
	pTextElem = makeTextElement(timeDate);
	pTimeElem->addChild(pTextElem);

	// make Property<Description> description element and add to root
	SPtr pDescriptionElem = makeTaggedElement("Description");
	pRoot->addChild(pDescriptionElem);
	pTextElem = makeTextElement(description);
	pDescriptionElem->addChild(pTextElem);

	// make Property<Data> data element and add to root
	SPtr pDataElem = makeTaggedElement("Data");
	pRoot->addChild(pDataElem);
	pTextElem = makeTextElement(data.getValue().save());
	pDataElem->addChild(pTextElem);

	// make Property<Children> children element and add to root
	SPtr pChildrenElem = makeTaggedElement("Children");
	pRoot->addChild(pChildrenElem);
	for (auto akey : children)
	{
		SPtr pChildElem = makeTaggedElement("Child Key");
		pTextElem = makeTextElement(akey);
		pChildElem->addChild(pTextElem);
		pChildrenElem->addChild(pChildElem);
	}

	xml = doc.toString();
	return xml;
}

/*
Description:	Restore an Element from xml string.
Return type:	Element<Data> - An instance of Element<Data>
*/
template<typename Data>
inline Element<Data> Element<Data>::fromXml(std::string xml) {
	using SPtr = std::shared_ptr<AbstractXmlElement>;
	Element<Data> newElem;
	try {
		XmlDocument doc(xml, XmlDocument::str);
		std::vector<std::string> tags = {"Name", "Category", "TimeDate" , "Description" , "Data" , "Children" };
		for (auto tag : tags) {
			std::vector<SPtr> desc = doc.descendents(tag).select();
			std::string value = "";
			if (desc[0]->children().size() > 0) {
				if (tag.compare("Data") == 0 || tag.compare("Children") == 0) {
					value = desc[0]->toString();
				}
				else {
					value = desc[0]->children()[0]->value();
					value = trim(value);
				}
			}
			if (tag.compare("Name") == 0) { newElem.name = value; }
			else if (tag.compare("Category") == 0) {  newElem.category = value; }
			else if (tag.compare("TimeDate") == 0) {  newElem.timeDate = value; }
			else if (tag.compare("Description") == 0) { newElem.description = value; }
			else if (tag.compare("Data") == 0) {
				Data d = Data::fromXml(value);
				newElem.data = d;
			}
			else if (tag.compare("Children") == 0) {
				XmlDocument childrenDoc(value, XmlDocument::str);
				std::vector<SPtr> rootDesc = childrenDoc.descendents("Child").select();
				//std::vector<SPtr> cdesc = rootDesc[0]->descendents("Child Key").select();
				for (auto ch : rootDesc) {
					if (ch->children().size() > 0) {
						std::string ckey = ch->children()[0]->value();
						ckey = trim(ckey);
						newElem.addChildByKey(ckey);
					}
				}
			}
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "\n xml document problem in Element.h";
		std::cout << "\n " << ex.what();
	}
	return newElem;
}


/*
Description:	Add an key as a child of current element.
Return type:	bool - indicate wether the key is inserted successfully
*/
template<typename Data>
inline bool Element<Data>::addChildByKey(std::string cKey)
{
	if (children.count(cKey) == 0)
	{
		children.insert(cKey);
		return true;
	}
	return false;
}

/*
Description:	Remove a child key in children of current element.
Return type:	bool - indicate wether the key has been removed.
*/
template<typename Data>
inline bool Element<Data>::removeChildByKey(std::string cKey)
{
	if (children.count(cKey) == 0)
	{
		return false;
	}
	children.erase(cKey);
	return true;
}

/*
Description:	Get all the keys of children element of the element.
Return type:	std::unordered_set - all the keys of the element.
*/
template<typename Data>
std::unordered_set<std::string> Element<Data>::getChildren()
{
	return children;
}

