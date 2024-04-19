#pragma once
class Asset;
#include "includess.h"
#define MoneyPerTurn 350
class Player
{
	string PlayerName;
	int MoneyBalance;
	int CurrentPosition;
	Asset** AssetArray;
	int NumberOfAssets;
	int NumberOfAssetsInHold;
	int JailTime;

	void AddAsset(Asset* assetptr);
	int SellAsset();//sells asset in positon 0 of the array
	void SetName(string name) { this->PlayerName = name; }
	void Rebuy(Asset* asset);
	void GetAssetsBack();
	void GetMoneyFromassets();
	void ClearPosetions();//clear all pleayers holdings
public:
	void AddAssetToArray(Asset* asset) {AddAsset(asset);}//add new asset to array
	int GetJailTime()const { return JailTime; }
	void reduceJailTime() { JailTime--; }
	void SendToJail() { JailTime = 3; }
	void MovePosition(int steps);
	bool Payment(int Sum);//add or remove sum for player return true if player still eligabil to play
	string GetName()const { return PlayerName; }
	int GetPosition()const { return CurrentPosition; }
	int GetBalance()const { return MoneyBalance; }
	int GetNumberOfAssets()const { return NumberOfAssets;  }
	int GetNumberOfAssetsInHold()const { return NumberOfAssetsInHold; }


	friend ostream& operator<<(ostream& os, const Player& P);

	Player(string name,int balance=0,int position=1);
	~Player();
};

