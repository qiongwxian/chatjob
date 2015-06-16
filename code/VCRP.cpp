#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
using namespace std;
#include "VCRP.h"

VCRP::VCRP()
{}

void VCRP::getReady(int popsize,int maxGenerations,int raceNum,int numOfisland,double proOfcrossover,double proOfmutation)
{
	this->m_popSize        = popsize;
	this->m_maxGenerations = maxGenerations;
	//this->m_numOfpoints    = numOfpoints;
	this->m_raceNum        = raceNum;
	this->m_proOfcrossover = proOfcrossover;
	this->m_proOfmutation  = proOfmutation;
	//this->m_capacity       = capacity;
	int numOfpoints = this->m_numOfpoints;
	srand(time(0));
	for(int i = 0;i < numOfisland;i++){
		islandType newIsland;
		for(int j = 0;j < popsize;){
			vector<bool> exist(numOfpoints + 1,false);
			geneType g;
			int len = 0;
			while(len < numOfpoints){
				int num = rand() % numOfpoints + 1;
				while(exist[num]){
					num = rand() % numOfpoints + 1;
				}
				exist[num] = true;
				g.gene.push_back(num);
				len++;
			}
			g.gene.push_back(0);
			newIsland.m_population.push_back(g);
			j++;
			for(int k = 0;k < 4;k++){
				geneType newG;
				if(j >= popsize){break;}
				int p1 = rand() % (numOfpoints - 1) + 1;
				int p2 = p1 + (rand() % (numOfpoints - p1) + 1);
				newG.gene.assign(g.gene.begin(),g.gene.end());
				reverse(newG.gene.begin() + p1,newG.gene.begin() + p2);
				/*newG.gene.assign(g.gene.begin(),g.gene.begin() + p1);
				for(int w = p2 - 1;w >= p1;w--){
					newG.gene.push_back(g.gene[w]);
				}*/
				//newG.gene.assign(g.gene.begin() + p2,g.gene.end());
				newIsland.m_population.push_back(newG);
				j++;
			}
		}
		this->m_island.push_back(newIsland);
	}
}

double VCRP::randval()
{
	return (double)rand() / RAND_MAX;
}

bool VCRP::Cmp(double& a,double& b)
{
	return a < b;
}

void VCRP::dpCalculate(geneType& gene)
{
	/*if(gene.gene[gene.gene.size() - 1] != 0){
		int tw;
		cout<<"invalid gene"<<endl;
		cin>>tw;
	}*/
	/*listType* dp;
	listType* dpTail;
	fitnessType min;
	fitnessType t;
	t.capacity = m_capacity;
	t.len = sqrt((m_points[gene.gene[0]].x - m_points[0].x) * (m_points[gene.gene[0]].x - m_points[0].x) +
		(m_points[gene.gene[0]].y - m_points[0].y) * (m_points[gene.gene[0]].y - m_points[0].y));
	dp = new listType;
	dp->item.capacity = t.capacity;
	dp->item.len = t.len;
	dp->next = NULL;
	dpTail = dp;
	//dp.push_back(t);
	min.capacity = m_capacity;
	min.len = t.len;
	//cout<<gene.gene.size()<<endl;
	for(int i = 1;i < gene.gene.size();i++){
		listType* temp;
		listType* tempTail;
		double x1 = m_points[gene.gene[i]].x;
		double x2 = m_points[gene.gene[i - 1]].x;
		double y1 = m_points[gene.gene[i]].y;
		double y2 = m_points[gene.gene[i - 1]].y;
		double x0 = m_points[0].x;
		double y0 = m_points[0].y;
		double dist = sqrt((x2 - x0) * (x2 - x0) + 
			               (y2 - y0) * (y2 - y0)) +
					  sqrt((x1 - x0) * (x1 - x0) +
						   (y1 - y0) * (y1 - y0));
		t.capacity = m_capacity;
		t.len = min.len + dist;
		//t.breakPoint = min.breakPoint;
		//t.breakPoint.push_back(gene.gene[i - 1]);
		//dp.push_back(t);
		listType* tt = new listType;
		tt->item.capacity = t.capacity;
		tt->item.len = t.len;
		tt->next = NULL;
		temp = tt;
		tempTail = tt;
		dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		min.len = t.len;
		min.capacity = m_capacity;
		//min.breakPoint = t.breakPoint;
		listType* j = dp;
		int count = 0;
		while(j != NULL){
			if(j->item.capacity >= m_points[gene.gene[i - 1]].demand + m_points[gene.gene[i]].demand){
				t.capacity = j->item.capacity - m_points[gene.gene[i - 1]].demand;
				t.len = j->item.len + dist;
				//t.breakPoint = j->breakPoint;
				if(t.len < min.len){
					min.capacity = t.capacity;
					min.len = t.len;
					//min.breakPoint = t.breakPoint;
				}
				tt = new listType;
				tt->item.capacity = t.capacity;
				tt->item.len = t.len;
				tt->next = NULL;
				tempTail->next = tt;
				tempTail = tt;
				//dp.push_back(t);
			}
			//dp.erase(j);
			tt = j;
			j = j->next;
			delete tt;
		}
		dp = temp;
	}
	gene.fitness.capacity = min.capacity;
	gene.fitness.len = min.len;
	listType* garbage = dp;
	while(garbage != NULL){
		dp = dp->next;
		delete garbage;
		garbage = dp;
	}*/
	//gene.fitness.breakPoint = min.breakPoint;
	double x[400] = {0.0};
	double y[400] = {0.0};
	int d[400] = {0};
	int amount[400] = {0};
	double dp[3000];
	int capacity = m_capacity;
	for(int i = 0;i <= m_numOfpoints;i++){
		x[i] = m_points[i].x;
		y[i] = m_points[i].y;
		amount[i] = m_points[i].demand;
	}
	for(int i = 0;i < gene.gene.size();i++){
		d[i] = gene.gene[i];
	}

	for(int i = 0;i <= capacity;i++){
		dp[i] = -1;
	}
	dp[capacity] = sqrt((x[d[0]] - x[0]) * (x[d[0]] - x[0]) + (y[d[0]] - y[0]) * (y[d[0]] - y[0]));
	d[m_numOfpoints] = 0;
	vector<int> posible;
	for(int i = 1;i <= m_numOfpoints;i++){
		double temp[3000];
		//vector<int> tempBreak[3000];
		for(int j = 0;j <= capacity;j++){
			temp[j] = -1;
		}
		int minj = 0;
		double dist = sqrt((x[d[i - 1]] - x[0]) * (x[d[i - 1]] - x[0]) + (y[d[i - 1]] - y[0]) * (y[d[i - 1]] - y[0])) + sqrt((x[d[i]] - x[0]) * (x[d[i]] - x[0]) + (y[d[i]] - y[0]) * (y[d[i]] - y[0]));
		for(int j = capacity;j >= 0;j--){
			if(dp[j] != -1&&(dp[j] + dist < temp[capacity]||temp[capacity] == -1)){
				temp[capacity] = dp[j] + dist;
				minj = j;
			}
		}
		//tempBreak[capacity].assign(breakPoint[minj].begin(),breakPoint[minj].end());
		//tempBreak[capacity].push_back(d[i - 1]);
		dist = sqrt((x[d[i]] - x[d[i - 1]]) * (x[d[i]] - x[d[i - 1]]) + (y[d[i]] - y[d[i - 1]]) * (y[d[i]] - y[d[i - 1]]));
		for(int j = capacity;j >= amount[d[i - 1]] + amount[d[i]];j--){
			if(dp[j] != -1&&(dp[j] + dist < temp[j - amount[d[i - 1]]]||temp[j - amount[d[i - 1]]] == -1)){
				temp[j - amount[d[i - 1]]] = dp[j] + dist;
				//tempBreak[j - amount[d[i - 1]]].assign(breakPoint[j].begin(),breakPoint[j].end());
			}
		}
		for(int j = 0;j <= capacity;j++){
			dp[j] = temp[j];
			//breakPoint[j].assign(tempBreak[j].begin(),tempBreak[j].end());
		}
	}
	double min = 1e9;
	int minjj = 0;
	for(int j = 1;j <= capacity;j++){
		//cout<<dp[j]<<endl;
		if(dp[j]!= -1&&min > dp[j]){
			min = dp[j];
			//cout<<j<<endl;
			minjj = j;
		}
	}
	gene.fitness.capacity = minjj;
	gene.fitness.len = min;
}

void VCRP::evaluate(islandType& island)
{
	int len = island.m_population.size();
	for(int i = 0;i < len;i++){
		dpCalculate(island.m_population[i]);
	}
}

void VCRP::keepTheBest(islandType& island)
{
	for(int i = 1;i < island.m_population.size();i++){
		if(Cmp(island.m_population[i].fitness.len,island.bestOne.fitness.len)){
			island.bestOne = island.m_population[i];
		}
	}
}

void VCRP::elitist(islandType& island)
{
	int bestMem = 0;
	int worstMem = 0;
	double best = 1e9,worst = -1;
	for(int i = 0;i < island.m_population.size();i++){
		if(Cmp(island.m_population[i].fitness.len,best)){
			best = island.m_population[i].fitness.len;
			bestMem = i;
		}
		if(Cmp(worst,island.m_population[i].fitness.len)){
			worst = island.m_population[i].fitness.len;
			worstMem = i;
		}
	}
	if(Cmp(best,island.bestOne.fitness.len)){
		island.bestOne = island.m_population[bestMem];
		island.bestStay = 0;
	}
	else{
		island.m_population[worstMem] = island.bestOne;
		island.bestStay++;
	}
}

void VCRP::select(islandType& island)
{
	int count;
	int bestMem;
	double best = 1e9;
	double bestNew = 1e9;
	double bestNewMem;
	double worstNew = -1;
	double worstNewMem;
	int temp;
	int len = island.m_population.size();
	vector<geneType> newPopulation;
	for(int i = 0;i < len;i++){
		vector<bool> visit(len,false);
		count = 0;
		while(count < m_raceNum){
			temp = rand() % len;
			if(!visit[temp]){
				if(Cmp(island.m_population[temp].fitness.len,best)){
					best = island.m_population[temp].fitness.len;
					bestMem = temp;
				}
				visit[temp] = true;
				count++;
			}
		}
		if(Cmp(best,bestNew)){
			bestNew = best;
			bestNewMem = i;
		}
		if(Cmp(worstNew,best)){
			worstNew = best;
			worstNewMem = i;
		}
		newPopulation.push_back(island.m_population[bestMem]);
	}
	int mostDiff = 0;
	int mostDiffMem = 0;
	for(int i = 0;i < len;i++){
		int diff = 0;
		for(int j = 0;j < m_numOfpoints;j++){
			if(newPopulation[bestNewMem].gene[j] != island.m_population[i].gene[j]){
				diff++;
			}
		}
		if(diff > mostDiff){
			mostDiff = diff;
			mostDiffMem = i;
		}
	}
	newPopulation[worstNewMem] = island.m_population[mostDiffMem];
	island.m_population.assign(newPopulation.begin(),newPopulation.end());
}

void VCRP::crossover(islandType& island)
{
	int i, mem, one;
	int first  =  0;
	double x;
	int len = island.m_population.size();
	for (mem = 0; mem < len; ++mem){
		x = randval();
		if (x < m_proOfcrossover){
			++first;
			if (first % 2 == 0)
				  Xover(island,one, mem);
			else
				  one = mem;
		}
	}
}

void VCRP::Xover(islandType& island,int one,int two)
{
	/*int i,j1,j2;
	int point1,point2;
	geneType tem1,tem2;
	vector<int> v1(m_numOfpoints+1,0);
	vector<int> v2(m_numOfpoints+1,0);

	if(m_numOfpoints > 2){
		point1 = rand() % m_numOfpoints;
		point2 = rand() % m_numOfpoints;
		while(point2 == point1){
			point2 = rand() % m_numOfpoints;
		}
		//printf("point1=%d point2=%d\n",point1,point2);
		if(point1 > point2){
			int t = point1;
			point1 = point2;
			point2 = t;
		}
		for(i = point1;i < point2;i++){
			v1[island.m_population[one].gene[i]] = 1;
			v2[island.m_population[two].gene[i]] = 1;
		}
		tem1 = island.m_population[one];
		tem2 = island.m_population[two];
		i = point2;
		j1 = i;
		j2 = i;
		while(i != point2 + m_numOfpoints){
			if(!v2[tem1.gene[i % m_numOfpoints]]){
				island.m_population[two].gene[j1 % m_numOfpoints] = tem1.gene[i % m_numOfpoints];
				j1++;
			}
			if(!v1[tem2.gene[i % m_numOfpoints]]){
				island.m_population[one].gene[j2 % m_numOfpoints] = tem2.gene[i % m_numOfpoints];
				j2++;
			}
			//cout<<"i="<<i<<" j1="<<j1 % m_numOfpoints<<" j2="<<j2 % m_numOfpoints<<endl;
			i++;
		}
	}*/
	vector<int> next1(m_numOfpoints+1,0);
	vector<int> next2(m_numOfpoints+1,0);
	vector<bool> v(m_numOfpoints+1,false);
	geneType temp;
	for(int i = 0;i < m_numOfpoints - 1;i++){
		next1[island.m_population[one].gene[i]] = island.m_population[one].gene[i + 1];
		next2[island.m_population[two].gene[i]] = island.m_population[two].gene[i + 1];
	}
	next1[island.m_population[one].gene[m_numOfpoints - 1]] = island.m_population[one].gene[0];
	next2[island.m_population[two].gene[m_numOfpoints - 1]] = island.m_population[two].gene[0];
	int point = rand() % m_numOfpoints + 1;
	temp.gene.push_back(point);
	v[point] = true;
	int count = 1;
	while(count < m_numOfpoints){
		int fontPoint1 = next1[point];
		int fontPoint2 = next2[point];
		double dist1 = (m_points[fontPoint1].x - m_points[point].x) * (m_points[fontPoint1].x - m_points[point].x) +
						(m_points[fontPoint1].y - m_points[point].y) * (m_points[fontPoint1].y - m_points[point].y);
		double dist2 = (m_points[fontPoint2].x - m_points[point].x) * (m_points[fontPoint2].x - m_points[point].x) +
						(m_points[fontPoint2].y - m_points[point].y) * (m_points[fontPoint2].y - m_points[point].y);
		if(!v[fontPoint1]){
			if(!v[fontPoint2]){
				if(dist1 < dist2){
					temp.gene.push_back(fontPoint1);
					v[fontPoint1] = true;
					point = fontPoint1;
				}
				else{
					temp.gene.push_back(fontPoint2);
					v[fontPoint2] = true;
					point = fontPoint2;
				}
			}
			else{
				temp.gene.push_back(fontPoint1);
				v[fontPoint1] = true;
				point = fontPoint1;
			}
			count++;
		}
		else{
			if(!v[fontPoint2]){
				temp.gene.push_back(fontPoint2);
				v[fontPoint2] = true;
				point = fontPoint2;
			}
			else{
				point = rand() % m_numOfpoints + 1;
				while(v[point]){
					point = rand() % m_numOfpoints + 1;
				}
				v[point] = true;
				temp.gene.push_back(point);
			}
			count++;
		}
	}
	temp.gene.push_back(0);
	island.m_population[one] = temp;
}

double VCRP::orDist(int a,int b,int m,int n)
{
	double dist1 = (m_points[a].x - m_points[b].x) * (m_points[a].x - m_points[b].x) +
					(m_points[a].y - m_points[b].y) * (m_points[a].y - m_points[b].y);
	double dist2 = (m_points[n].x - m_points[m].x) * (m_points[n].x - m_points[m].x) +
					(m_points[n].y - m_points[m].y) * (m_points[n].y - m_points[m].y);
	return dist1 + dist2;
}

void VCRP::mutate(islandType& island)
{
	int one,two;
	int count = 0;
	double x;
	int len = island.m_population.size();
	geneType g;
	for(int i = 0;i < len;i++){
		//g = island.m_population[i];
		count = 0;
		for(int j = 0;j < m_numOfpoints;j++){
			g.gene.clear();
			x = randval();
			if(x < m_proOfmutation){
				if(count % 2){
					//cout<<one<<" "<<j<<endl;
					//int temp = island.m_population[i].gene[one];
					//island.m_population[i].gene[one]  = island.m_population[i].gene[j];
					//island.m_population[i].gene[j] = temp;
					reverse(island.m_population[i].gene.begin() + one,island.m_population[i].gene.begin() + j);
					//reverse(island.m_population[i].gene.begin() + two,island.m_population[i].gene.begin() + j);
					/*double dist1 = orDist(island.m_population[i].gene[one],island.m_population[i].gene[one + 1],
											island.m_population[i].gene[j],island.m_population[i].gene[j + 1]);
					double dist2 = orDist(island.m_population[i].gene[one],island.m_population[i].gene[j + 1],
											island.m_population[i].gene[j],island.m_population[i].gene[one + 1]);
					if(dist2 < dist1){
						int temp = island.m_population[i].gene[one + 1];
						island.m_population[i].gene[one + 1] = island.m_population[i].gene[j + 1];
						island.m_population[i].gene[j + 1] = temp;
					}*/
				}
				else{
					one = j;
				}
				count++;
			}
			/*if(x < m_proOfmutation){
				double dist1 = orDist(island.m_population[i].gene[j - 1],island.m_population[i].gene[j + 2],
										island.m_population[i].gene[j],island.m_population[i].gene[j + 1]);
				int a = island.m_population[i].gene[j - 1];
				int b = island.m_population[i].gene[j + 2];
				int m = island.m_population[i].gene[j];
				int n = island.m_population[i].gene[j + 1];
				for(int k = 0;k < m_numOfpoints - 3;k++){
					if(island.m_population[i].gene[k] != a&&island.m_population[i].gene[k] != m&&island.m_population[i].gene[k] != n){
						double dist2 = orDist(island.m_population[i].gene[k],island.m_population[i].gene[k + 1],m,n);
						//cout<<k<<endl;
						if(dist2 < dist1){
							for(int w = 0;w < m_numOfpoints;w++){
								if(w == k){
									g.gene.push_back(island.m_population[i].gene[w]);
									g.gene.push_back(m);
									g.gene.push_back(n);
								}
								else if(island.m_population[i].gene[w] != m&&island.m_population[i].gene[w] != n){
									g.gene.push_back(island.m_population[i].gene[w]);
								}
							}
							g.gene.push_back(0);
							break;
						}
					}
				}
			}
			if(g.gene.size() > 0){
				island.m_population[i] = g;
			}*/
		}
		//dpCalculate(g)
	}
}

void VCRP::report()
{
	int numOfisland = m_island.size();
	double best = 1e9;
	int bestMem = 0;
	for(int i = 0;i < numOfisland;i++){
		*output<<"island"<<i<<endl;
		*output<<"  "<<m_island[i].bestOne.fitness.len<<endl;
		if(Cmp(m_island[i].bestOne.fitness.len,best)){
			best = m_island[i].bestOne.fitness.len;
			bestMem = i;
		}
	}
	*output<<"All best\n  "<<best<<endl;
	for(int i = 0;i < m_numOfpoints;i++){
		*output<<m_island[bestMem].bestOne.gene[i]<<" ";
	}
	*output<<endl;
}

void VCRP::setInputFile(ifstream *input)
{
	this->input = input;
}

void VCRP::setOutputFile(ofstream *output)
{
	this->output = output;
}

void VCRP::inputPoints()
{
	*input>>m_numOfpoints;
	*input>>m_capacity;
	pointType p;
	p.demand = 0;
	*input>>p.x>>p.y;
	m_points.push_back(p);
	for(int i = 0;i < m_numOfpoints;i++){
		int a;
		*input>>a>>p.x>>p.y>>p.demand;
		m_points.push_back(p);
	}
}

void VCRP::getSolution()
{
	/*geneType gg;
	int a;
	for(int i = 0;i < 100;i++){
		*input>>a;
		cout<<a<<endl;
		gg.gene.push_back(a);
	}
	gg.gene.push_back(0);
	cout<<gg.gene[gg.gene.size() - 1]<<endl;
	dpCalculate(gg);
	cout<<gg.fitness.len<<endl;
	cin>>a;*/
	int generation = 0;
	int numOfisland = m_island.size();
	for(int i = 0;i < numOfisland;i++){
		evaluate(m_island[i]);
		//std::cout<<i<<endl;
	}
	//std::cout<<"OK"<<endl;
	while(generation < m_maxGenerations){
		for(int i = 0;i < numOfisland;i++){
			select(m_island[i]);
			//std::cout<<"select OK"<<endl;
			crossover(m_island[i]);
			//std::cout<<"crossover OK"<<endl;
			mutate(m_island[i]);
			//std::cout<<"mutate OK"<<endl;
			evaluate(m_island[i]);
			//std::cout<<"evaluate OK"<<endl;
			elitist(m_island[i]);
			//std::cout<<"elitist OK"<<endl;
			if(m_island[i].bestStay >= 20){
				//m_proOfmutation += 0.01;
				/*cout<<"add"<<endl;
				m_island[i].bestStay = 0;*/
				int tot = rand() % m_popSize;
				for(int j = 0;j < tot;j++){
					int mem = rand() % numOfisland;
					while(mem == i){
						mem = rand() % numOfisland;
					}
					int p1 = rand() % m_popSize;
					int p2 = rand() % m_popSize;
					geneType g = m_island[i].m_population[p1];
					m_island[i].m_population[p1] = m_island[mem].m_population[p2];
					m_island[mem].m_population[p2] = g;
				}
				m_island[i].bestStay = 0;
				cout<<i<<endl;
			}
		}
		cout<<generation<<endl;
		generation++;
		double best = 1e9;
		cout<<generation - 1<<":"<<endl;
		for(int i = 0;i < numOfisland;i++){
			cout<<"island"<<i<<endl;
			cout<<"  "<<m_island[i].bestOne.fitness.len<<endl;
			if(Cmp(m_island[i].bestOne.fitness.len,best)){
				best = m_island[i].bestOne.fitness.len;
			}
		}
		cout<<"All best\n  "<<best<<endl;
	}
	report();
}
