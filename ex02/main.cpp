#include "PmergeMe.hpp"
#include <iomanip>

int main(int ac, char *av[])
{
	(void)ac;
	std::clock_t start;
	PmergeMe::PmergeVector pmVec;
	PmergeMe::PmergeDeque pmDeq;
	double durationForVec;
	double durationForDeq;

	start = std::clock();
	pmDeq.applyMergeInsertSort(av);
	durationForDeq = ((std::clock() - start) / (double)1000) ;

	start = std::clock();
	pmVec.applyMergeInsertSort(av);
	durationForVec = (std::clock() - start) / (double)1000 ;

	std::cout << "duration for deque: \n" << std::setprecision(5) << durationForDeq << std::endl;
	std::cout << "duration for Vector: \n" << std::setprecision(5) << durationForVec << std::endl;

	return 0;
}
