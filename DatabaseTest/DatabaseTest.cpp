// DatabaseTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#using <mscorlib.dll>
#using <System.Data.dll>
#using <System.dll>

using std::string;
using namespace System;
using namespace System::Data;
using namespace System::Data::OleDb;
using namespace System::Collections::Generic;

int main() {

	OleDbConnection^ conn = nullptr;
	OleDbCommand^ cmd = nullptr;

	try {
		conn = gcnew OleDbConnection("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\Users\\Bart\\Documents\\Access\\ProfsrFinancial.accdb");
		conn->Open();

		array<Object^>^ emptyRestrictions{};

		DataTable^ dt_tables = conn->GetOleDbSchemaTable(OleDbSchemaGuid::Tables, emptyRestrictions);
		DataTable^ dt2 = conn->GetOleDbSchemaTable(OleDbSchemaGuid::Foreign_Keys, emptyRestrictions);

		conn->Close();

		Console::WriteLine("Tables: \n");

		List<String^>^ tables = gcnew List<String^>();

		int tablesCount = dt_tables->Rows->Count;

		for (int i = 0; i < tablesCount; i++) {
			DataRow^ dr = dt_tables->Rows[i];
			if (dr[3]->ToString() == "TABLE") {
				tables->Add(dr[2]->ToString());
			}
		}

		for (int i = 0; i< tables->Count; i++) {
			Console::WriteLine(tables[i]);
		}

		Console::WriteLine("\n\nRelations: \n");
		for (int i = 0; i < dt2->Rows->Count; i++) {
			DataRow^ dr2 = dt2->Rows[i];	
			String^ t1 = dr2[2]->ToString();
			String^ t2 = dr2[8]->ToString();

			if (tables->Contains(t1) && tables->Contains(t2)) {
				Console::WriteLine(dr2[2]->ToString() + " - - - " + dr2[8]->ToString());
			}					
		}
		
	} catch (Exception^ ex) {
		Console::WriteLine(ex->ToString());
	}

	Console::ReadLine();
	return 0;
}

