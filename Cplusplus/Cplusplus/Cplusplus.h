#ifndef _CPLUSPLUS_H
#define _CPLUSPLUS_H

class Cplusplus
{
public:
	Cplusplus();
	~Cplusplus();
	Cplusplus(const Cplusplus&);
	Cplusplus& operator =(const Cplusplus&);
private:
	int m_nPlusRet;
};

#endif;