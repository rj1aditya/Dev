#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {

        //O( log( min( nums1.size(), nums2.size())))

        if (nums2.size() < nums1.size())
            return findMedianSortedArrays(nums2, nums1);
        int n1 = nums1.size();
        int n2 = nums2.size();
        int low = 0, high = n1;

        while (low <= high)
        {
            int cut1 = (low + high)/2;
            int cut2 = (n1 + n2 + 1) / 2 - cut1;

            int left1 = cut1 == 0 ? INT_MIN : nums1[cut1 - 1];
            int left2 = cut2 == 0 ? INT_MIN : nums2[cut2 - 1];

            int right1 = cut1 == n1 ? INT_MAX : nums1[cut1];
            int right2 = cut2 == n2 ? INT_MAX : nums2[cut2];

            if (left1 <= right2 && left2 <= right1)
            {
                if ((n1 + n2) % 2 == 0)
                    return (max(left1, left2) + min(right1, right2)) / 2.0;
                else
                    return max(left1, left2);
            }
            else if (left1 > right2)
            {
                high = cut1 - 1;
            }
            else
            {
                low = cut1 + 1;
            }
        }
        return 0.0;
        /* TIME Complexity not O(log(m+n))
        int len1 = nums1.size();
        int i = 0;
        
        int len2 = nums2.size();
        int j = 0;
        
        vector<int> v;

        while( i < len1 && j < len2 )
        {
            nums1[i] < nums2[j] ? v.push_back(nums1[i++]) : v.push_back(nums2[j++]);
        }
        
        while( i < len1 )
        {
            v.push_back(nums1[i++]);
        }
        while( j < len2 )
        {
            v.push_back(nums2[j++]);
        }
        
        if( (len1+len2) & 1 )
            return v[(len1+len2)/2];
        else
            return (v[(len1+len2)/2] + v[(len1+len2)/2 - 1])/2;
        return 0;
        */
    }
};

int main()
{
    vector<int> v1{1, 2};
    vector<int> v2{3};
    Solution s;
    s.findMedianSortedArrays(v1, v2);
}