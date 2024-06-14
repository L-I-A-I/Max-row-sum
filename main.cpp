#include <algorithm>
#include <iostream>
#include <vector>

int I, J;
long long int maxSum = 0;
const int N = 20;

void cache(int arr[], std::vector<int>& sum, std::vector<int>& ind)
{
    sum.push_back(maxSum);
    ind.push_back(I);
    ind.push_back(J);
    I = J + 1;
    J = I;
    maxSum = arr[I];
}

void cleanTwo(std::vector<int>& sum, std::vector<int>& ind)
{
    sum.pop_back();
    sum.pop_back();

    std::swap(*(ind.end() - 5), ind.back());
    
    ind.pop_back();
    ind.pop_back();
    ind.pop_back();
    ind.pop_back();
}

void deleteTwo(std::vector<int>& sum, std::vector<int>& ind)
{
    sum.pop_back();
    sum.pop_back();

    ind.pop_back();
    ind.pop_back();
    ind.pop_back();
    ind.pop_back();
}

int main()
{
    //main array
    int a[N] = {};

	//populate array
    srand(time(nullptr));
    for (size_t i = 0; i < N; i++)
    {
        a[i] = (rand() % N) - N / 2;
        std::cout << a[i] << ' ';
    }

    const int aSize = sizeof(a) / sizeof(a[0]);
    maxSum = a[0];

    for (size_t i = 0; i < aSize - 1; ++i)
    {
        if (a[i] > 0)
        {
            maxSum = a[i];
            I = i;
            J = i;
            break;
        }
        else
        {
            if (maxSum < a[i + 1])
                maxSum = a[i + 1];
        }        
    }

    if (maxSum <= 0)
    {
        std::cout << "\nMax num: " << maxSum << std::endl;
        return 0;
    }

	std::vector<int> sums, indexes;
	
	//make positive and negative groups
    while (J < aSize) {
        if (a[I] >= 0)
            for (size_t i = I; i < aSize - 1 && a[i + 1] >= 0; ++i)
            {
                J = i + 1;
                maxSum += a[J];
            }
        else
            for (size_t i = I; i < aSize - 1 && a[i + 1] <= 0; i++) {
                J = i + 1;
                maxSum += a[J];
            }

        cache(a, sums, indexes);
    }

	//delete last group if it is negative
    if (sums[sums.size() - 1] < 0) {
        sums.pop_back();
        indexes.pop_back();
        indexes.pop_back();
    }

	//merge groups if relevant
    if (sums.size() > 1)
    {
        maxSum = 0;

        for (size_t i = sums.size() - 1; i > 1;)
        {
            if (sums[i] + sums[i - 1] > 0)
            {
                sums[i - 2] += sums[i] + sums[i - 1];
                cleanTwo(sums, indexes);
                i -= 2;
                if (maxSum < sums[i])
                {
                    maxSum = sums[i];
                    I = indexes[indexes.size() - 2];
                    J = indexes[indexes.size() - 1];
                }
            }
            else
            {
                if (maxSum < sums[i])
                {
                    maxSum = sums[i];
                    I = indexes[indexes.size() - 2];
                    J = indexes[indexes.size() - 1];
                }
                deleteTwo(sums, indexes);
                i -= 2;
            }
        }

        std::cout << "Max sum: " << maxSum << " (" << I << ", " << J << ")";
    }
    else {
        std::cout << "Max sum: " << maxSum << " (" << indexes[0] << ", "
            << indexes[1] << ")";
    }
}