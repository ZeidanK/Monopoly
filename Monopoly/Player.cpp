#include "Player.h"
#include "Asset.h"

ostream& operator<<(ostream& os, const Player& P) {

	cout << "Player " << P.GetName() << " details:" << endl;
	cout << "Current Money Balance:" << P.GetBalance() << endl;
	cout << "Current Position on board:" << P.GetPosition() << endl;
	cout << "Total Number of Propertys:" << P.GetNumberOfAssets() << endl;
	cout << "Number of propertys on hold by bank:" << P.GetNumberOfAssetsInHold() << endl;
	if (P.GetJailTime())
		cout << "This player has " << P.GetJailTime() << " turns left in jail" << endl;
	return os;
}

void Player::ClearPosetions() {

	for (int i = 0; i < NumberOfAssets; i++)
	{
		AssetArray[i]->SetHold(false);
		AssetArray[i]->ResetYear();
		AssetArray[i]->SetOwner();

	}

	


}



void Player::AddAsset(Asset* AsPtr) {

	this->AssetArray = (Asset**)realloc(AssetArray, ((int)this->NumberOfAssets + 1) * sizeof(Asset**));
	this->AssetArray[this->NumberOfAssets] = AsPtr;
	this->NumberOfAssets++;
}

int Player::SellAsset() {

	Asset* Temp = AssetArray[0];
	for (int i = 1; i < NumberOfAssets; i++)
		AssetArray[i - 1] = AssetArray[i];
	this->AssetArray = (Asset**)realloc(AssetArray, ((int)this->NumberOfAssets - 1) * sizeof(Asset**));
	NumberOfAssets--;
	Temp->SetOwner();
	return Temp->GetPrice();

}
void Player::Rebuy(Asset* asset) {

	
	this->MoneyBalance -= asset->RebuyPrice();
	this->NumberOfAssetsInHold--;
	asset->ResetYear();
	asset->SetHold(false);
}

void Player::GetAssetsBack() {

for (int i = 0; i < NumberOfAssets; i++)
		if (AssetArray[i]->GetHold())
			if (AssetArray[i]->RebuyPrice() < this->GetBalance())
				this->Rebuy(AssetArray[i]);

}
void Player::GetMoneyFromassets() {
	for (int i = 0; i < NumberOfAssets; i++) {
		if (!AssetArray[i]->GetHold()) {
			this->MoneyBalance += AssetArray[i]->GetPrice();
			AssetArray[i]->SetHold(true);
			AssetArray[i]->ResetYear();
			AssetArray[i]->AddYearCount();
			this->NumberOfAssetsInHold++;
		}
		if (NumberOfAssets == NumberOfAssetsInHold || MoneyBalance >= 0)
			return;
	}
}
bool Player::Payment(int sum) {
	
	this->MoneyBalance += sum;
	if (sum>0 && NumberOfAssetsInHold)
		GetAssetsBack();
	if (this->MoneyBalance<0 && NumberOfAssets>NumberOfAssetsInHold)
		GetMoneyFromassets();
	return (MoneyBalance > 0);
}

void Player::MovePosition(int steps) {

	CurrentPosition += steps;
	if (CurrentPosition > NumOfSlots) {
		CurrentPosition -= (NumOfSlots);
		Payment(MoneyPerTurn);
		for (int i = 0; i < NumberOfAssets; i++)
			if (AssetArray[i]->GetHold())
				AssetArray[i]->AddYearCount();	
	}
}
Player::Player(string name,int balance,int position)
{
	this->SetName(name);
	this->MoneyBalance = balance;
	this->CurrentPosition = position;
	this->NumberOfAssets = 0;
	this->AssetArray = NULL;
	this->NumberOfAssetsInHold = 0;
	this->JailTime = 0;
}


Player::~Player()
{
	this->ClearPosetions();
	this->PlayerName.~basic_string();
	delete[] AssetArray;

}
