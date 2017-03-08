
// modular arithmetic 
// 모듈로(modulus) M에 도달하면 다시 0으로 돌아가는 정수들을 가지고 하는 연산 

// 모듈라 덧셈, 뺄셈 그리고 곱셈 
// 정수 a,b를 M으로 나눈 나머지가 각각 a`,b`라고 하면 이때 a+b를 M으로 나눈 나머지는 ? 
// a = xM + a` , b = yM + b` => a+b = (x+y)M + (a` + b`) => (a+b)%M = (a`+b`)%M 
// (a+b)%M = ((a%M)+(b%M))%M
// (a-b)%M = ((a%M)-(b%M))%M 
// (a*b)%M = ((a%M)*(b%M))%M 

// 모듈라 나눗셈 
// 위 공식 성립 X

// 확장 유클리드 알고리즘 
// 유클리드 알고리즘은 사실 한 수에서 다른 수를 빼는 과정을 반복하기 때문에 유클리드 알고리즘 gcd(p,q)을 
// 수행하는 도중에 출현하는 모든 수는 p,q의 가중치 합인 a*p + b*q으로 쓸 수 있다. 
// 예를 들어 15와 6의 최대 공약수를 구하는 과정은 다음과 같다. 
// gcd(6,15) = gcd(9,6) = gcd(3,6) = gcd(3,3) = gcd(0,3) = 3 
// gcd(9,6)에서 9는 15-6이고 gcd(3,6)에서의 3은 9-6 = (15-6)-6 = 15 - 2 * 6 이다.
// 이점을 이용하면 gcd(p,q) = a*p + b*q 

