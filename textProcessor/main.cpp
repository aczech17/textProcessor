#include "textarray.h"

#include <iostream>
using namespace std;
int main()
{
	TextArray<> txa;

	txa.addText("Nazywam sie *imie* *nazwisko*");//0
	txa.addText("Szanowny panie *imie* *nazwisko*. Moj numer telefonu to *numer telefonu*");//1

	stringPairs v1 = { {"*imie*", "Cezary"},{"*nazwisko*","Baryka"} };//0
	stringPairs v2 = { {"*numer telefonu*","123 333 777"} };//1

	txa.addRecord(v1);
	txa.addRecord(v2);


	txa.replacement(0, 0);
	cout << txa.textWithNumber(0) << endl;;

	txa.replacement(1, 1);
	cout << txa.textWithNumber(1);

	cin.ignore(2);
	return 0;
}