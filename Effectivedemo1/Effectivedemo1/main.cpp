#include <stdio.h>
#include <iostream>

class CTextBlock{
public:
	CTextBlock();
	~CTextBlock();

	std::size_t length() const;

	static std::size_t StaticLength(){ a = 20; return 0;};

private:
	char * pText;
	static int a;
	mutable std::size_t textLength;
	mutable bool lengthIsValid;
};

int CTextBlock::a = 10;


CTextBlock::CTextBlock()
{
	lengthIsValid = false;
}

CTextBlock::~CTextBlock()
{

}

/*std::size_t CTextBlock::StaticLength()
{
	a = 30;
	return a;
}*/

std::size_t CTextBlock::length() const
{
	a = 20; 

	if(!lengthIsValid)
	{
		textLength = std::strlen(pText);
		lengthIsValid = true;
	}

	return textLength;

}

int main(int argc,char **argv)
{
	CTextBlock a;
	const int constant = 21;
	const int *tmp = &constant;

	int* modifier =const_cast<int *> (&constant); //const转化为非const
	int b = 1;

	static_cast<const int>(b);    //非const转化为const

	a.length();

	return 0;
}