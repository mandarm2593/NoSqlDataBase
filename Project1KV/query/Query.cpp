#include "../query/query.h"
#include "../NoSqlDb/NoSqlDb.h"
#include "../CppProperties/CppProperties.h"
#include <iostream>

#ifdef TEST_QUERY



int main()
{
	Element<StrData> elem1, elem2;
	NoSqlDb<StrData> db;
	query<StrData> q;
	elem1.name = "Mandar";
	elem1.category = "UnderGrad";
	elem1.data = "CE";
	time_t now = time(0);
	struct tm * curtime = localtime(&now);
	elem1.timeDate = asctime(curtime);
	elem2.name = "Mark";
	elem2.category = "Grad";
	elem2.data = "EE";
	elem2.child.push_back("Mandar");
	elem1.child.push_back("John");
	std::cout << "-----------------------------Test Stub-----------------------";
	db.save(elem1.name, elem1);
	db.save(elem2.name, elem2);	
	std::cout << "-------------------------Testing keypattern function---------------";
	q.keypattern(db, 'M');
	std::cout << "-------------------Testing viewallkeys function----------------";
	q.viewallKeys(db);
	std::cout << "-----------------------Testing Earlierquery function-----------------";
	q.EarlierQuery({ "Mandar","Mark" }, db);
	std::cout << "----------------------------Testing Specified string in name funstion--------------------";
	q.specifiedstringinName(db, "Mandar");
	std::cout << "-----------------------testing Specified string in category function-----------------------";
	q.specifiedstringinCategory(db, "Grad");
	std::cout << "-----------------------------testing specified string in data function---------------------";
	q.specifiedstringinData(db, "CE");
	std::cout << "-------------------------------testing add new element function----------------------";
	//this function basically combines the addition of an element in DB, to XMl and fromXml functions
	q.addnewElem(db, "jane", "Grad", "CE", { "Mandar","Mark" });
	std::cout << "--------------------testing show value function-----------------";
	q.showValue(db, db.keys(), "Mandar");
	std::cout << "------------------------testing show children function------------------------";
	q.showChildren(db, "Mark");
	std::cout << "------------------------------testing keys union function--------------------" ;
	q.keysUnion({ "Mandar","John" }, { "Mandar","Jane","Mark" });
	std::cout << "---------------------testing view all queries function---------------------";
	q.allQueries(db);//this function is basically a combination of all above functions into one that is used in the main test executive




}

#endif