#pragma once

#include <iostream>
#include <vector>
#include <deque>
class PmergeMe
{
private:
	std::vector<std::pair<int, int> > vec_pair;
	std::vector<std::deque<int> > vec_deque;
	std::vector<int> vec;


	// create pair
	void createVectorPairs();
	//sort pairs
	void sortVectorPairs();
	//create main chain and pend;
	void createMainChainPend();
	//sort pairs
	void sortPairVector();
	//merge sort
	void merge(std::vector<std::pair<int, int> > &array, int begin, int mid, int end);
	//merge left and right
	void mergeSort(std::vector<std::pair<int, int> > &array, int begin, int end);

public:
	PmergeMe();
	void getIntegerSequence(char *av[]);

	PmergeMe(PmergeMe const &other);

	PmergeMe &operator=(PmergeMe const &other);

	~PmergeMe();
};
