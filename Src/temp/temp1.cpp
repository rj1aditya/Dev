#include <bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
using namespace std;

// #include <bits/stdc++.h>
// int maxArea(vector<int>& height) {

//     int max_area = 0;
//     int area;
//     int n = height.size();
//   	for(int i =0; i < n-1; i++)
//     {
//         for(int j = i+1; j<n; j++)
//         {
//             area=min(height[i], height[j])*(j-i);
//             if(max_area<area)
//                 max_area= area;
//         }
//     }
// 	return max_area;
// }


// Driver program
int main()
{
    vector<int> v{4, 3, 2, 1, 4};
    cout << maxArea(v);
    return 0;
}
