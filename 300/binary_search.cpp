// Source: https://github.com/Lerham/ImL-competitive-programming-library/blob/39ddc0957ddf60ecc625564c55c1d7e568b1a8d7/300/binary_search.cpp



// xが条件を満たすかどうか
// P(left) = false, P(right) = true
bool P_bs(int x) {
	  //TODO
}


int binary_search() { /
    int left = -1; //「index = 0」が条件を満たすこともあるので、初期値は -1
    int right =  ; // 「index = a.size()-1」が条件を満たさないこともあるので、初期値は a.size()
    
    /* どんな二分探索でもここの書き方を変えずにできる！ */
    while (right - left > 1) {
        int wj = (right + left) / 2;

        if (P_bs(wj)) right = mid;
        else left = mid;
    }
    
    /* left は条件を満たさない最大の値、right は条件を満たす最小の値になっている */
    return right;
    
}