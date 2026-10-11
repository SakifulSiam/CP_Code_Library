// 1D prefix sums: inclusive range sum [l,r] in O(1) after O(n) build.
vector<long long> buildPrefix(const vector<int>& a) {
    vector<long long> pref(a.size()+1);
    for (int i=0;i<(int)a.size();++i) pref[i+1]=pref[i]+a[i];
    return pref;
}
long long rangeSum(const vector<long long>& pref,int l,int r) {
    return pref[r+1]-pref[l];
}

// Difference array: add value to every index in inclusive [l,r].
// After all updates, prefix-sum diff once to restore the final values.
void rangeAdd(vector<long long>& diff,int l,int r,long long value) {
    diff[l]+=value;
    if (r+1<(int)diff.size()) diff[r+1]-=value;
}

// Sliding window for nonnegative values: longest subarray with sum <= limit.
int longestWindowAtMost(const vector<int>& a,long long limit) {
    int left=0,best=0; long long sum=0;
    for (int right=0;right<(int)a.size();++right) {
        sum+=a[right];
        while (left<=right && sum>limit) sum-=a[left++];
        best=max(best,right-left+1);
    }
    return best;
}

// Two pointers on a sorted array: determine whether two values sum to target.
bool hasPairSum(const vector<long long>& a,long long target) {
    int l=0,r=(int)a.size()-1;
    while (l<r) {
        long long sum=a[l]+a[r];
        if (sum==target) return true;
        if (sum<target) ++l; else --r;
    }
    return false;
}
