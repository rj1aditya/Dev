class Solution
{

    int BinarySearch(vector<int> &nums, int target, int firstFound)
    {
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r)
        {
            int mid = l + (r - l) / 2;

            int number = nums[mid];

            if (number == target)
            {
                //to find the first occurance
                if (firstFound)
                {
                    if (mid == l || nums[mid - 1] != target)
                        return mid;

                    r = mid - 1;
                }
                //to find the last occurance
                else
                {
                    if (nums[mid + 1] != target)
                        return mid;

                    l = mid + 1;
                }
            }
            else if (number < target)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return -1;
    }

public:
    vector<int> searchRange(vector<int> &nums, int target)
    {

        int indx1 = BinarySearch(nums, target, true);
        if (indx1 == -1)
            return {-1, -1};

        int indx2 = BinarySearch(nums, target, false);

        return {index1, index2};
        /* it worked 1st approach
        int l = 0; int r = nums.size()-1;
        
        while( l < r )
        {
            if( nums[l] != target )
                l++;
            if( nums[r] != target )
                r--;
            
            if( nums[l] == target && nums[r] == target)
                break;
        }
        //[] target 0?
        if( l<=r && nums[l] == target && nums[r] == target )
            return {l, r};
        
        return {-1, -1};
        */
    }
};