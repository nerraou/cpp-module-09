#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <set>

#include <exception>
class PmergeMe
{
private:
	std::vector<int> vec;
	std::vector<int> positions;
	std::vector<std::pair<int, int> > vecPair;
	std::deque<int>	mainChain;
	std::vector<int>	pend;
	std::deque<int>	jacobSequence;



	void getIntegerSequence(char *av[]);
	// create pair
	void createVectorPairs();
	//sort pairs
	void sortVectorPairs();
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
	//generate jacob_insertion_sequence
	void generateJacobInsertionSequence();
	//jacobsthal index
	int jacobsthal(int n);
	//generate positions
	void generatPositions();

	//insert to main chain
	void insertToMainChain();



public:
	PmergeMe();

	//main function
	void applyMergeInsertSort(char *av[]);

	PmergeMe(PmergeMe const &other);

	PmergeMe &operator=(PmergeMe const &other);

	~PmergeMe();

	class exception :public std::exception
	{

	};
};
