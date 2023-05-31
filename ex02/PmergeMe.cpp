#include "PmergeMe.hpp"

void print(std::vector<std::pair<int, int> > const &a)
{
	std::cout << "The vector elements are : " << std::endl;

	for (unsigned int i = 0; i < a.size(); i++)
		std::cout << a.at(i).first << ", " << a.at(i).second << std::endl;
}

void printDeque(std::deque<int>  const &a)
{

	for (unsigned int i = 0; i < a.size(); i++)
		std::cout << a.at(i) << std::endl;
}

void PmergeMe::getIntegerSequence(char *av[])
{
	int i;
	char *ptr;

	i = 1;
	int val;
	while (av[i])
	{
		
		val = std::strtol(av[i], &ptr, 10);
		if (*ptr != '\0' ||  val < 0)
			std::cout << "Error" << std::endl;
		this->vec.push_back(val);
		i++;
	}
}


void PmergeMe::createVectorPairs()
{
	int size;
	unsigned int i;

	i = 0;
	size = this->vec.size() / 2;
	while (size != 0)
	{
		this->vecPair.push_back(std::make_pair(this->vec.at(i), this->vec.at(i + 1)));
		i += 2;
		size--;
	}
}



void PmergeMe::sortVectorPairs()
{
	unsigned int i;
	int tmp;

	i = 0;
	while (i < this->vecPair.size())
	{
		if (this->vecPair.at(i).first < this->vecPair.at(i).second)
		{
			tmp = this->vecPair.at(i).first;
			this->vecPair.at(i).first = this->vecPair.at(i).second;
			this->vecPair.at(i).second = tmp;
		}
		i++;
	}
	
}

void PmergeMe::createMainChainAndPend()
{
	size_t i;

	mainChain.push_back(this->vecPair.at(0).second);
	
	i = 0;
	while (i < this->vecPair.size())
	{
		mainChain.push_back(this->vecPair.at(i).first);
		pend.push_back(this->vecPair.at(i).second);
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

void PmergeMe::binaryInsertionSort(int target)
{
	int pos;

	pos = this->binarySearch(this->mainChain, target, 0, this->mainChain.size() - 1);
	this->mainChain.insert(this->mainChain.begin() + pos, target);
	
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

void PmergeMe::generateJacobInsertionSequence()
{
	size_t size; 
	size_t jcobstalIndex;
	int index;

	size = this->pend.size();
	index = 3;

	while ((jcobstalIndex = this->jacobsthal(index)) < size - 1)
	{
		this->jacobSequence.push_back(jcobstalIndex);
		index++;
	}
}

int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

void PmergeMe::generatPositions()
{
	size_t val;
	size_t pos;
	size_t lastPos;

	if (this->pend.empty())
		return;
	this->generateJacobInsertionSequence();
	lastPos = 1;
	val = 1;
	while (!this->jacobSequence.empty())
	{
		val  = this->jacobSequence.front();
		
		this->jacobSequence.pop_front();
		this->positions.push_back(val);
		
		pos = val - 1;
		while (pos > lastPos)
		{
			this->positions.push_back(pos);
			pos--;
		}
		lastPos = val;
	}
	while (val++ < this->pend.size())
		this->positions.push_back(val);

}

void printSet(std::set<int>  const &myset)
{
	std::set<int>::iterator i = myset.begin();  
	while (i != myset.end())  
	{
		std::cout << *i - 1 << " ";  
		std::cout << std::endl;  
		i++;
	}
}

void PmergeMe::insertToMainChain()
{
	std::vector<int>::iterator it;
	int target;
	size_t endPos;
	size_t addedCount;
	size_t pos;

	this->generatPositions();
	addedCount = 0;

	for (it = this->positions.begin(); it < this->positions.end(); it++)
	{
		target = this->pend.at(*it - 1);

		endPos = *it + addedCount;
		pos = this->binarySearch(this->mainChain, target, 0, endPos);
		this->mainChain.insert(this->mainChain.begin() + pos, target);
		addedCount++;
	}
	if (this->vec.size() % 2 != 0)
	{
		target = this->vec.at(this->vec.size() - 1);
		pos = this->binarySearch(this->mainChain, target, 0, this->mainChain.size() - 1);
		this->mainChain.insert(this->mainChain.begin() + pos, target);
	}
}

void PmergeMe::applyMergeInsertSort(char *av[])
{
	this->getIntegerSequence(av);
	//check for vec size if it's one print it;
	
	this->createVectorPairs();
	this->sortVectorPairs();
	this->mergeSort(this->vecPair, 0, this->vecPair.size() - 1);
	this->createMainChainAndPend();
	this->insertToMainChain();
	// printDeque(this->mainChain);
	std::sort(this->vec.begin(), this->vec.end());
	for (size_t i = 0; i < this->vec.size(); i++)
	{
		if (this->vec[i] != this->mainChain.at(i))
			{
				std::cout << this->vec[i] << " - " << this->mainChain.at(i) << std::endl;
				std::cout << "Not sorted\n";
				return;
			}
	}
	std::cout << "sorted\n";
}

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(PmergeMe const &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
	this->vec = other.vec;
	this->vecPair = other.vecPair;
	return (*this);
}

PmergeMe::~PmergeMe()
{
}
