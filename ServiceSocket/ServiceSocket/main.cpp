#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//using namespace std;

template <typename elemType>


void display(const std::string &msg,const std::vector<elemType> &vec)
{
	std::cout << msg;
	for(int i=0;i < vec.size();i++)
	{
		elemType t = vec[i];
		std::cout<< t <<""<<std::endl;
	}
}

int main(int argc,char **argv)
{
	std::ofstream outfile( "./myconf.txt",std::ios_base::app );
	if(!outfile)
	{
		std::cout<< "error" <<std::endl;
	}
	else
	{
		outfile << "my name is hqt" <<std::endl;
	}

	std::ifstream infile("./myconf.txt");
	if(!infile)
	{
		std::cout << "in error" << std::endl;
	}
	else
	{
		char a[100];
		memset(a,0,sizeof(a));
		infile.seekg(10);
		infile.read(a,100);
		std::cout << a << std::endl;
		if(infile == NULL)
		{
			std::cout << "NULL" << std::endl;
		}
	}

	std::vector <std::string> ivec;
	ivec.push_back("123");
	std::string msg;
	msg = "ok";

	display(msg,ivec);


	getchar();
	return 0;
}

