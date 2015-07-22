#pragma once

#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 )

#define SCHEMA_REVISION "11"

#include <string>

#include <memory>
using std::shared_ptr;
using std::unique_ptr;
#include <cstdlib>  // std::exit
#include <iostream>

#include <odb/database.hxx>
#include <odb/connection.hxx>
#include <odb/sqlite/connection.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/sqlite/exceptions.hxx> 
#include <sqlite3.h>

#include <iostream>
#include <fstream>

using std::vector;
using std::string;
using std::cout;
using std::ifstream;

template <class DBPtrType>

inline DBPtrType open_sqlite_database(const std::string& name)
{
	using namespace polaris::io;
	DBPtrType db(new odb::sqlite::database (make_name(name, db_inventory[0]), SQLITE_OPEN_READWRITE));	

	odb::connection_ptr c (db->connection ());
	//c->execute("PRAGMA synchronous = OFF");
	//c->execute("PRAGMA journal_mode = MEMORY");
	ifstream test;
	if (db_inventory.size()>1)
	{
		for (std::vector<string>::iterator it = db_inventory.begin()+1; it != db_inventory.end(); ++it)
		{
			test.open(make_name(name, *it).c_str());
			if(test.is_open())
			{
				test.close();
				c->execute(make_attach_string(name,*it));
			}
			test.close();			
		}
	}
	return db;
}