#include "ReplaceAlogorithm.h"
//��ʽһ
/*class Cache
{
private:
	ReplaceAlgorithm *m_ra;
public:
	Cache(ReplaceAlgorithm *ra){m_ra = ra;}
	~Cache(){delete m_ra;}
	Cache(const Cache&);  //�������캯��
	Cache &operator= (const Cache&); //��ֵ���캯��
	void Replace(){m_ra->Replace();}
};*/


//��ʽ��
/*enum RA{LRU,MRU,RRU};

class Cache
{
private:
	ReplaceAlgorithm *m_ra;
public:
	Cache(enum RA ra)
	{
		if(ra == LRU)
		{
			m_ra = new L_ReplaceAlgorithm();
		}
		else if(ra == MRU)
		{
			m_ra = new M_ReplaceAlgorithm();
		}
		else if(ra == RRU)
		{
			m_ra = new R_ReplaceAlgorithm();
		}
		else
			m_ra = NULL;
	}

	~Cache(){delete m_ra;}
	void Replace(){m_ra->Replace();}
}*/

//��ʽ��
template <class RA>

class Cache
{
private:
	RA m_ra;
public:
	Cache(){}
	~Cache(){}
	void Replace(){m_ra.Replace();}
};