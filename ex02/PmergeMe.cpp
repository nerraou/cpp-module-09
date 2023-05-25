#include "PmergeMe.hpp"

void print(std::vector<std::pair<int, int> > const &a)
{
	std::cout << "The vector elements are : " << std::endl;

	for (unsigned int i = 0; i < a.size(); i++)
		std::cout << a.at(i).first << ", " << a.at(i).second << std::endl;
}

void printDeque(std::deque<int>  const &a)
{
	std::cout << "The deque elements are : " << std::endl;

	for (unsigned int i = 0; i < a.size(); i++)
		std::cout << a.at(i) << std::endl;
}

void PmergeMe::getIntegerSequence(char *av[])
{
	int i;
	char *ptr;

	i = 1;
	while (av[i])
	{
		this->vec.push_back(std::strtol(av[i], &ptr, 10));
		if (*ptr != '\0')
			std::cout << "Error" << std::endl;
		i++;
	}
	this->createVectorPairs();
}

void PmergeMe::createVectorPairs()
{
	int size;
	unsigned int i;

	i = 0;
	size = this->vec.size() / 2;
	while (size != 0)
	{
		this->vec_pair.push_back(std::make_pair(this->vec.at(i), this->vec.at(i + 1)));
		i += 2;
		size--;
	}
	this->sortVectorPairs();

	// print(this->vec_pair);

	this->mergeSort(this->vec_pair, 0, this->vec_pair.size() - 1);
	this->createMainChainAndPend();
	std::cout << "Main chain" << std::endl;
	printDeque(this->main_chain);
	std::cout << "Pend" << std::endl;
	printDeque(this->pend);
	int new_pos = this->binarySearch(this->main_chain, 3, 0, this->main_chain.size() - 1);
	std::cout << "new position: " << new_pos << std::endl;
	this->main_chain.insert(this->main_chain.begin() + new_pos, 3);

	std::cout  << "--------------------------------------After\n";
	std::cout << "Main chain" << std::endl;
	printDeque(this->main_chain);
}

void PmergeMe::sortVectorPairs()
{
	unsigned int i;
	int tmp;

	i = 0;
	while (i < this->vec_pair.size())
	{
		if (this->vec_pair.at(i).first < this->vec_pair.at(i).second)
		{
			tmp = this->vec_pair.at(i).first;
			this->vec_pair.at(i).first = this->vec_pair.at(i).second;
			this->vec_pair.at(i).second = tmp;
		}
		i++;
	}
	
}

void PmergeMe::createMainChainAndPend()
{
	size_t i;

	main_chain.push_back(this->vec_pair.at(0).second);
	main_chain.push_back(this->vec_pair.at(0).first);
	i = 1;
	while (i < this->vec_pair.size())
	{
		main_chain.push_back(this->vec_pair.at(i).first);
		pend.push_back(this->vec_pair.at(i).second);
		i++;
	}
}

int PmergeMe::binarySearch(std::deque<int> array, int target, int begin, int end)
{
	int mid;

	while (begin <= end)
	{
		mid = begin + (end - begin) / 2;
		if (target == array.at(mid))
			return (mid);

		if (target > array.at(mid))
			begin = mid + 1;
		else
			end = mid - 1;
		
	}
	if (target > array.at(mid))
		return (mid + 1);
	else
		return (mid);
}

void PmergeMe::sortPairVector()
{
	unsigned int i;
	unsigned int j;
	unsigned int size;
	int tmp;

	size = this->vec_pair.size();
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (this->vec_pair.at(j).first < this->vec_pair.at(j + 1).first)
			{
				tmp = this->vec_pair.at(j).first;
				this->vec_pair.at(j).first = this->vec_pair.at(j + 1).second;
				this->vec_pair.at(j + 1).second = tmp;
			}
		}
		
	}
}

void PmergeMe::merge(std::vector<std::pair<int, int> > &array, int begin, int mid, int end)
{
	size_t leftArrayIndex;
	size_t rightArrayIndex;
	size_t mergedArrayIndex;

	std::vector<std::pair<int, int> > leftArray(array.begin() + begin, array.begin() + mid + 1);
	std::vector<std::pair<int, int> > rightArray(array.begin() + mid + 1, array.begin() + end + 1);

	leftArrayIndex = 0;
	rightArrayIndex = 0;
	mergedArrayIndex = begin;


	while (leftArrayIndex < leftArray.size() && rightArrayIndex < rightArray.size())
	{
		if (leftArray[leftArrayIndex].first <= rightArray[rightArrayIndex].first)
		{
			array[mergedArrayIndex] = leftArray[leftArrayIndex];
			leftArrayIndex++;
		}
		else
		{
			array[mergedArrayIndex] = rightArray[rightArrayIndex];
			rightArrayIndex++;
		}
		mergedArrayIndex++;
	}
	while (leftArrayIndex < leftArray.size())
	{
		array[mergedArrayIndex] = leftArray[leftArrayIndex];
		leftArrayIndex++;
		mergedArrayIndex++;
	}
	while (rightArrayIndex < rightArray.size())
	{
		array[mergedArrayIndex] = rightArray[rightArrayIndex];
		rightArrayIndex++;
		mergedArrayIndex++;
	}
}

void PmergeMe::mergeSort(std::vector<std::pair<int, int> > &array, int begin, int end)
{
	int mid;

	if (begin >= end)
		return ;
	mid =  begin + (end - begin) / 2;	
	this->mergeSort(array, begin, mid);
	this->mergeSort(array, mid + 1, end);
	this->merge(array, begin, mid, end);
}

PmergeMe::PmergeMe(/* args */)
{
}

PmergeMe::PmergeMe(PmergeMe const &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
	this->vec = other.vec;
	this->vec_pair = other.vec_pair;
	return (*this);
}

PmergeMe::~PmergeMe()
{
}
