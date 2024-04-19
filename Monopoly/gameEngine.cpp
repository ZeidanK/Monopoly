#include "gameEngine.h"

int gameEngine::throwDice() {

	return (rand() % 6 + 1);
}

bool gameEngine::JailCheak(Player* P) {

	if (P->GetJailTime()) {
		P->reduceJailTime();
		return true;
	}return false;

}

bool gameEngine::CheckName(string name,int NumOfPlayerInQ)throw (const char*) {
	Player* tempPlayer = NULL;
	for (int i = 0; i < NumOfPlayerInQ; i++)
	{
		tempPlayer = PQueue.front();
		if (tempPlayer->GetName() == name)
			throw("this Name is already taken try a different name");
		else
		{
			PQueue.pop();
			PQueue.emplace(tempPlayer);
		}
	}

	return true;

}
void gameEngine::RemovePlayer(Player* P) {

	cout << "--------------" << endl;
	cout << "Player " << P->GetName() << " is out of the game" << endl;
	cout << "--------------" << endl;
	P->~Player();
	NumberOfPlayers--;

}
bool gameEngine::NewSlotOptions(Slot* slot, Player* P) {
	if (typeid(Asset&)== typeid(*slot))
	{
		return AssetOptions((Asset*)(slot),P);

	}
	else return InstuctionOption((Instruction*)slot,P);
	

}

bool gameEngine::AssetOptions(Asset* asset, Player* P) {
	int input;
	bool res=true;
	if (asset->GetOwner() == NULL)
	{
		cout << "would you like to buy this property?(1=yes,0=no)";
		cin >> input;
		if (input)
		{
			if (P->GetBalance() >= asset->GetPrice())
			{
				P->Payment((-1)*asset->GetPrice());
				cout << "you now own this asset" << endl;
				asset->SetOwner(P);
				P->AddAssetToArray(asset);
			}
			else
				cout << "you cant afford this asset" << endl;
		}
	}
	else {
		cout << "this property is owned by " << asset->GetOwner()->GetName() << endl;
		cout << "you will have to pay rent in the sum of:" << asset->GetRent() << endl;
		res = P->Payment(asset->GetRent());
		if (!asset->GetHold())
			asset->GetOwner()->Payment(asset->GetRent());
	}
	return res;
}
bool gameEngine::InstuctionOption(Instruction* instruction, Player* P) {

	int type = instruction->GetTypeInt();
	switch (type) {
	case 1: {
		if (JailCheak(P)) {
			if (P->GetJailTime()>1)
				cout << "you are still in jail, time remaining" << P->GetJailTime() << endl;
			else
				cout << "this is your last turn in jail." << endl;
			P->reduceJailTime();

		}
		else
		{
			cout << "you have landed in jail and will be out after 3 turns(this turn wont count)" << endl;
			P->SendToJail();
		}
		return true;
	}
	case 2:
	{
		cout << "you have landed back at the starting position a sum of " << MoneyPerTurn;
		cout << " will be added to your balance" << endl;
		return true;

	}
	case 3:
	{
		int draw = Cards->DrawCard();
		cout << "you have landed on a draw card slot and draw:" << draw << endl;
		return P->Payment(draw);
	}
	default:
	{
		cout << "invalid type in instruction option function" << endl;
		return true;
	}

	}
}
void gameEngine::PrintSlotInfo(int position) {

	GameBoard.PrintSlotInfo(position);

}
void gameEngine::intigame() {
	string name;
	cout << "Please enter the number of player's:";
	cin >> NumberOfPlayers;
	bool NameCheak;
	for (int i = 0; i < NumberOfPlayers; i++)
	{
		NameCheak = false;
		while (!NameCheak) {
			try {
				cout << "Please enter player " << i + 1 << " name:";
				cin >> name;
				NameCheak = CheckName(name, i);
			}
			catch (const char* msg) {
				cout << msg << endl;
			}
		}
		Player* Pinit=new Player(name);
		Pinit->Payment(MoneyPerTurn);
		PQueue.push(Pinit);
	}

}

bool gameEngine::Turn(Player* P) {
	int input;
	cout << *P;// function to print player info here
	cout << "would you like to quit the game?(1=yes,0=no)";
	cin >> input;
	if (input)return false;
	if (this->JailCheak(P))return true;
	cout << "Player's current position:" << endl;
	GameBoard.PrintSlotInfo(P->GetPosition());
	input = this->throwDice();
	cout << "Dice roll result:" << input << endl;
	cout << "Player's new potition:" << endl;
	P->MovePosition(input);//updating player position after dice roll
	GameBoard.PrintSlotInfo(P->GetPosition());
	cout << "-------------" << endl;
	return NewSlotOptions(GameBoard.GetSlot(P->GetPosition()), P);//returns true if player is still in the game
	
}

void gameEngine::RunGame() {
	bool gameRunning = true, loop = true;
	Player* P = NULL;
	int TurnCount = 0;
	while (NumberOfPlayers>1) {
		P = PQueue.front();//first use of stl taking the first element of the queue
		PQueue.pop();
		do{
			cout << "------------------Turn Count=" << TurnCount << "-----------------" << endl;
			loop = true;
			try {
				if (!Turn(P)) {
					
					RemovePlayer(P);
				}
				else PQueue.emplace(P);//second use of an stl function adding the player back to the end of the queue
				loop = false;
				}
				catch (const char* msg) { cout << msg << endl; }
				catch (...) {
					std::cout << "unhandeled eception";
				};			
		} while (loop);
		TurnCount++;
	}
	P = PQueue.front();
	cout << "-----------------------" << endl;
	cout << "Game over player " << P->GetName() << " has won the game." << endl;


}
gameEngine::gameEngine()
{
	intigame();
	Cards = new Deck(DeckSize);
}


gameEngine::~gameEngine()
{
	for (int i = 0; i < NumberOfPlayers; i++)
	{
		PQueue.front()->~Player();
		PQueue.pop();
	}
	Cards->~Deck();
	GameBoard.~Board();
	
}
