#pragma once
#include "Slot.h"
#include "Player.h"
#define Ribit 1
class Player;

class Asset:public Slot
{
protected:
	string CityName;
	int HousePrice;
	int Rent;
	Player* PlayerPtr;
	int YearCount;
	bool OnHold;

	void SetCityName(string CName) { CityName = CName; }
	void setprice(int price) { HousePrice = price; }
	void setrent_price(int rent_price) { Rent = rent_price; }

public:
	void SetHold(bool hold) { OnHold = hold; }
	int RebuyPrice() { return YearCount * HousePrice*Ribit; }
	bool GetHold()const { return OnHold; }
	void ResetYear() { YearCount = 0; }
	void AddYearCount() { YearCount++; }
	void SetOwner(Player* Pptr = NULL) { PlayerPtr = Pptr; }
	Player* GetOwner()const { return PlayerPtr; }
	int GetPrice()const { return HousePrice; }
	int GetRent()const { return Rent; }
	string GetCityName()const { return CityName; }
	virtual void PrintSlot() { cout << *this; }


	friend ostream& operator<<(ostream& os, const Asset& asset);
	Asset(string Slotname,string city_name, int houseprice,int rentprice,Player* Pptr=NULL);
	~Asset();
};


