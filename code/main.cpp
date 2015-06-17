#include <iostream>
#include <fstream>
using namespace std;

#include "VCRP.h"

int main()
{
	ifstream input;
	ofstream output;
	input.open("data4.txt");
	output.open("out2-385.txt");
	VCRP vcrp;
	vcrp.setInputFile(&input);
	vcrp.setOutputFile(&output);
	vcrp.inputPoints();
	vcrp.getReady(250,60000,5,3,0.8,0.02);
	cout<<"ok"<<endl;
	vcrp.getSolution();
	input.close();
	output.close();
}
