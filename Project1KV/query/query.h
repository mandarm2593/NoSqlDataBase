#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////
//    query.h implements a query class that has query related functions which are accessed in //   
//    main testexecutive.                                                                     //
//                                                                                            //
//                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////


/*
Package Description:
--------------------
1. implements a query class whose methods can be accessed in our test executive.
2. all query functionalities are implemented according to the project requirements.

*/
#include "../NoSqlDb/NoSqlDb.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <vector>
#include "../CppProperties/CppProperties.h"
#include <fstream>
#include <algorithm>
//#include "../Demo/Help.h";
//#include "../XmlDocument/XmlDocument/XmlDocument.h"
//#include "../Demo/Help.cpp"
using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;
using namespace XmlProcessing;
template<typename data>
class query {

public:

	void keypattern(NoSqlDb<StrData> x, char y) {
		std::vector<std::string> keys = x.keys();
		std::cout << "All keys starting with " << y << " : ";
		for (unsigned int i = 0; i < keys.size(); ++i)
		{
			std::string m = keys.at(i);
			if (m.at(0) == y) {
				std::cout << m;
				std::cout << ", ";

			}
		}
	}

	std::vector<std::string> viewallKeys(NoSqlDb<StrData> x) {
		std::cout << "The set of all Keys is : ";
		std::vector < std::string > setofkeys = x.keys();
		for (unsigned int z = 0; z < setofkeys.size(); ++z) {
			std::cout << setofkeys.at(z) << ", ";
		}
		return setofkeys;
	}

	void EarlierQuery(std::vector<std::string> SetofKeys, NoSqlDb<StrData> &x)
	{
		std::cout << "Value of the keys returned by the previous query(from requirement 7.5 - \n";
		for (unsigned int k = 0; k < SetofKeys.size(); ++k)
		{
			std::string s = SetofKeys.at(k);
			std::cout << s;
			std::cout << x.value(s).show();
		}
	}

	std::vector<std::string> specifiedstringinName(NoSqlDb<StrData> &x, std::string pattern) {
		std::vector<std::string> keyvector = x.keys();
		std::vector<std::string> ssn;
		for (unsigned int i = 0; i < keyvector.size(); ++i) {
			if ((std::string) x.value(keyvector.at(i)).name == pattern)
			{
				std::cout << keyvector.at(i) << " contains " << "\"" << pattern << "\"" << " in its Name \n";
				ssn.push_back(keyvector.at(i));
			}
		}

		return  ssn;
	}

	std::vector<std::string> specifiedstringinCategory(NoSqlDb<StrData> &x, std::string pattern) {
		std::vector<std::string> keyvector = x.keys();
		std::vector<std::string> ssc;
		for (unsigned int i = 0; i < keyvector.size(); ++i) {

			if ((std::string) x.value(keyvector.at(i)).category == pattern)
			{
				std::cout << keyvector.at(i) << " contains " << "\"" << pattern << "\"" << " in its Category \n";
				ssc.push_back(keyvector.at(i));
			}

		}

		return ssc;
	}
	std::vector<std::string> specifiedstringinData(NoSqlDb<StrData> &x, std::string pattern) {
		std::vector<std::string> keyvector = x.keys();
		std::vector<std::string> ssd;

		for (unsigned int i = 0; i < keyvector.size(); ++i) {
			if ((std::string) x.value(keyvector.at(i)).data == pattern)
			{
				std::cout << keyvector.at(i) << " contains " << "\"" << pattern << "\"" << " in its Data \n";
				ssd.push_back(keyvector.at(i));
			}

		}
		return ssd;
	}


	

	void addnewElem(NoSqlDb<StrData> &x, StrData name, StrData category, StrData data, std::vector<StrData> childnames) {
		using namespace XmlProcessing;
		//persist<StrData> p;

		static int i = 0;
		Keys keys = x.keys();
		Element<StrData> Elemadd;

		Elemadd.name = name;
		Elemadd.category = category;
		Elemadd.data = data;
		time_t now = time(0);
		struct tm * curtime = localtime(&now);
		Elemadd.timeDate = asctime(curtime);
		Elemadd.child = childnames;
		x.save(Elemadd.name, Elemadd);

		++i;
		x.save(Elemadd.name, Elemadd);
		std::cout << "New key/value pair added\n";
		if (i % 3 == 0)
		{
			std::cout << "Data being persisted............\n";
			x.databasetoXml(x);
			
			//x.toxml(keys, x);
		}
	}
	void showValue(NoSqlDb < StrData> &x, std::vector<std::string> KEY, StrData keyenter) {


		for (unsigned int i = 0; i < KEY.size(); ++i)
		{
			if (keyenter == KEY.at(i)) {
				std::string k = KEY.at(i);
				std::cout << "The value of key - " << k << " is " << x.value(k).show();
			}
		}
	}

	void showChildren(NoSqlDb<StrData> &x, StrData Keyenter) {
		std::cout << "The children/child of " << Keyenter << " : \n";
		for (unsigned int i = 0; i < x.value(Keyenter).child.size(); ++i)
		{
			std::cout << "Child" << i + 1 << " : " << x.value(Keyenter).child.at(i) << std::endl;
		}

	}

	void keysUnion(std::vector<std::string> x, std::vector<std::string> y) {

		std::cout << "\n Union of keys returned by queries, specific string in category and specific string in data\n";
		std::vector<std::string> Union, v;
		std::sort(x.begin(), x.end());
		std::sort(y.begin(), y.end());
		std::vector<std::string> c(x.size() * 2);
		std::vector<std::string>::iterator it = set_union(x.begin(), x.end(), y.begin(), y.end(), c.begin());
		c.resize(it - c.begin());
		for (unsigned int i = 0; i < c.size(); ++i) {

			std::cout << c.at(i) << "\n";
		}
	}
	void showDB(NoSqlDb<StrData> &x)
	{

		std::vector<std::string> keys = x.keys();
		std::cout << "Size of the DataBase : " << keys.size() << std::endl;
		for (unsigned int i = 0; i < keys.size(); ++i) {

			std::cout << keys.at(i) << x.value(keys.at(i)).show() << std::endl;
		}

	}

	void allQueries(NoSqlDb<StrData> &x) {
		std::vector<std::string> keys = x.keys();
		std::cout << "---------------------Demonstrating requirement 7--------------------------\n";
		std::cout << "Showing all keys - ";
		viewallKeys(x);
		std::cout << "\n7.1 - The Value of a specified key - \n";
		showValue(x, keys, "Mark");
		std::cout << "7.2 - The Children of a specified key - \n";
		showChildren(x, "Jane");
		std::cout << "7.3 - A set of keys matching a specified pattern - \n";
		keypattern(x, 'M');
		std::cout << "\n7.4 - All keys that contain a specfied string in their item name - \n";
		specifiedstringinName(x, "Andrew");
		std::cout << "7.5 - All keys that contain a specified string in their category - \n";
		std::vector<std::string> setofkeys = specifiedstringinCategory(x, "Graduate");
		std::cout << "7.6 - All keys that contain a specified string in their Data - \n";
		std::vector<std::string> setofkeys2 = specifiedstringinData(x, "Computer Engineering");
		std::cout << "----------------Requirement 8 - Queries on a set of keys returned by an earlier query ----------- \n";
		EarlierQuery(setofkeys, x);
		std::cout << "-------Requirement 9-----Union of keys returned by 7.5 and 7.6--------------";
		keysUnion(setofkeys, setofkeys2);

	}






};