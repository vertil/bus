// Bus_stop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "trip.h"
using namespace std;


int main()
{
	vector<trip> Posh;
	vector<trip> Grotty;

	ifstream openBus("original.txt", std::ios::out);
	char buff[50];
	string buffs;
	trip bufft;
	string end= "<end - of - file>";
	for (;;) {
		openBus.getline(buff, 50);
		buffs = string(buff);

		if (buffs[0]=='<') break;
		
		if (buffs[0] == 'P') {
			
			bufft.startHour = atoi(buffs.substr(5,6).c_str());
			bufft.startMin = atoi(buffs.substr(8, 9).c_str());

			
			bufft.endHour = atoi(buffs.substr(11, 12).c_str());
			bufft.endMin = atoi(buffs.substr(14, 15).c_str());

			bufft.calTotalTime();
			Posh.push_back(bufft);
		}

		if (buffs[0] == 'G') {

			bufft.startHour = atoi(buffs.substr(7, 8).c_str());
			bufft.startMin = atoi(buffs.substr(10, 11).c_str());


			bufft.endHour = atoi(buffs.substr(13, 14).c_str());
			bufft.endMin = atoi(buffs.substr(16, 17).c_str());

			bufft.calTotalTime();
			Grotty.push_back(bufft);
		}

		
	} //парсим
	//пропарсили
	openBus.close();
	for (auto it = Posh.begin(); it != Posh.end(); ) {  //удаляем маршруты от поша от часа и дольше
		if (it->totalTime > 59) {
			it = Posh.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto it = Grotty.begin(); it != Grotty.end(); ) { //удаляем маршруты от гроти от часа и дольше
		if (it->totalTime>59) {
			it = Grotty.erase(it);
		}
		else {
			++it;
		}
	}	
	/*for (auto it = Posh.begin(); it != Posh.end(); ) {
		for (auto at = Grotty.begin(); at != Grotty.end(); ) {
			if (it == at) {
				at = Grotty.erase(at);
			}
			else {
				++at;
			}
		}
	}*/
	vector<int> indexx;
	vector<int> PoshI;
	vector<int> GrottyI;
	//----------------------------------------------------------
	for (int i = 0; i < Posh.size(); ++i) {  //находим одинаковые , 
		for (int j = 0; j < Grotty.size(); ++j) {
			if (Posh[i] == Grotty[j]) {
				indexx.push_back(j);
			}			
		}
	}


	for (auto i : indexx) {  //и удаляем из гроттит, т.к. у них хуже автобусы
		Grotty.erase(Grotty.begin() + i);
	}
	indexx.clear();
	//-------------------------------------------------------------------------------

	for (int i = 0; i < Posh.size(); ++i) { //находим те , которые начинаеются в одно время, но заканчиваются позже
		for (int j = 0; j < Grotty.size(); ++j) {
			if (Posh[i].totalStart == Grotty[j].totalStart) {
				if (Posh[i].totalEnd > Grotty[j].totalEnd) {
					PoshI.push_back(i);
				}
				else {
					GrottyI.push_back(j);
				}
			}
		}
	}
	for (auto i : PoshI) {  //удаляем
		Posh.erase(Posh.begin() + i);
	}
	for (auto i : GrottyI) { //удаляем
		Grotty.erase(Grotty.begin() + i);
	}
	PoshI.clear();
	GrottyI.clear();
//-------------------------------------------------------------------------------

	for (int i = 0; i < Posh.size(); ++i) { //находим те, которые заканчиваюстя в одно время, но начинаются раньше
		for (int j = 0; j < Grotty.size(); ++j) {
			if (Posh[i].totalEnd == Grotty[j].totalEnd) {
				if (Posh[i].totalStart < Grotty[j].totalStart) {
					PoshI.push_back(i);
				}
				else {
					GrottyI.push_back(j);
				}
			}
		}
	}
	for (auto i : PoshI) {  //удаляем
		Posh.erase(Posh.begin() + i);
	}
	for (auto i : GrottyI) { //удаляем
		Grotty.erase(Grotty.begin() + i);
	}
	PoshI.clear();
	GrottyI.clear();
//-------------------------------------------------------------------------------------
	for (int i = 0; i < Posh.size(); ++i) { //находим те, которые, одна в одной
		for (int j = 0; j < Grotty.size(); ++j) {
			if (Posh[i].totalStart>Grotty[j].totalStart && Posh[i].totalEnd < Grotty[j].totalEnd) {
				GrottyI.push_back(j);
			}
			if (Posh[i].totalStart < Grotty[j].totalStart && Posh[i].totalEnd > Grotty[j].totalEnd) {
				PoshI.push_back(i);
			}
		}
	}
	for (auto i : PoshI) {  //удаляем
		Posh.erase(Posh.begin() + i);
	}
	for (auto i : GrottyI) { //удаляем
		Grotty.erase(Grotty.begin() + i);
	}
	PoshI.clear();
	GrottyI.clear();
//-----------------------------------------------------------------------------------------------------

	for (int i = 0; i < Posh.size(); ++i) {
		for (int j = i; j < Posh.size(); ++j) {
			if (Posh[i].totalStart<Posh[j].totalStart && Posh[i].totalEnd > Posh[j].totalStart) {
				if (!binary_search(indexx.begin(), indexx.end(), i))
				{
					indexx.push_back(i);
				}


			}
			if (Posh[i].totalStart>Posh[j].totalStart && Posh[i].totalEnd < Posh[j].totalStart) {
				if (!binary_search(indexx.begin(), indexx.end(), j))
				{
					indexx.push_back(j);
				}
			}
		}
	}
	for (auto i : indexx) {  //удаляем
		Posh.erase(Posh.begin() + i);
	}
	indexx.clear();
//--------------------------------------------------------------------------	
	for (int i = 0; i < Grotty.size(); ++i) {
		for (int j = i; j < Grotty.size(); ++j) {
			if (Grotty[i].totalStart<Grotty[j].totalStart && Grotty[i].totalEnd > Grotty[j].totalStart) {
				if (!binary_search(indexx.begin(), indexx.end(), i))
				{
					indexx.push_back(i);
				}


			}
			if (Grotty[i].totalStart > Grotty[j].totalStart && Grotty[i].totalEnd < Grotty[j].totalStart) {
				if (!binary_search(indexx.begin(), indexx.end(), j))
				{
					indexx.push_back(j);
				}
			}
		}
	}
	for (auto i : indexx) {  //удаляем
		Grotty.erase(Grotty.begin() + i);
	}
	indexx.clear();
//---------------------------------------------------------------------------
	//запись в файл
	ofstream loadBus("normal.txt", std::ios::out);
	
	buffs.clear();
	for (auto i : Posh) {
		buffs.clear();
		buffs+="Posh ";
		//------------start
		if (i.startHour < 10) {
			buffs += '0' + to_string(i.startHour) +':';
		}
		else {
			buffs += to_string(i.startHour)+':';
		}

		if (i.startMin < 10) {
			buffs += '0' + to_string(i.startMin) + ' ';
		}
		else {
			buffs += to_string(i.startMin) +' ';
		}
		//-------------------end
		if (i.endHour < 10) {
			buffs += '0' + to_string(i.endHour) + ':';
		}
		else {
			buffs += to_string(i.endHour) + ':';
		}

		if (i.endMin < 10) {
			buffs += '0' + to_string(i.endMin);
		}
		else {
			buffs += to_string(i.endMin);
		}

		buffs += "\n";
		loadBus << buffs;
		buffs.clear();
	}
	loadBus << "\n";

	for (auto i : Grotty) {
		buffs.clear();
		buffs += "Posh ";
		//------------start
		if (i.startHour < 10) {
			buffs += '0' + to_string(i.startHour) + ':';
		}
		else {
			buffs += to_string(i.startHour) + ':';
		}

		if (i.startMin < 10) {
			buffs += '0' + to_string(i.startMin) + ' ';
		}
		else {
			buffs += to_string(i.startMin) + ' ';
		}
		//-------------------end
		if (i.endHour < 10) {
			buffs += '0' + to_string(i.endHour) + ':';
		}
		else {
			buffs += to_string(i.endHour) + ':';
		}

		if (i.endMin < 10) {
			buffs += '0' + to_string(i.endMin);
		}
		else {
			buffs += to_string(i.endMin);
		}

		buffs += "\n";
		loadBus << buffs;
		buffs.clear();
	}
	

	
	
	loadBus << "<end-of-file>";
	loadBus.close();
	
}


