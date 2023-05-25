#pragma once

#include <iostream>
#include <vector>
#include <deque>
class PmergeMe
{
private:
	std::vector<int> vec;
	std::vector<std::pair<int, int> > vec_pair;
	std::deque<int>  main_chain;
	std::deque<int>  pend;


	// create pair
	void createVectorPairs();
	//sort pairs
	void sortVectorPairs();
	//sort pairs
	void sortPairVector();
	//merge sort
	void merge(std::vector<std::pair<int, int> > &array, int begin, int mid, int end);
	//merge left and right
	void mergeSort(std::vector<std::pair<int, int> > &array, int begin, int end);
	//create main chain and pend;
	void createMainChainAndPend();
	// binary search
	int binarySearch(std::deque<int> array,int target, int begin, int end);
	//binary insertin sort
	void binaryInsertionSort(int target);
	

public:
	PmergeMe();
	void getIntegerSequence(char *av[]);

	PmergeMe(PmergeMe const &other);

	PmergeMe &operator=(PmergeMe const &other);

	~PmergeMe();
};
