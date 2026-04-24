#include <bits/stdc++.h>
using namespace std;

// Problem 2673: m0ss1 的翘课系统
// Maintain a set of non-overlapping intervals (activities).
// Operation A l r: insert [l, r] but must delete all conflicting activities first.
//   Return the count of deleted activities.
// Operation B: return the number of current activities.
// Constraints: up to 2e5 ops, coordinates up to 1e5.
// We maintain disjoint intervals in an ordered map keyed by l.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;

    // map of intervals: key = l, value = r, disjoint and sorted by l.
    map<int,int> mp;

    auto find_first_overlap_it = [&](int l)->map<int,int>::iterator{
        auto it = mp.upper_bound(l);
        if(it!=mp.begin()){
            auto prev = it; --prev;
            if(prev->second >= l) return prev;
        }
        return it;
    };

    for(int i=0;i<n;++i){
        char op;
        cin >> op;
        if(op=='A'){
            int l,r; cin>>l>>r;
            // Count deletions of overlapping intervals
            int deleted = 0;
            auto it = find_first_overlap_it(l);
            // Move it to first candidate that might overlap [l,r]
            if(it!=mp.end()){
                // ensure it->first >= l or it is previous that overlaps; handled above
            }
            // Collect iterators to erase to avoid iterator invalidation issues
            vector<map<int,int>::iterator> toerase;
            // Check previous if upper_bound returned first with key>l but previous may overlap handled in find_first_overlap_it
            for(; it!=mp.end() && it->first <= r; ++it){
                // if this interval overlaps [l,r]
                if(it->second < l) continue; // shouldn't happen due to it start
                // Overlaps
                ++deleted;
                toerase.push_back(it);
            }
            for(auto &eit: toerase) mp.erase(eit);
            // Insert new interval [l,r]
            mp[l]=r;
            cout << deleted << '\n';
        }else if(op=='B'){
            cout << (int)mp.size() << '\n';
        }else{
            // undefined input; ignore line
            string rest; getline(cin, rest);
            --i; // try keep count, though not expected
        }
    }
    return 0;
}
