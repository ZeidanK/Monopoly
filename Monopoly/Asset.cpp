#include "Asset.h"


ostream& operator<<(ostream& os, const Asset& asset) {

	cout << "Slot type Asset by the name:" << asset.GetName() << " details:" << endl;
	cout << "City Name:" << asset.GetCityName() << endl;
	cout << "House Price:" << asset.GetPrice() << endl;
	cout << "Rent Price:" << asset.GetRent() << endl;
	if (asset.GetOwner() == NULL)
		cout << "This Property is up for sale" << endl;
	else
		cout << "This Property is owned by: " << asset.GetOwner()->GetName() << endl;

	return os;

}
Asset::Asset(string Slotname, string city_name, int houseprice, int rentprice, Player* Pptr):Slot(Slotname)
{
	SetCityName(city_name);
	setprice( houseprice);
	setrent_price(rentprice);
	SetOwner(Pptr);
	ResetYear();
	OnHold = false;
}


Asset::~Asset()
{
	this->CityName.~basic_string();
}
