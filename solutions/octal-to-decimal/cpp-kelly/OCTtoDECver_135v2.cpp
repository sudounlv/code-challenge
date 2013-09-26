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


	if(DigitLeft >= '0' && DigitLeft <= '7')
		decimal = base * (DigitLeft - '0');

	if(DigitRight >= '0' && DigitRight <= '9')
		decimal += (DigitRight - '0');

	cout << "Decimal = " << decimal << endl;

	return 0;
}
