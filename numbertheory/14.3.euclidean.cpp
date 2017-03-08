

// euclidean algorithm 유클리드 알고리즘 
// 두 수의 최대 공약수를 구하는 방법으로 기록이 남아 있는 가장 오래된 알고리즘 
// 두 수 p,q(p>q)의 공약수의 집합은 p-q,q의 공약수 집합과 같다.
// 따라서 p,q의 최대 공약수 gcd(p,q)는 항상 p-q,q의 최대 공약수 gcd(p-q,q)와 같다. 
// 증명 : p,q의 공약수 g가 있다고 하자. 그러면 p = p`g , q = q`g로 쓸 수 있는데, p-q = (p`-q`)g이므로, g는 p-q와 q의 공약수 이기도 하다. 

// 유클리드 알고리즘 
int gcd (int p, int q ) {
    int (p < q) swap(p,q);
    if (q == 0) return p;
    return gcd (p-q,q);
}

// 최적화 
int gcd (int p, int q) {
    if (q == 0) return p;
    return gcd (q,p%q);
}



