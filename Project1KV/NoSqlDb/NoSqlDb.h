#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  NoSqlDb.h defines two classes that are used in populating and calling important function in our database//
//                                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Package operation:
------------------
1. Defines two classes of template type namely : Element and NoSqlDb.
2. Element class is used to create individual elements of the database.
3. NoSqlDb class is used to add these individual elements to an unordered map using a save function.
4. These two classes together foem our data base.

*/
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../CppProperties/CppProperties.h"
#include<ctime>
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"

#include "../StrHelper.h"
using StrData = std::string;
/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair

template<typename Data>
class Element
{
public:
	using Name = std::string;
	using Category = std::string;
	using Description = std::string;
	using TimeDate = std::string;
	using Children = std::string;
	Property<Name> name;            // metadata
	Property<Category> category;    // metadata
	Property<TimeDate> timeDate;    // metadata

	Property<Data> data;            // data

	std::vector<Children> child;		//child data


	std::string show();
};


template<typename Data>
std::string Element<Data>::show()
{


	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out << "\n    " << std::setw(8) << "name" << " : " << name;
	out << "\n    " << std::setw(8) << "category" << " : " << category;

	out << "\n    " << std::setw(8) << "data" << " : " << data;
	for (unsigned int i = 0; i < child.size(); ++i)
	{
		out << "\n    " << std::setw(8) << "child" << i + 1 << " : " << child.at(i);//showing children

	}
	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;



	out << "\n";
	return out.str();
}

/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements

template<typename Data>
class NoSqlDb
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;

	Keys keys();
	bool save(Key key, Element<Data> elem);
	void del(Key key);
	void update(Key key, Element<Data> &c);
	void NoSqlDb <Data> ::updatemeta(Key key, std::string b, std::string c, std::vector<std::string> children);
	void addChild(Key key, std::string a);//addition of child to any key value
	void databasetoXml(NoSqlDb<StrData> x);//persistence function that links toxml and fromxml
	std::string NoSqlDb<Data>::toxml(Keys keys, NoSqlDb <Data> x);
	Element<Data> NoSqlDb<Data>::fromxml(const std::string& xml, int i);
	std::string NoSqlDb<Data>::toxml2();//used for demonstrating requirement 10
	Element<Data> value(Key key);
	size_t count();
private:
	using Item = std::pair<Key, Element<Data>>;

	std::unordered_map<Key, Element<Data>> store;
};

template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
	Keys keys;


	for (Item item : store)
	{
		keys.push_back(item.first);
	}
	return keys; //returns a vector of keys
}

template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)//save functionality to store key/value pairs
{
	if (store.find(key) != store.end())
		return false;
	store[key] = elem;
	return true;
}

template<typename Data>
void NoSqlDb<Data> ::del(Key key)
{
	store.erase(key);
	std::cout << "\"" << key << "\"" << " deleted\n ";//deleting any value by taking its key as input

}



template<typename Data>
void NoSqlDb <Data> ::update(Key key, Element <Data> &c)
{
	if (store.find(key) != store.end())
		store[key] = c;

	else
		std::cout << "error";

}

template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return Element<Data>();
}
template<typename Data>
size_t NoSqlDb<Data>::count()
{
	return store.size();
}

template<typename Data>
void NoSqlDb <Data> ::updatemeta(Key key, std::string b, std::string c, std::vector<std::string> children)
{
	store[key].category = b;
	store[key].data = c;
	store[key].child = children;
	std::cout << key << " metadata updated\n\n";
}



template <typename Data>
void NoSqlDb<Data>::addChild(Key key, std::string a) {


	store[key].child.push_back(a);
	std::cout << "Child added to " << key;
}

template <typename Data>
void NoSqlDb<Data>::databasetoXml(NoSqlDb<StrData> x) {
	using namespace XmlProcessing;

	Keys keys = x.keys();
	std::string xml = x.toxml(keys, x);
	std::ofstream myfile;
	myfile.open("Project1.xml");
	myfile << xml;
	myfile.close();
	std::cout << "\n  DataBase xml string:" << xml << std::endl;

	std::cout << "\n Retrieving Data from XML file : \n";

	for (unsigned int k = 0; k < keys.size(); ++k) {
		Element<StrData> y = x.fromxml(xml, k);
		std::cout << std::endl << keys.at(k) << y.show();
	}
}
template<typename Data>
std::string NoSqlDb<Data>::toxml(Keys keys, NoSqlDb<Data> x)
{

	using namespace XmlProcessing;
	using Sptr = std::shared_ptr<AbstractXmlElement>;
	std::string xml;
	XmlDocument doc;
	Sptr pRoot = makeTaggedElement("NoSqlDb");
	doc.docElement() = pRoot;

	for (unsigned int i = 0; i < keys.size(); ++i)
	{

		Sptr pKeyElem = makeTaggedElement("key");
		pRoot->addChild(pKeyElem);
		Sptr pkElem = makeTextElement(keys.at(i));
		pKeyElem->addChild(pkElem);



		Sptr pNameElem = makeTaggedElement("Name");
		pRoot->addChild(pNameElem);
		Sptr pTextElem = makeTextElement(value(keys.at(i)).name);
		pNameElem->addChild(pTextElem);

		Sptr pCategoryElem = makeTaggedElement("Category");
		pRoot->addChild(pCategoryElem);
		Sptr pcatElem = makeTextElement(value(keys.at(i)).category);
		pCategoryElem->addChild(pcatElem);

		Sptr pDataElem = makeTaggedElement("Data");
		pRoot->addChild(pDataElem);
		Sptr pdataelem = makeTextElement(value(keys.at(i)).data);
		pDataElem->addChild(pdataelem);

		Sptr pTimeDateElem = makeTaggedElement("Time Date");
		pRoot->addChild(pTimeDateElem);
		Sptr pdatetimeelem = makeTextElement(value(keys.at(i)).timeDate);
		pTimeDateElem->addChild(pdatetimeelem);

		Sptr pChildren = makeTaggedElement("Children");
		pRoot->addChild(pChildren);


		for (unsigned int m = 0; m < value(keys.at(i)).child.size(); ++m)
		{
			Sptr pchild = makeTextElement(value(keys.at(i)).child.at(m));
			pChildren->addChild(pchild);
		}


	}
	xml = doc.toString();
	return xml;
}
template<typename Data>
Element<Data> NoSqlDb<Data>::fromxml(const std::string & xml, int i)
{
	using namespace XmlProcessing;
	using Sptr = std::shared_ptr<AbstractXmlElement>;
	Element<StrData> elementsfromxml;
	XmlDocument doc(xml, XmlDocument::str);
	std::vector<Sptr> desc = doc.descendents("Name").select();
	size_t size = desc.size();
	std::string name_value = desc[i]->children()[0]->value();
	name_value = trim(name_value);
	elementsfromxml.name = name_value;

	desc = doc.descendents("Category").select();
	std::string cat;
	cat = desc[i]->children()[0]->value();
	elementsfromxml.category = cat;
	desc = doc.descendents("Data").select();
	std::string data;
	data = desc[i]->children()[0]->value();
	elementsfromxml.data = data;


	desc = doc.descendents("Children").select();
	std::string child;
	child = desc[i]->children()[0]->value();

	std::string child1, child2;

	std::string::size_type pos = child.find(' ');

	if (child.npos != pos) {
		child1 = child.substr(0, pos);
		child2 = child.substr(pos + 1);
	}

	child1 = trim(child1);
	child2 = trim(child2);

	elementsfromxml.child.push_back(child1);

	elementsfromxml.child.push_back(child1);

	elementsfromxml.child.push_back(child2);

	return  elementsfromxml;

}


template<typename Data>
std::string NoSqlDb<Data>::toxml2()
{

using namespace XmlProcessing;
using Sptr = std::shared_ptr<AbstractXmlElement>;
std::string xml;
XmlDocument doc;
Sptr pRoot = makeTaggedElement("KeyValue");
doc.docElement() = pRoot;



Sptr pKeyElem = makeTaggedElement("CppProperties");
pRoot->addChild(pKeyElem);
Sptr pkElem = makeTextElement("CppProperties.cpp, CppProperties.h");
pKeyElem->addChild(pkElem);



Sptr pNameElem = makeTaggedElement("NoSqlDb");
pRoot->addChild(pNameElem);
Sptr pTextElem = makeTextElement("NoSqlDb.h, query.h, NoSqlDb.cpp");
pNameElem->addChild(pTextElem);

Sptr pCategoryElem = makeTaggedElement("query");
pRoot->addChild(pCategoryElem);
Sptr pcatElem = makeTextElement("CppProperties.h, NoSqlDb.h, query.h, Query.cpp");
pCategoryElem->addChild(pcatElem);

Sptr pDataElem = makeTaggedElement("TestExecutive");
pRoot->addChild(pDataElem);
Sptr pdataelem = makeTextElement("NoSqlDb.h,query.h, TestExecutivecpp.cpp");
pDataElem->addChild(pdataelem);

Sptr pTimeDateElem = makeTaggedElement("Utilities");
pRoot->addChild(pTimeDateElem);
Sptr pdatetimeelem = makeTextElement("Utilities.h, Utilities.cpp");
pTimeDateElem->addChild(pdatetimeelem);

Sptr pChildren = makeTaggedElement("XmlDocument");
pRoot->addChild(pChildren);
Sptr pchildelem = makeTextElement("XmlDocument.h, XmlElement.h, XmlDocument.coo, XmlElement.cpp");


xml = doc.toString();
return xml;
}










