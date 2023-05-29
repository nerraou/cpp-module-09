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

	this->generateJacobInsertionSequence();
	
	std::cout << "Jacob sequence" << std::endl;
	this->insertTomainChain();
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

void PmergeMe::insertTomainChain()
{
	std::set<int> indexSequnce;
	std::vector<int> vec;
	std::string flag;
	int jacobIndex;
	size_t i;
	int item;

	jacobIndex = 3;
	i = 0;
	flag = "non";

	while (i <=  this->pend.size())
	{
		if (this->jacobSequence.size() != 0 && flag != "jacob")
		{
			
			indexSequnce.insert(this->jacobSequence.front());
			vec.push_back(this->jacobSequence.front());
			item = this->pend.at(this->jacobSequence.front() - 1);
			this->jacobSequence.pop_front();
			flag = "jacob";
		}
		else
		{
			if (indexSequnce.count(i))
			{
				
				i++;
			}
			
			indexSequnce.insert(i);
			vec.push_back(i);
			item = this->pend.at(i - 1);
			flag = "not-jacob";
		}
		i++;
	}
	printSet(indexSequnce);
	
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
