// Solution to UNLV Sudo Octal to Decimal Conversion Problem
// Kelly Klare <klarek@unlv.nevada.edu>, September 2013

// Does not use Linux Redirection since it may not have been taught to CS 135 yet

#include <iostream>
#include <string>
using namespace std;

int main()
{
	bool inputError = false;
	char DigitLeft, DigitRight;
	int decimal;
	int base = 8;

	cout << "Please enter a 2-digit Octal number (e.g., 37): ";
	cin.get(DigitLeft);
	cin.get(DigitRight);


	if(DigitLeft >= '0' && DigitLeft <= '7')
		decimal = base * (DigitLeft - '0');
	else
		inputError = true;

	if(DigitRight >= '0' && DigitRight <= '7')
		decimal += (DigitRight - '0');
	else
		inputError = true;

	if(!inputError)
		cout << "Decimal = " << decimal << endl;
	else
		cout << "ERROR: INVALID INPUT" << endl;

	return 0;
}