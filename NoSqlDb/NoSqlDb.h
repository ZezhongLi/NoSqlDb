#pragma once
/////////////////////////////////////////////////////////////////////////////////////
// NoSqlDb.h - NoSqlDb class is implementation of key/value pair in-memory database
// Ver 1.0                                                              
// Application: Project #1  key/value pair in-memory database            
// Language:    C++, Visual Studio 2015                                 
// Platform:    Macbook pro, Core-i7, Windows 10                 
// Author:      Zezhong Li, SUID:903800321                            
// Reference:   Jim Fawcett, CST 4-187, Syracuse University			    
//              (315) 443-3948, jfawcett@twcny.rr.com				    
/////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations :
*== == == == == == == == == == == == == == == =
* This package provides functionalites to 
*						build NoSqlDb instance, 
*						add, delete, edit elements
*						query Element<Data>, 
*						persist and restore to and from xml.
*
* Public Interface :
*== == == == == == == == == == == == == == ==
*	size_t count();
*	Keys keys();
*	Values values();
*	Element<Data> value(Key key);
*	std::unordered_set<Key> getChildrenByKey(Key key);
*	std::unordered_set<Key> keysWithPatternInElem(std::function<bool(Element<Data>)> pattern);
*	std::unordered_set<Key> keysWithPatternInKey(std::function<bool(std::string)> pattern);
*	std::unordered_set<Key> keysBetweenIntervals(std::string interval1, std::string interval2 = "*");
*	NoSqlDb<Data> subDbOfKeys(std::unordered_set<std::string> set);
*	std::unordered_set<Key> unionOfSets(std::vector<std::unordered_set<std::string>> vec);
*	bool save(Key key, Element<Data> elem);
*	bool add(Key key, Element<Data> elem);
*	void put(Key key, Element<Data> elem);
*	bool remove(Key key);
*	void clear();
*	void toXmlFile(std::string file);
*	static NoSqlDb<Data> fromXml(std::string src);
*
*
* Required Files :
*== == == == == == == == == == == == == ==
*	Element.h,	CppProperties.h
*	API in std library: <string>, <sstream>, <iomanip>, <iostream>,	<fstream>, <unordered_map>
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

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "../CppProperties/CppProperties.h"
#include "Element.h"


template<typename Data>
class NoSqlDb
{
public:
	/* Alias */
	using Key = std::string;
	using Keys = std::vector<Key>;
	using Values = std::list<Element<Data>>;

	size_t count();
	Keys keys();
	Values values();
	Element<Data> value(Key key);
	std::unordered_set<Key> getChildrenByKey(Key key);
	std::unordered_set<Key> keysWithPatternInElem(std::function<bool(Element<Data>)> pattern);
	std::unordered_set<Key> keysWithPatternInKey(std::function<bool(std::string)> pattern);
	std::unordered_set<Key> keysBetweenIntervals(std::string interval1, std::string interval2 = "*");
	NoSqlDb<Data> subDbOfKeys(std::unordered_set<std::string> set);
	std::unordered_set<Key> unionOfSets(std::vector<std::unordered_set<std::string>> vec);
	bool save(Key key, Element<Data> elem);
	bool add(Key key, Element<Data> elem);
	void put(Key key, Element<Data> elem);
	bool remove(Key key);
	void clear();
	void toXmlFile(std::string file);
	static NoSqlDb<Data> fromXml(std::string src);

private:
	/* key / value pair */
	using Item = std::pair<Key, Element<Data>>;
	/* actual data structure to store the elements */
	std::unordered_map<Key, Element<Data>> store;
};


/*
Description:	Return the number of element store in current NoSqlDb instance
Return Type:	size_t
*/
template<typename Data>
size_t NoSqlDb<Data>::count()
{
	return store.size();
}

/*
Description:	Return all the keys of the stored elements
Return type:	std::vector<std::string>
*/
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
	Keys keys;
	for (Item item : store)
	{
		keys.push_back(item.first);
	}
	return keys;
}

/*
Description:	Return all the elements stored
Return type:	std::list<Element<Data>>
*/
template<typename Data>
typename NoSqlDb<Data>::Values NoSqlDb<Data>::values()
{
	Values values;
	for (Item item : store)
	{
		values.push_back(item.second);
	}
	return values;
}


/*
Description:	Return element corresponding to specific key
Parameter:
	Key:	key of the element
Return type:	Element<Data>
*/
template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return Element<Data>();
}


/*
Description:	Return chilren's keys of an element's that corresponding to specific key
Parameter:
	key:	key of the element
Return type:	Element<Data>
*/
template<typename Data>
inline std::unordered_set<std::string> NoSqlDb<Data>::getChildrenByKey(Key key)
{
	auto elem = value(key);
	return elem.getChildren();;
}


/*
Description:	Take a functor of a specified pattern and return a set of keys of elements that follow the pattern.
Parameter:
	pattern:	A functor which takes in an Element<Data> instance and return a bool value
Return type:	std::unordered_set<std::string>
*/
template<typename Data>
inline std::unordered_set<std::string> NoSqlDb<Data>::keysWithPatternInElem(std::function<bool(Element<Data>)> pattern)
{
	std::unordered_set<std::string> set;
	for (auto key : keys()) {
		if (pattern(value(key))) {
			set.insert(key);
		}
	}
	return set;
}


/*
Description:	Take a functor of a specified pattern and return a set of keys of elements that follow the pattern.
				Checks keys in db to follow specified pattern.
Parameter:
	pattern:	A functor that takes in an std::string instance and return a bool value
Return type:	std::unordered_set<std::string>
*/
template<typename Data>
inline std::unordered_set<std::string> NoSqlDb<Data>::keysWithPatternInKey(std::function<bool(std::string)> pattern)
{
	std::unordered_set<std::string> set;
	for (auto key : keys()) {
		if (pattern(key)) {
			set.insert(key);
		}
	}
	return set;
}


/*
Description:	Takes two time stamp and return all the keys of elements that have TimeDate in between the two timestamp.
				If the second timestamp is not provided, current timestamp will be used.
Parameter:
	interval1:	The start timestamp
	interval2:	The end timestamp
Return type:	std::unordered_set<std::string>
*/
template<typename Data>
inline std::unordered_set<std::string> NoSqlDb<Data>::keysBetweenIntervals(std::string interval1, std::string interval2 = "*")
{
	if (interval2.compare("*") == 0) {
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &timeinfo);
		interval2 = buffer;
	}
	std::unordered_set<std::string> set;
	for (auto key : keys()) {
		Element<Data> elem = value(key);
		std::string time = elem.timeDate.getValue();
		bool one = time.compare(interval1) > 0;
		bool two = time.compare(interval2) < 0;
		if (one && two) {
			set.insert(key);
		}
	}
	return set;
}


/*
Description:	Takes a set of keys of elements exist in db and create a sub database for easier access.
				This is built for compound queries. Another query can be based on this result.
Parameter:
	set:	A set of key exist in current db instance.
Return type:	A new database instance which is a sub set of the original database.
*/
template<typename Data>
inline NoSqlDb<Data> NoSqlDb<Data>::subDbOfKeys(std::unordered_set<std::string> set)
{
	NoSqlDb<Data> db;
	for (auto key : set) {
		db.save(key, value(key));
	}
	return db;
}


/*
Description:	Takes a container of sets and make union of all sets in the container, and return the joined set.
Parameter:
	vec:	A vector stores one or more sets.
Return type:	A new set contains all the keys in the given sets.
*/
template<typename Data>
inline std::unordered_set<std::string> NoSqlDb<Data>::unionOfSets(std::vector<std::unordered_set<std::string>> vec)
{
	std::unordered_set<std::string> set;
	for (auto sub : vec) {
		set.insert(sub.begin(), sub.end());
	}
	return set;
}


/*
Description:	Save an pair with key / value. This method is for element already exist in db.
Parameter:
	key:	The key of the Element.
	elem:	The value part of key/value pair.
Return type:	A bool value represent the save state.
				True: succeed
				False: feil;
*/
template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
	if (store.find(key) != store.end())
		return false;
	store[key] = elem;
	return true;
}


/*
Description:	Save an pair with key / value. This method is more element not exist in db.
Parameter:
key:	The key of the Element.
elem:	The value part of key/value pair.
Return type:	A bool value represent the add state.
	True: succeed
	False: feil;
*/
template<typename Data>
bool NoSqlDb<Data>::add(Key key, Element<Data> elem)
{
	if (store.find(key) != store.end())
	{
		store[key] = elem;
		return true;
	}
	return false; // already exist, refuse to add
}


/*
Description:	Put an pair with key / value. If element exist in db, then edit the value.
				If element not in db, save it in db.
Parameter:
	key:	The key of the Element.
	elem:	The value part of key/value pair.
Return type:	A bool value represent the put state.
	True: succeed
	False: feil;
*/
template<typename Data>
void NoSqlDb<Data>::put(Key key, Element<Data> elem)
{
	if (!save(key, elem))
	{
		store[key] = elem;
	}
}


/*
Description:	Remove a key / value pair in database.
Parameter:
	key:	The key of the Element.
Return type:	A bool value represent the remove state.
	True: succeed
	False: feil;
*/
template<typename Data>
bool NoSqlDb<Data>::remove(Key key)
{
	if (store.find(key) != store.end())
	{
		store.erase(key);
		return true;
	}
	return false; // not found, refuse to remove
}


/*
Description:	Remove all the key / value pairs in database.
*/
template<typename Data>
void NoSqlDb<Data>::clear()
{
	store.clear();
}

/*
Description:	Write All key / value pairs in database to a file provided by user with the format of xml.
Parameter:
	file:	The name of the file.
*/
template<typename Data>
inline void NoSqlDb<Data>::toXmlFile(std::string file)
{
	//std::string exName = typeid(Data()).name();
	//exName.append("-");
	//exName.append(file);
	std::fstream datafile(file, std::ios::out);
	datafile << "\n<NoSqlDb>";
	std::string keyTypeName = typeid(std::string).name();
	std::string dataTypeName = typeid(Data).name();
	datafile << "\n<KeyType>" << keyTypeName << "</KeyType>";
	datafile << "\n<DataType>" << dataTypeName << "</DataType>";
	auto ks = keys();
	for (auto key : ks)
	{
		datafile << "\n	<Key>" << key << "</Key>";
		datafile << value(key).toXml() << std::endl;
	}
	datafile << "\n</NoSqlDb>";
	datafile.close();
}


/*
Description:	Restore database from a xml file
Parameter:
	src:	The xml file name.
Return type:	A database instance.
*/
template<typename Data>
inline NoSqlDb<Data> NoSqlDb<Data>::fromXml(std::string src) 
{
	NoSqlDb<Data> db;
	XmlParser parser(src);
	parser.verbose();
	XmlDocument* pDoc = parser.buildDocument();
	std::vector<SPtr> descKeys = pDoc->descendents("Key").select();
	std::vector<SPtr> descElems = pDoc->descendents("Element").select();

	for (unsigned int i = 0; i < descElems.size(); i++)
	{
		std::string elem_key = descKeys[i]->children()[0]->value();
		std::string elem_string = descElems[i]->toString();
		Element<Data> newElem = Element<Data>::fromXml(elem_string);
		db.save(elem_key, newElem);
	}

	return db;
}



