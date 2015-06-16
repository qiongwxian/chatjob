#ifndef VCRP_H
#define VCRP_H
#include <vector>
#include <fstream>
#include <list>
using namespace std;

class VCRP
{
public:
	VCRP();
	void getSolution(void);
	void getReady(int,int,int,int,double,double);
	void setInputFile(ifstream *);
	void setOutputFile(ofstream *);
	void inputPoints();
private:
	int     m_popSize;
	int     m_maxGenerations;
	int     m_numOfpoints;
	int     m_raceNum;
	int     m_capacity;
	double  m_proOfcrossover;
	double  m_proOfmutation;
	ifstream *input;
	ofstream *output;
	struct fitnessType{
		int capacity;
		double len;
		//list<int> breakPoint;
		fitnessType(){capacity = 0;len = 1e9;}
	};
	struct listType{
		fitnessType item;
		listType* next;
	};
	struct geneType{
		vector<int> gene;
		fitnessType fitness;
	};
	struct islandType{
		vector<geneType> m_population;
		geneType bestOne;
		int bestStay;
		islandType(){bestStay = 0;}
	};
	struct pointType{
		double x,y;
		int demand;
	};
	vector<islandType> m_island;
	vector<pointType> m_points;
private:
	double randval(void);
	bool Cmp(double&,double&);
	void dpCalculate(geneType&);
	void evaluate(islandType&);
	void keepTheBest(islandType&);
	void elitist(islandType&);
	void select(islandType&);
	void crossover(islandType&);
	void Xover(islandType&,int,int);
	void swap(double *, double *);
	void mutate(islandType&);
	void report(void);
	double orDist(int,int,int,int);
};

#endif