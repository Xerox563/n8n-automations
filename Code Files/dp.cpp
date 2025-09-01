#include <bits/stdc++.h>
using namespace std;

/*
// Recursive
int fibonacci(int n)
{
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Memoization
int solve(int n, vector<int> &dp)
{
    // TC -> O(n) , SC -> O(n) + O(n)
    if (n <= 1)
        return n;
    if (dp[n] != -1)
    {
        return dp[n];
    }
    return dp[n] = solve(n - 1, dp) + solve(n - 2, dp);
}

// Tabulation
int solve(int n, vector<int> &dp)
{
    // TC -> O(n) , SC -> O(n)
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

void fibonacci(int n)
{
    vector<int> dp(n + 1, -1);
    cout << solve(n, dp);
}



int climbStairs(int ind, vector<int> &dp)
{
    if (ind == 0)
        return 1;

    if (dp[ind] != -1)
        return dp[ind];
    int one = 0;
    if (ind > 0)
        one += climbStairs(ind - 1, dp);
    int two = 0;
    if (ind > 1)
        two += climbStairs(ind - 2, dp);
    return dp[ind] = one + two;
}

*/

int frogJump(int ind, vector<int> &dp, vector<int> &arr)
{
    // if (ind == 0)
    //     return 0;
    // if (dp[ind] != -1)
    //     return dp[ind];
    // int oneStep = 1e9;
    // if (ind > 0)
    //     oneStep = frogJump(ind - 1, dp, arr) + abs(arr[ind] - arr[ind - 1]);
    // int twoStep = 1e9;
    // if (ind > 1)
    //     twoStep = frogJump(ind - 2, dp, arr) + abs(arr[ind] - arr[ind - 2]);
    // return dp[ind] = min(oneStep, twoStep);
}

// tabulation
int frogJump(vector<int> &dp, vector<int> &arr)
{
    dp[0] = 0;
    for (int i = 1; i < arr.size(); i++)
    {
        int fs = dp[i - 1] + abs(arr[i] - arr[i - 1]);
        int ss = INT_MAX;
        if (i > 1)
        {
            ss = dp[i - 2] + abs(arr[i] - arr[i - 2]);
        }
        dp[i] = min(fs, ss);
    }
    return dp[arr.size() - 1];
}
// tabulation
int k = 6;
int kfrogJumps(vector<int> &dp, vector<int> &arr)
{
    // TC -> O(n*k), SC -> O(n)
    dp[0] = 0;
    for (int i = 1; i < arr.size(); i++)
    {
        int ans = INT_MAX;
        for (int j = 1; j <= k; j++)
        {
            if (i - j >= 0)
                ans = min(ans, dp[i - j] + abs(arr[i] - arr[i - j]));
        }

        dp[i] = ans;
    }
    return dp[arr.size() - 1];
}

int houseRobberI(int ind, vector<int> &dp, vector<int> &arr)
{
    // f(ind) -> maximum sum i can get from elements between indices {0,ind}
    // base case
    if (ind == 0)
    {
        return arr[0];
    }
    if (ind < 0)
        return 0;
    if (dp[ind] != -1)
        return dp[ind];
    // recurence
    int pick = arr[ind] + houseRobberI(ind - 2, dp, arr);
    int notpick = houseRobberI(ind - 1, dp, arr);
    return dp[ind] = max(pick, notpick);

    // Tabulation
    dp[0] = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        int p = arr[i];
        if (i > 1)
            p += dp[i - 2];
        int np = dp[i - 1];
        return dp[i] = max(p, np);
    }
    return dp[arr.size() - 1];
}

int countWaysinGrid(int i, int j, vector<vector<int>> arr, vector<vector<int>> &dp, int m, int n)
{
    //
    // dp[i][j] = no. of ways from {0,0} to
    // base case
    if (i == m && j == n)
    {
        return 1;
    }
    if (i > m || j > n)
        return 0;

    if (dp[i][j] != -1)
    {
        return dp[i][j]
    }
    // recurence
    int r = countWaysinGrid(i, j + 1, arr, dp, m, n);
    int b = countWaysinGrid(i + 1, j, arr, dp, m, n);
    return dp[i][j] = r + b;

    // Tabulation
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == m - 1 || j == n - 1)
                dp[i][j] = 1;
            // recurence
            int r = 0;
            if (j + 1 < n)
                r += countWaysinGrid(i, j + 1, arr, dp, m, n);
            int b = 0;
            if (i < m - 1)
                b += countWaysinGrid(i + 1, j, arr, dp, m, n);

            return dp[i][j] = r + b;
        }
        return dp[m - 1][n - 1];
    }
}
int mod = (int)(1e9 + 7);
int mazeObstacles(int i, int j, vector<vector<int>> arr, vector<vector<int>> &dp)
{
    if (i == 0 && j == 0)
    {
        return 1;
    }
    if (arr[i][j] == -1 || i < 0 || j < 0)
    {
        return 0;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    int left = mazeObstacles(i, j - 1, arr, dp);
    int top = mazeObstacles(i - 1, j, arr, dp);
    return dp[i][j] = (left + top) % mod;

    // Tabulation
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[0].size(); j++)
        {
            if (arr[i][j] != -1)
                dp[i][j] = 0;
            else if (i == 0 || j == 0)
                dp[i][j] = 1;
            else
                int top = 0, left = 0;
            if (j > 0)
                left = dp[i][j - 1];
            if (i > 0)
                top = dp[i - 1][j];

            dp[i][j] = (top + left) % mod;
        }
        return dp[arr.size() - 1][arr[0].size() - 1];
    }
}

int minPathSum(int i, int j, vector<vector<int>> arr, vector<vector<int>> &dp)
{
    if (i == 0 && j == 0)
    {
        return arr[i][j];
    }
    if (i < 0 || j < 0)
        return INT_MAX;

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    // recurence
    int left = arr[i][j] + mazeObstacles(i, j - 1, arr, dp);
    int top = arr[i][j] + mazeObstacles(i - 1, j, arr, dp);
    return dp[i][j] = min(left, top);

    // Tabulation
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[0].size(); j++)
        {
            if (i == 0 && j == 0)
                dp[i][j] = arr[0][0];
            else
                int left = arr[i][j];
            if (j > 0)
                left += dp[i][j - 1];
            int top = arr[i][j];
            if (i > 0)
                top += dp[i - 1][j];
            dp[i][j] = min(left, top);
        }
        return dp[arr.size() - 1][arr[0].size(); -1];
    }
}

// fixed point -> variable ending point
int triangleSum(int i, int j, vector<vector<int>> arr, vector<vector<int>> &dp)
{
    // n*m grid , also dp[n][m]
    if (i == n - 1)
    {
        return arr[i][j];
    }

    if (dp[i][j] != -1)
        return dp[i][j];

    int tp = arr[i][j] + triangleSum(i + 1, j, arr, dp);
    int tl = arr[i][j] + triangleSum(i + 1, j + 1, arr, dp);
    return dp[i][j] = min(tp, tl);

    // Tabulation

    for (int j = 0; i < n; j++)
    {
        dp[n - 1][j] = arr[n - 1][j];
    }

    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = i; j >= 0; j--)
        {
            int tp = arr[i][j];
            if (i + 1 < n)
                tp += dp[i + 1][j];

            int tl = arr[i][j];
            if (j + 1 < m && i + 1 < n)
                tl += dp[i + 1][j + 1];

            dp[i][j] = min(tp, tl);
        }
        return dp[0][0];
    }
}

// varible start and variable end point
int maxPathSum(int i, int j, vector<vector<int>> arr, vector<vector<int>> &dp)
{
}
int main()
{
    int n, m;
    cin >> m >> n;
    vector<vector<int>> arr(m, vector<int>(n));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
    triangleSum(0, 0, arr, dp);
}
