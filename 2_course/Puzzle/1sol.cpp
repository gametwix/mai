#include <iostream>
#include <vector>
int main()
{
    int num;
    int size = 0;
    std::vector<int> nums;
    while(std::cin>>num)
    {
        ++size;
        nums.push_back(num);
    }
    for(int i = 0; i <size;++i)
    {
        for(int j = 0;j < size;++j)
        {
            for(int k = 0;k < size;++k)
            {
                if(((i != j) && (i != k) && (k != j)) && (nums[i] + nums[j] + nums[k] == 2020))
                {
                    std::cout << nums[i]*nums[j]*nums[k] << std::endl;
                }
            }
        }
    }
    return 0;
}