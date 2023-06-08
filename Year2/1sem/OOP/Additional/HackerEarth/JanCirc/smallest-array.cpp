#include <bits/stdc++.h>
using namespace std;

vector<long long> smallestArray(long long N, long long K, const vector<long long> &A,
                                const vector<long long> &L, const vector<long long> &R)
{
    vector<long long> B(N);
    copy(L.begin(), L.end(), B.begin());
    long long curAbs = 0LL;
    for (long long i = 0; i < N; ++i)
    {
        curAbs += llabs(A[i] - B[i]);
    }

    if (curAbs > K)
    {

        for (long long i = N - 1; i > -1; --i)
        {

            if (B[i] > A[i])
                continue;

            if (min(R[i], A[i]) - B[i] >= curAbs - K)
            {
                B[i] += curAbs - K;
                return B;
            }
            else
            {

                curAbs -= min(R[i], A[i]) - B[i];
                B[i] = min(R[i], A[i]);
            }
        }
    }

    else if (curAbs < K)
    {

        for (long long i = N - 1; i > -1; --i)
        {

            if (R[i] - max(B[i], A[i]) < abs(A[i] - B[i]))
                continue;

            if ((R[i] - max(B[i], A[i])) - (abs(A[i] - B[i])) >= K - curAbs)
            {
                B[i] = max(B[i], A[i]) + (K - curAbs);
                return B;
            }
            else
            {
                curAbs += (R[i] - max(B[i], A[i])) - abs(B[i] - A[i]);
                B[i] = R[i];
            }
        }
    }
    else
    {
        if (curAbs == K)
            return B;

        return {-1LL};
    }
}

int main()
{

    ios::sync_with_stdio(0);
    cin.tie(0);
    long long N;
    cin >> N;
    long long K;
    cin >> K;
    vector<long long> A(N);
    for (long long i_A = 0; i_A < N; i_A++)
    {
        cin >> A[i_A];
    }
    vector<long long> L(N);
    for (long long i_L = 0; i_L < N; i_L++)
    {
        cin >> L[i_L];
    }
    vector<long long> R(N);
    for (long long i_R = 0; i_R < N; i_R++)
    {
        cin >> R[i_R];
    }

    vector<long long> out_;
    out_ = smallestArray(N, K, A, L, R);
    cout << out_[0];
    for (long long i_out_ = 1; i_out_ < out_.size(); i_out_++)
    {
        cout << " " << out_[i_out_];
    }
    cout << '\n';
}
/*
4
6
2 1 3 0
0 2 1 1
3 2 2 1

4
8
2 1 3 0
0 2 1 1
3 5 6 1

*/
