// Solution to UNLV Sudo Octal to Decimal Conversion Problem
// Kelly Klare <klarek@unlv.nevada.edu>, September 2013

//Note- CS 135 kids have not yet learned Linux Redirection.
//		Thus, we will use a prompt to collect input.

//no error checking

#include <iostream>
using namespace std;

int main()
{
	char DigitLeft, DigitRight;
	int decimal;
	int base = 8;

	cout << "Please enter a 2-digit Octal number (e.g., 37): ";
	cin.get(DigitLeft);
	cin.get(DigitRight);

	if(DigitLeft=='0')
		decimal = base * 0;
	else if(DigitLeft=='1')
		decimal = base * 1; 
	else if(DigitLeft=='2')
		decimal = base * 2; 
	else if(DigitLeft=='3')
		decimal = base * 3; 
	else if(DigitLeft=='4')
		decimal = base * 4; 
	else if(DigitLeft=='5')
		decimal = base * 5; 
	else if(DigitLeft=='6')
		decimal = base * 6; 
	else if(DigitLeft=='7')
		decimal = base * 7; 

	if(DigitRight=='0')
		decimal = decimal + 0;
	else if(DigitRight=='1')
		decimal = decimal + 1; 
	else if(DigitRight=='2')
		decimal = decimal + 2; 
	else if(DigitRight=='3')
		decimal = decimal + 3; 
	else if(DigitRight=='4')
		decimal = decimal + 4; 
	else if(DigitRight=='5')
		decimal = decimal + 5; 
	else if(DigitRight=='6')
		decimal = decimal + 6; 
	else if(DigitRight=='7')
		decimal = decimal + 7; 

	cout << "Decimal = " << decimal << endl;

	return 0;
}
