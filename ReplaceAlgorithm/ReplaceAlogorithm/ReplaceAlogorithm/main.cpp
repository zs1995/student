#include "Cache.h"

int main(int argc,char **argv)
{
	//Cache cache(new M_ReplaceAlgorithm());
	//Cache cache(LRU);
	Cache<R_ReplaceAlgorithm> cache;
	cache.Replace();
	getchar();
	return 0;
}