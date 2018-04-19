/*    Enter the Lists
      Author : Ashwin Lall
      Started: 2018-03-22
      This program implements the game Enter the Lists
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "List.h"
using namespace std;

const int HAND_SIZE = 4;
const int ATTACKS = 5;
const int HEALS = 5;
const int PARRIES = 2;
const int STARTING_HEALTH = 12;

const int WITTY_INSULTS = 4;
const int WITTY_COMEBACKS = 2;
const int START_SPIRIT = 4;


void shuffle(List<char> & v);  // shuffles a vector randomly

int main()
{
  List<char> deck1, deck2;
  List<char> hand1, hand2;
  int health1 = STARTING_HEALTH, health2 = STARTING_HEALTH;		// player health
  int hitsinarow1 = 0, hitsinarow2 = 0;							// player hits in a row
  int healsinarow1 = 0, healsinarow2 = 0;						// player heals in a row

  int spirit1 = START_SPIRIT, spirit2 = START_SPIRIT;
  int spihitsinarow1 = 0, spihitsinarow2 = 0;							// player hits in a row


  srand(time(NULL));

  // fill a deck with the different types of cards
  for(int i = 0; i < ATTACKS; ++i)
      deck1.append('A');            // tests append
  for(int i = 0; i < HEALS; ++i)
      deck1.append('H');            // tests append
  for(int i = 0; i < PARRIES; ++i)
      deck1.append('P');            // tests append
  for(int i = 0; i < WITTY_INSULTS; ++i)
      deck1.append('I');            // tests append
  for(int i = 0; i < WITTY_COMEBACKS; ++i)
      deck1.append('C');            // tests append


  deck2 = deck1;                 // tests assignment operator

  // shuffles both decks
  shuffle(deck1);
  shuffle(deck2);

  // deals out HAND_SIZE cards into both players' hands
  for(int i = 0; i < HAND_SIZE; ++i)
    {
      hand1.append(deck1.pop(0));	// tests pop and append
      hand2.append(deck2.pop(0));
    }

  // display rules
  cout << "Welcome to the lists! In this game you will select a card to play each turn against" << endl;
  cout << "your opponent, the Knoxious Knight." << endl;
  cout << "You have " << ATTACKS << " (A)ttack, " << PARRIES << " (P)arry, and " << HEALS << " (H)eal cards in your deck. " << endl;
  cout << "The attack card does damage equal to the number of attack cards played consecutively" << endl;
  cout << "(one damage for the first one, two for the next right after, and so on). " << endl;
  cout << "The parry card can parry (negate) an attack and also reset the number of attacks in a row. " << endl;
  cout << "The heal card can heal you for the number of heal cards played in a row." << endl;
  cout << "Both knights start with " << STARTING_HEALTH << " hit points. Good luck!" << endl;

  cout<<"But, instead of doing all this, you can just (I)nsult your opponent."<<endl;
  cout<<"Both knights started with "<<START_SPIRIT<<" spirit points."<<endl;
  cout << "You have " << WITTY_INSULTS << " (I)nsult and " << WITTY_COMEBACKS << " (C)omeback cards in your deck. " << endl;
  cout<<"With each (I)nsult, you can inflict damage equal to the number of consecutive (I)nsult cards played."<<endl;
  cout<<"If either of your feelings get too hurt, The other automatically wins."<<endl;
  cout<<"Be careful, if one of you prepares a great (C)omeback at the right time \n(when the other (I)nsults), the insulter's spirit might be so damaged \nthey cannot continue the fight. "<<endl;

  // play game until someone dies or we run out of cards
  while(health1 > 0 && health2 > 0 && hand1.length() > 0 && spirit1 > 0 && spirit2 > 0)			// tests length
	{
      // player picks card
      cout << endl << "You have the following cards in your hand:" << endl;
      for(int i = 0; i < hand1.length(); ++i)
      	cout << i << ": " << hand1[i] << endl;
      cout << "and " << deck1.length() << " cards left in your deck." << endl;
      int choice = -1;
      do
      {
      	cout << "Please enter which card you want (from 0 to " << hand1.length() - 1 << "): ";
      	cin >> choice;
      }
      while(choice < 0 || choice >= hand1.length());
      char card1 = hand1.pop(choice);
      if (deck1.length() > 0)
      	hand1.append(deck1.pop(0));

	  // computer picks card randomly
	  char card2 = hand2.pop(rand() % hand2.length());
	  if (deck2.length() > 0)
	  	hand2.append(deck2.pop(0));





      // resolve cards
	  if (card1 == 'A' && card2 == 'A')
	  {
	  	cout << "You both attack." << endl;
	  	health1 -= hitsinarow2 + 1;
	  	cout << "You take " << hitsinarow2 + 1 << " damage." << endl;
	  	health2 -= hitsinarow1 + 1;
	  	cout << "Your opponent takes " << hitsinarow1 + 1 << " damage." << endl;
	  	hitsinarow1++;
	  	hitsinarow2++;
      spihitsinarow2=0;
      spihitsinarow1=0;
	  	healsinarow1 = 0;
	  	healsinarow2 = 0;
	  }

    else if (card1 == 'A' && card2 == 'I')
    {
      cout << "You attack and your opponent insults you." << endl;
      spirit1 -= spihitsinarow2 + 1;
      cout << "Your feelings are hurt. You took " << spihitsinarow2 + 1 << " damage." << endl;
      health2 -= hitsinarow1 + 1;
      cout << "Your opponent takes " << hitsinarow1 + 1 << " physical damage." << endl;
      hitsinarow1++;
      hitsinarow2 = 0;
      spihitsinarow2++;
      spihitsinarow1=0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

    else if (card1 == 'A' && card2 == 'C')
    {
      cout << "You attack and your opponent is physically hurt.\n They have a great verbal comeback prepared,\n but unfortunately never had the chance to use it." << endl;
      health2 -= hitsinarow1 + 1;
      cout << "Either way, your opponent takes " << hitsinarow1 + 1 << " physical damage." << endl;
      hitsinarow1++;
      hitsinarow2 = 0;
      spihitsinarow2 = 0;
      spihitsinarow1= 0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

	  else if (card1 == 'A' && card2 == 'P')
	  {
	  	cout << "You attack and your opponent parries. No one takes any damage." << endl;
	  	hitsinarow1 = 0;
	  	hitsinarow2 = 0;
      spihitsinarow2=0;
      spihitsinarow1=0;
	  	healsinarow1 = 0;
	  	healsinarow2 = 0;
	  }

	  else if (card1 == 'A' && card2 == 'H')
	  {
	  	cout << "You attack and your opponent heals." << endl;
	  	health2 -= hitsinarow1 + 1;
	  	health2 += healsinarow2 + 1;
	  	cout << "Your opponent takes " << hitsinarow1 + 1 << " damage but heals for " << healsinarow2 + 1 << "." << endl;
	  	hitsinarow1++;
	  	hitsinarow2 = 0;
      spihitsinarow2=0;
      spihitsinarow1=0;
	  	healsinarow1 = 0;
	  	healsinarow2++;
	  }




	  else if (card1 == 'P' && card2 == 'A')
	  {
	  	cout << "Your opponent attacks and you parry. No one takes any damage." << endl;
	  	hitsinarow1 = 0;
	  	hitsinarow2 = 0;
      spihitsinarow2=0;
      spihitsinarow1=0;
	  	healsinarow1 = 0;
	  	healsinarow2 = 0;
	  }

    else if (card1 == 'P' && card2 == 'I')
    {
      cout << "Your opponent insults you and you parry. No one takes any damage, but your feelings are hurt." << endl;
      cout << "You take " << spihitsinarow2 + 1 << " damage to your soul." << endl;
      spirit1-=spihitsinarow2+1;
      hitsinarow1 = 0;
      hitsinarow2 = 0;
      spihitsinarow2++;
      spihitsinarow1=0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

    else if (card1 == 'P' && card2 == 'C')
    {
      cout << "You parry, and your opponent has a great verbal comeback prepared,\n but it is all for nothing." << endl;
      hitsinarow1 = 0;
      hitsinarow2 = 0;
      spihitsinarow2 = 0;
      spihitsinarow1= 0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

	  else if (card1 == 'P' && card2 == 'P')
	  {
	  	cout << "You both parry. No one takes any damage." << endl;
	  	hitsinarow1 = 0;
	  	hitsinarow2 = 0;
      spihitsinarow2=0;
      spihitsinarow1=0;
	  	healsinarow1 = 0;
	  	healsinarow2 = 0;
	  }

    else if (card1 == 'P' && card2 == 'H')
	  {
	    health2 += healsinarow2 + 1;
	  	cout << "You parry and your opponent heals " << healsinarow2 + 1 << "." << endl;
	  	hitsinarow1 = 0;
	  	hitsinarow2 = 0;
      spihitsinarow2=0;
      spihitsinarow1=0;
	  	healsinarow1 = 0;
	  	healsinarow2++;
	  }





    else if (card1 == 'H' && card2 == 'A')
	  {
	  	cout << "You heal and your opponent attacks." << endl;
	  	health1 -= hitsinarow2 + 1;
	    health1 += healsinarow1 + 1;
	    cout << "You take " << hitsinarow2 + 1 << " damage but heal for " << healsinarow1 + 1 << "." << endl;
	  	hitsinarow1 = 0;
	  	hitsinarow2++;
      spihitsinarow2=0;
      spihitsinarow1=0;
	  	healsinarow1++;
	  	healsinarow2 = 0;
	  }

    else if (card1 == 'H' && card2 == 'I')
    {
      cout << "You heal but your opponent insults you." << endl;
      health1 += healsinarow1 + 1;
      cout << "You heal for " << healsinarow1 + 1 << ", but your soul takes "<< spihitsinarow2 + 1 << " hurts." << endl;
      hitsinarow1 = 0;
      hitsinarow2=0;
      spihitsinarow2++;
      spihitsinarow1=0;
      healsinarow1++;
      healsinarow2 = 0;
    }

    else if (card1 == 'H' && card2 == 'C')
    {
      cout << "Your opponent has a great verbal comeback prepared, \n but you were just trying to heal yourself." << endl;
      cout << "Your health increases by "<<healsinarow1 + 1 <<"." << endl;
      health1 += healsinarow1 + 1;
      hitsinarow1 = 0;
      hitsinarow2 = 0;
      spihitsinarow2 = 0;
      spihitsinarow1= 0;
      healsinarow1++;
      healsinarow2 = 0;
    }

	  else if (card1 == 'H' && card2 == 'P')
	  {
	  	health1 += healsinarow1 + 1;
	  	cout << "You heal for " << healsinarow1 + 1 << " up to " << health1 << " health while your opponent parries." << endl;
	  	hitsinarow1 = 0;
	  	hitsinarow2 = 0;
      spihitsinarow2=0;
      spihitsinarow1=0;
	  	healsinarow1++;
	  	healsinarow2 = 0;
	  }

    else if (card1 == 'H' && card2 == 'H')
	  {
	  	cout << "You and your opponent both heal." << endl;
	  	health1 += healsinarow1 + 1;
	  	health2 += healsinarow2 + 1;
	  	cout << "You heal " << healsinarow1 + 1 << " up to " << health1 << " health and your opponent heals for " << healsinarow2 + 1 << "." << endl;
	  	hitsinarow1 = 0;
	  	hitsinarow2 = 0;
      spihitsinarow2=0;
      spihitsinarow1=0;
	  	healsinarow1++;
	  	healsinarow2++;
	  }





    else if (card1 == 'I' && card2 == 'I')
    {
      cout << "You and your opponent insult each other simultaneously." << endl;
      spirit1 -= spihitsinarow2 + 1;
      cout << "You take " << spihitsinarow2 + 1 << " damage to your soul." << endl;
      spirit2 -= spihitsinarow1 + 1;
      cout << "Your opponent takes " << spihitsinarow1 + 1 << " damage to theirs." << endl;
      spihitsinarow1++;
      spihitsinarow2++;
      hitsinarow2=0;
      hitsinarow1=0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

    else if (card1 == 'I' && card2 == 'A')
    {
      cout << "Your opponent attack and you insults them." << endl;
      spirit2 -= spihitsinarow1 + 1;
      cout << "Their feelings are hurt. They took " << spihitsinarow1 + 1 << " damage." << endl;
      health1 -= hitsinarow2 + 1;
      cout << "You take " << hitsinarow2 + 1 << " physical damage." << endl;
      hitsinarow2++;
      hitsinarow1 = 0;
      spihitsinarow1++;
      spihitsinarow2=0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

    else if (card1 == 'I' && card2 == 'C')
    {
      cout << "You insult your opponent, but they have a WICKED COMEBACK!!!" << endl;
      cout << "They gained " << spihitsinarow2 + 2 << " back to their soul." << endl;
      spirit2 += spihitsinarow2 + 2;
      cout << "You took " << spihitsinarow2 + 3 << " hurts." << endl;
      spirit1 -= spihitsinarow2 + 3;
      hitsinarow1=0;
      hitsinarow2 = 0;
      spihitsinarow2 = 0;
      spihitsinarow1= 0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

    else if (card1 == 'I' && card2 == 'P')
    {
      cout << "You insult and your opponent parries. No one takes any damage, but their feelings are hurt." << endl;
      cout << "They take " << spihitsinarow1 + 1 << " damage to their soul." << endl;
      spirit2-=spihitsinarow2+1;
      hitsinarow1 = 0;
      hitsinarow2 = 0;
      spihitsinarow1++;
      spihitsinarow2=0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

    else if (card1 == 'I' && card2 == 'H')
    {
      cout << "Your opponent heals but you insult them." << endl;
      health2 += healsinarow2 + 1;
      cout << "They heal for " << healsinarow2 + 1 << ", but take "<< spihitsinarow2 + 1 << " hurts." << endl;
      hitsinarow1 = 0;
      hitsinarow2=0;
      spihitsinarow1++;
      spihitsinarow2=0;
      healsinarow2++;
      healsinarow1 = 0;
    }






    else if (card1 == 'C' && card2 == 'C')
    {
      cout << "You and your opponent both prepaired some great comebacks,\n but neither of you insulted each other actually, so you just stare at each other akwardly.\n This is uncomfortable; nothing actually happens though." << endl;
      spihitsinarow1=0;
      spihitsinarow2=0;
      hitsinarow2=0;
      hitsinarow1=0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

    else if (card1 == 'C' && card2 == 'I')
    {
      cout << "Your opponent insults you, but you have a WICKED COMEBACK!!!" << endl;
      cout << "You gained " << spihitsinarow1 + 2 << " back to your soul." << endl;
      spirit1 += spihitsinarow1 + 2;
      cout << "Your opponent took " << spihitsinarow1 + 3 << " damage to their mental health." << endl;
      spirit2 -= spihitsinarow1 + 3;
      hitsinarow1=0;
      hitsinarow2 = 0;
      spihitsinarow2 = 0;
      spihitsinarow1= 0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

    else if (card1 == 'C' && card2 == 'A')
    {
      cout << "Despite having prepared a great comeback, your opponent strikes and you are physically hurt." << endl;
      health1 -= hitsinarow2 + 1;
      cout << "As a result, you take " << hitsinarow2 + 1 << " physical damage. :(" << endl;
      hitsinarow2++;
      hitsinarow1 = 0;
      spihitsinarow2 = 0;
      spihitsinarow1= 0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

    else if (card1 == 'C' && card2 == 'P')
    {
      cout << "Your opponent parries, and you have a great verbal comeback prepared,\n but it is all for nothing." << endl;
      hitsinarow1 = 0;
      hitsinarow2 = 0;
      spihitsinarow2 = 0;
      spihitsinarow1= 0;
      healsinarow1 = 0;
      healsinarow2 = 0;
    }

    else if (card1 == 'C' && card2 == 'H')
    {
      cout << "You have a great verbal comeback prepared, \n but your opponent was just trying to heal themselves." << endl;
      cout << "Their health increases by "<<healsinarow2 + 1 <<"." << endl;
      health2 += healsinarow2 + 1;
      hitsinarow1 = 0;
      hitsinarow2 = 0;
      spihitsinarow2 = 0;
      spihitsinarow1= 0;
      healsinarow1=0;
      healsinarow2++;
    }







	  // don't allow players to heal above starting health
	  if (health1 > STARTING_HEALTH)
	  	health1 = STARTING_HEALTH;
	  if (health2 > STARTING_HEALTH)
	  	health2 = STARTING_HEALTH;

	  // print out current status
	  cout << "Your health is " << health1 << ", and your spirit is "<<spirit1<<"." << endl;
	  cout << "Your opponent's health is " << health2 << ", and their spirit is "<<spirit2<< "." << endl;
	  cout << "There are " << deck1.length() << " cards left in both your decks." << endl;
    }

  cout << endl;

  // declare winner / tie
  if (health1 == 0 && health2 == 0)
  {
  	cout << "Both you and your opponent strike each other down simultaneously. It is a draw!" << endl;
  }
  else if (spirit1<=0&&spirit2<=0)
  {
    cout<< "You both hurted each other to the point of crying out loud. You both need some time for self-care. Time to leave."<<endl;
  }
  else if (spirit1<=0)
  {
    cout<< "Your opponent hurts your feeling too much you can't take it anymore. Come back again when you're ready to fight :)"<<endl;
  }
  else if (spirit2<=0)
  {
    cout<< "Your insults were so devastating that your opponent ran away from the battlefield. Great job! You Won!!!"<<endl;
  }
  else if (health1 == health2)
  {
  	cout << "The battle is unresolved as both of you are exhausted simultaneously. It is a draw!" << endl;
  }
  else if (health1 > health2)
  {
  	cout << "You vanquish your opponent. The crowd goes wild. You win!" << endl;
  }
  else
  {
  	cout << "Your opponent defeats you this time. Perhaps you will have better luck at the next list? You lose." << endl;
  }

  return 0;
}

void shuffle(List<char> & deck)
{
	for(int i = 0; i < deck.length(); ++i)
	{
		int pos = i + rand() % (deck.length() - i);
		// swap positions i and pos
		char hold = deck.pop(pos);     // tests pop
		deck.insert(pos, deck[0]);     // tests insert
		deck.pop(0);                   // tests pop
		deck.insert(0, hold);          // tests insert
	}
}
