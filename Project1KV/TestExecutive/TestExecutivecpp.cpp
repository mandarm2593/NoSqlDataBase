#include "../NoSqlDb/NoSqlDb.h"
#include "../query/query.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include<string>

int main()
{
	NoSqlDb<StrData> db;
	Element<StrData> elem1,elem2,elem3;
	elem1.name = "Mandar";//populating our database with initial values
	elem1.category = " Graduate";
	elem1.data = "Computer Engineering";
	elem1.child.push_back("Shantanu");
	time_t now = time(0);
	struct tm * curtime = localtime(&now);
	elem1.timeDate = asctime(curtime);
	db.save(elem1.name, elem1);
	elem2.name = "Mark";
	elem2.category = "Graduate";
	elem2.data = "Biomedical";
	elem2.child.push_back("John");
	elem2.timeDate = asctime(curtime);
	db.save(elem2.name, elem2);
	elem3.name = "John";
	elem3.category = "Graduate";
	elem3.data = "Mechanical Engineering";
	elem3.child.push_back("Jane");
	elem3.timeDate = asctime(curtime);
	db.save(elem3.name, elem3);
	query<StrData> q;
	std::cout << "\n===============================Demonstrating Test executive===========================================\n";
	std::cout << "-----------------Requirement 2-------------------\n \n";
	q.showDB(db);
	std::cout << "-------------------Requirement 3-------------------\n\n";
	std::vector<StrData> childnames1{ "Mark" };
	q.addnewElem(db, "Tom", "Graduate", "Mechanical Engg", childnames1);
	q.showDB(db);
	db.del("John");
	q.showDB(db);
	std::cout << "------------------Requirement 4------------------------\n\n";
	db.addChild("Mandar", "Tom");
	q.showDB(db);
	std::vector<StrData> children{ "John" };
	db.updatemeta("Mark", "Undergraduate", "Computer Engineering", children);
	q.showDB(db);
	std::cout << "-------------------------Requirement 5 and 6--------------------------\n\n";
	std::cout << "DataBase Contents are persisted in XML file for every 3 writes(1 write is already done as a part of requirement 3)\n";
	std::vector<std::string> childnames2{ "John","Mark" };
	q.addnewElem(db, "Andrew", "Undergraduate", "Electrical Engineering", childnames2);
	std::vector<std::string> childnames3{ "Mandar" };
	q.addnewElem(db, "Jane", "Graduate", "Computer Engineering", childnames3);
	q.allQueries(db);
	std::cout <<"---------------------Demonstrating Requirement 10------------------------\n"<< db.toxml2();
	getchar();
	return 0;
}