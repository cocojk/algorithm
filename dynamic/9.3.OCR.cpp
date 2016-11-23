
// 광학 문자 인식 문제를 해결하는 동적 계획법 알고리즘 

int n,m;
// 분류기가 반환한 문장 단어 번호로 되어 있음 
int R[100];
// T[i][j] = i 단어 이후에 j 단어가 나올 확률의 로그값 
double T[501][501];
// M[i][j] = i 단어가 j 단어로 분류될 확률의 로그 값 
double M[501][501];
// reconstrcut을 위해 저장하는 선택된 현재 단어 
int choice[102][502];
double cache[102][502]; // 1로 초기화 한다. 

// Q - 실제 단어, R - 광학기가 인식한 단어 
// P(Q|R) = 광학기가 인식한 단어가 R일 때, 실제 단어가 Q일 확률 
// P(Q|R) = ( P(R|Q) * P(Q) ) / P(R) 
// P(R) - 단어가 R일 확률 -> 이전 단어와 연관 있다. T[i][j] 값 가르킴 - 모든 경우에 대해서 동일 
// P(Q) - 단어가 Q일 확률 -> 이전 단어와 연관 있다. T[i][j] 값 가르킴 
// P(R|Q) - 실제단어가 Q일떄, 광학기가 인식한 단어가 R인 경우, -> M[i][j] 값 가르킴 
// 확률을 로그로 변환해 곱 연산에서 더하기 연산으로 변환 

// 현재 단어 index가 segment이고, 이전 단어가 previousMatch 일때
// P(R|Q) * P(Q)의 로그값을 반환한다. 
double recognize(int segment, int previousMatch) {
    if (segment == n)
        return 0;
    double* ret = &cache[segment][previousMatch];
    if (*ret != 1.0)
        return *ret;
    *ret = -e200; // log(0) = 음의 무한대에 해당하는 값 
    int* choose = choice[segment][previousMatch];
    
    // 현재 segment에서 대응되는 단어를 찾는다.
    for (int thisMatch = 0; thisMatch < m; thisMatch++) {
        double cand = T[previousMatch][thisMatch] + M[thisMatch][R[segment]] + recognize(segment+1,thisMatch);
        if (*ret < cand) {
            *ret = cand;
            choose = thisMatch;
        }
    }

    return *ret;
}

// 광학 문자 인식 문제의 실제 답 계산하기 
// 입력받은 단어들의 목록 
string corpus [501];
string reconstrcut(int segment, int previousMatch) {
    int choose = choice[segment][previousMatch];
    string ret = corpus[choose];
    if (segment < n-1)
        ret = ret + " " + reconstrcut(segment+1,choose);
    return ret;
}


