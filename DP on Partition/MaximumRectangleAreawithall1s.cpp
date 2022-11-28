/*Question :- Given a rows x cols binary matrix filled with 0's and 1's,
find the largest rectangle containing only 1's and return its area.*/
#include <bits/stdc++.h>
using namespace std;

// we can use the logic behind the problem "largest rectangle under histogram to solve this problem"
//  helper function is function which solved the problem "largest rectangle under histogram to solve this problem" and returns the area
int helper(vector<int> histo)
{
    int n = histo.size();
    stack<int> st;
    int max_ans = 0;
    for (int i = 0; i <= n; i++)
    {
        while ((!st.empty()) && (i == n || histo[st.top()] >= histo[i]))
        {
            // height calculation
            int height = histo[st.top()];
            st.pop();
            // width calcalation
            int width;
            if (st.empty())
                width = i;
            else
                width = i - st.top() - 1;
            // max_ans  update
            max_ans = max(max_ans, height * width);
        }
        st.push(i);
    }
    return max_ans;
}

// we can form histograms for every row of the matrix
// the height of the individual histogram bar keeps increasing if the col values are being 1 repeatedly
// at any col if a 0 is encountered the height of the bar becomes 0
// then the problem just becomes find max area in histogram problem
int maxrectanglewithall1s(vector<vector<int>> &matrix)
{
    int row = matrix.size();
    int col = matrix[0].size();
    int max_ans = 0;
    vector<int> histo(col, 0);
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            if (matrix[r][c] == 1)
                histo[c]++;
            else
                histo[c] = 0;
        }
        int ans = helper(histo);
        max_ans = max(max_ans, ans);
    }
    return max_ans;
}
int main()
{
    vector<vector<int>> matrix = {{1, 0, 1, 0, 0},
                                  {1, 0, 1, 1, 1},
                                  {1, 1, 1, 1, 1},
                                  {1, 0, 0, 1, 0}};
    cout << "Area of largest rectangle containing only 1's is " << maxrectanglewithall1s(matrix) << " sq meter";
}

// TC -> o(row*(col + col))
// SC -> o(col)