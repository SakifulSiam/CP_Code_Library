// WHEN: offline range queries mixed with point assignments. TIME: about O((N+Q)N^(2/3)) moves. ASSUMES: 0-based inclusive ranges; each update records before/after values and each query its update-time.
// Offline range queries with point assignments. Example maintained answer: range sum.
struct MoUpdate { int pos, before, after; };
struct MoQuery3D { int l,r,time,id; };
vector<long long> moWithUpdates(vector<int> a,const vector<MoUpdate>& updates,vector<MoQuery3D> qs) {
    int n=a.size(), block=max(1,(int)pow(max(1,n),2.0/3));
    sort(qs.begin(),qs.end(),[&](auto x,auto y){
        int bx=x.l/block,by=y.l/block; if(bx!=by)return bx<by;
        int br=x.r/block,cr=y.r/block; if(br!=cr)return (bx&1)?br>cr:br<cr;
        return (br&1)?x.time>y.time:x.time<y.time;
    });
    vector<long long> ans(qs.size()); int L=0,R=-1,T=0; long long cur=0;
    auto add=[&](int i){cur+=a[i];}; auto remove=[&](int i){cur-=a[i];};
    auto apply=[&](int idx,bool forward){auto u=updates[idx]; int value=forward?u.after:u.before;
        if(L<=u.pos&&u.pos<=R) remove(u.pos); a[u.pos]=value; if(L<=u.pos&&u.pos<=R) add(u.pos);};
    for(auto q:qs) {
        while(T<q.time) apply(T++,true); while(T>q.time) apply(--T,false);
        while(L>q.l)add(--L); while(R<q.r)add(++R); while(L<q.l)remove(L++); while(R>q.r)remove(R--);
        ans[q.id]=cur;
    }
    return ans;
}
