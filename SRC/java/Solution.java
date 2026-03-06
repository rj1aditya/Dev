class Solution {

    public int longestOnes(int[] numbs, int k) {
        int l = 0;
        int r = 0;
        int zeros = 0;
        int maxLen = 0;

        while (r < numbs.size()) {
            if (numbs[r] == 0)
                zeros++;

            if (zeros > k) {
                if (numbs[l] == 0)
                    zeros--;
                l++;
            }

            if (zeros <= k) {
                maxLen = max(maxLen, r - l + 1);
            }
            r++;
        }
        return maxLen
    }

    public static void main(String[] args) {
        System.out.println("Hello, Java!!");
    }
}