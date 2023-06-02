#include "PmergeMe.hpp"



PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(PmergeMe const &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
	(void)other;
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::exception::exception()
{
}

PmergeMe::exception::~exception() throw()
{
}

const char *PmergeMe::exception::what() const throw()
{
	return ("Error");
}

void PmergeMe::PmergeVector::getIntegerSequence(char *av[])
{
	int i;
	char *ptr;

	i = 1;
	int val;
	while (av[i])
	{
		if (av[i][0] == '\0')
			throw (PmergeMe::exception());

		val = std::strtol(av[i], &ptr, 10);

		if (*ptr != '\0' || val < 0)
			throw (PmergeMe::exception());

		this->vec.push_back(val);
		i++;
	}
}

void PmergeMe::PmergeVector::createVectorPairs()
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

void PmergeMe::PmergeVector::sortVectorPairs()
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

void PmergeMe::PmergeVector::merge(std::vector<std::pair<int, int> > &array, int begin, int mid, int end)
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

void PmergeMe::PmergeVector::mergeSort(std::vector<std::pair<int, int> > &array, int begin, int end)
{
	int mid;

	if (begin >= end)
		return ;
	mid =  begin + (end - begin) / 2;	
	this->mergeSort(array, begin, mid);
	this->mergeSort(array, mid + 1, end);
	this->merge(array, begin, mid, end);
}

void PmergeMe::PmergeVector::createMainChainAndPend()
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

int PmergeMe::PmergeVector::binarySearch(std::vector<int> array, int target, int begin, int end)
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

void PmergeMe::PmergeVector::generateJacobInsertionSequence()
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

int PmergeMe::PmergeVector::jacobsthal(int n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

void PmergeMe::PmergeVector::generatPositions()
{
	size_t val;
	size_t pos;
	size_t lastPos;
	size_t i;

	if (this->pend.empty())
		return;
	this->generateJacobInsertionSequence();
	lastPos = 1;
	val = 1;
	i = 0;
	while (i < this->jacobSequence.size())
	{
		val  = this->jacobSequence.at(i);
		
		this->positions.push_back(val);
		
		pos = val - 1;
		while (pos > lastPos)
		{
			this->positions.push_back(pos);
			pos--;
		}
		lastPos = val;
		i++;
	}
	while (val++ < this->pend.size())
		this->positions.push_back(val);
}

void PmergeMe::PmergeVector::insertToMainChain()
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

PmergeMe::PmergeVector::PmergeVector()
{
}

PmergeMe::PmergeVector::~PmergeVector()
{
}

void PmergeMe::PmergeVector::applyMergeInsertSort(char *av[])
{
	this->getIntegerSequence(av);

	if (this->vec.size() == 1)
	{
		this->mainChain.push_back(this->vec.at(0));
	}
	else
	{
		this->createVectorPairs();
		this->sortVectorPairs();
		this->mergeSort(this->vecPair, 0, this->vecPair.size() - 1);
		this->createMainChainAndPend();
		this->insertToMainChain();
	}
}

void PmergeMe::PmergeVector::printBefore()
{
	for (unsigned int i = 0; i < this->vec.size(); i++)
		std::cout << this->vec.at(i) << " ";
}

void PmergeMe::PmergeVector::printAfter()
{
	for (unsigned int i = 0; i < mainChain.size(); i++)
		std::cout << this->mainChain.at(i) << " ";
}

void PmergeMe::PmergeDeque::getIntegerSequence(char *av[])
{
	int i;
	char *ptr;

	i = 1;
	int val;
	while (av[i])
	{
		if (av[i][0] == '\0')
			throw (PmergeMe::exception());

		val = std::strtol(av[i], &ptr, 10);

		if (*ptr != '\0' || val < 0)
			throw (PmergeMe::exception());

		this->deque.push_back(val);
		i++;
	}
}

void PmergeMe::PmergeDeque::createDequePairs()
{
	int size;
	unsigned int i;

	i = 0;
	size = this->deque.size() / 2;
	while (size != 0)
	{
		this->dequePair.push_back(std::make_pair(this->deque.at(i), this->deque.at(i + 1)));
		i += 2;
		size--;
	}
}

void PmergeMe::PmergeDeque::sortDequePairs()
{
	unsigned int i;
	int tmp;

	i = 0;
	while (i < this->dequePair.size())
	{
		if (this->dequePair.at(i).first < this->dequePair.at(i).second)
		{
			tmp = this->dequePair.at(i).first;
			this->dequePair.at(i).first = this->dequePair.at(i).second;
			this->dequePair.at(i).second = tmp;
		}
		i++;
	}
}

void PmergeMe::PmergeDeque::merge(std::deque<std::pair<int, int> > &array, int begin, int mid, int end)
{
	size_t leftArrayIndex;
	size_t rightArrayIndex;
	size_t mergedArrayIndex;

	std::deque<std::pair<int, int> > leftArray(array.begin() + begin, array.begin() + mid + 1);
	std::deque<std::pair<int, int> > rightArray(array.begin() + mid + 1, array.begin() + end + 1);

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

void PmergeMe::PmergeDeque::mergeSort(std::deque<std::pair<int, int> > &array, int begin, int end)
{
	int mid;

	if (begin >= end)
		return ;
	mid =  begin + (end - begin) / 2;	
	this->mergeSort(array, begin, mid);
	this->mergeSort(array, mid + 1, end);
	this->merge(array, begin, mid, end);
}

void PmergeMe::PmergeDeque::createMainChainAndPend()
{
	size_t i;

	mainChain.push_back(this->dequePair.at(0).second);
	
	i = 0;
	while (i < this->dequePair.size())
	{
		mainChain.push_back(this->dequePair.at(i).first);
		pend.push_back(this->dequePair.at(i).second);
		i++;
	}
}

int PmergeMe::PmergeDeque::binarySearch(std::deque<int> array, int target, int begin, int end)
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

void PmergeMe::PmergeDeque::generateJacobInsertionSequence()
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

int PmergeMe::PmergeDeque::jacobsthal(int n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

void PmergeMe::PmergeDeque::generatPositions()
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

void PmergeMe::PmergeDeque::insertToMainChain()
{
	std::deque<int>::iterator it;
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
	if (this->deque.size() % 2 != 0)
	{
		target = this->deque.at(this->deque.size() - 1);
		pos = this->binarySearch(this->mainChain, target, 0, this->mainChain.size() - 1);
		this->mainChain.insert(this->mainChain.begin() + pos, target);
	}
}

PmergeMe::PmergeDeque::PmergeDeque()
{
}

PmergeMe::PmergeDeque::~PmergeDeque()
{
}

void PmergeMe::PmergeDeque::applyMergeInsertSort(char *av[])
{
	this->getIntegerSequence(av);

	if (this->deque.size() == 1)
	{
		this->mainChain.push_back(this->deque.front());
	}
	else
	{
		this->createDequePairs();
		this->sortDequePairs();
		this->mergeSort(this->dequePair, 0, this->dequePair.size() - 1);
		this->createMainChainAndPend();
		this->insertToMainChain();
	}
}
