
#include<iostream>
#include<vector>
using namespace std;


void buildSegmentTree(int i, int l, int r, vector<int> &nums, vector<int> &segTree)
{
    if(l == r)
    {
        segTree[i] = nums[l];
        return;
    }

    int mid = l + (r-l)/2; 
    buildSegmentTree(2*i+1, l, mid, nums, segTree);
    buildSegmentTree(2*i+2, mid+1, r, nums, segTree);

    segTree[i] = segTree[2*i+1] + segTree[2*i+2];
}

void updateSegTree(int i, int l, int r,
                   int idx, int val,
                   vector<int> &nums,
                   vector<int> &segTree)
{
    // Leaf node
    if(l == r)
    {
        nums[idx] = val;
        segTree[i] = val;
        return;
    }

    int mid = l + (r - l) / 2;

    if(idx <= mid)
        updateSegTree(2*i+1, l, mid, idx, val, nums, segTree);
    else
        updateSegTree(2*i+2, mid+1, r, idx, val, nums, segTree);

    segTree[i] = segTree[2*i+1] + segTree[2*i+2];
}


int findSumInRange(int start, int end,
                   int i, int l, int r,
                   vector<int> &segTree)
{
    // No overlap
    if(r < start || l > end)
        return 0;

    // Complete overlap
    if(start <= l && r <= end)
        return segTree[i];

    // Partial overlap
    int mid = l + (r - l) / 2;

    return findSumInRange(start, end, 2*i+1, l, mid, segTree)
         + findSumInRange(start, end, 2*i+2, mid+1, r, segTree);
}

int main()
{
    vector<int> num{1,4,5,3,2,7,2};
    vector<int> segTree(4 * num.size());
    buildSegmentTree(0, 0, num.size() - 1, num, segTree);

    //update 3rd index value to 20
    updateSegTree(0, 0, num.size()-1, 3, 20, num, segTree);
    int ans = findSumInRange(2, 5, 0, 0, num.size()-1, segTree);
    return 0;
}