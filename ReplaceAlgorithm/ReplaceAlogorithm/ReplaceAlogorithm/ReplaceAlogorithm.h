#include <iostream>

using namespace std;
class ReplaceAlgorithm
{
public:
	virtual void Replace() = 0;
};

class L_ReplaceAlgorithm:public ReplaceAlgorithm
{
public:
	void Replace(){cout << "L use ReplaceAlgorithm" << endl;}
};

class M_ReplaceAlgorithm:public ReplaceAlgorithm
{
public:
	void Replace(){cout << "M use ReplaceAlgorithm" << endl;}
};

class R_ReplaceAlgorithm:public ReplaceAlgorithm
{
public:
	void Replace(){cout << "R use ReplaceAlgorithm" << endl;}
};