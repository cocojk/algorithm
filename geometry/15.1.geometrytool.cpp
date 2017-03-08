
// vector 

// 코드 15.1 2차원 벡터를 표현하는 vector2 클래스의 구현 

const double PI = 2.0 * acos(0.0);

// 2차원 벡터를 표현한다.

struct vector2 {
    double x,y;
    // 생성자를 explicit으로 지정하면 vector2를 넣을 곳에 잘못해 
    // 실수가 들어가는 일을 방지해준다.
    explicit vector2 (double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

    // 두 벡터의비교 
    bool operator == (const vector2& rhs) const { 
        return x == rhs.x && y == rhs.y;
    }

    bool operator < (const vector2& rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }

    // 벡터의 덧셈과 뺄셈 
    vector2 operator + (const vector2& rhs) const {
        return vector2 (x + rhs.x, y + rhs.y);
    }

    vector2 operator - (const vector2& rhs) const {
        return vector2 (x -rhs.x,y-rhs.y);
    }

    // 실수로 곱셈 
    vector2 operator * (double rhs) const { 
        return vetor2 ( x*rhs,y*rhs);
    }

    // 벡터의 길이를 반환한다.
    double norm() const { return hypot(x,y); }

    // 방향이 같은 단위 벡터 (unit vector)를 반환한다.
    // 영벡터에 대해 호출한 경우 반환값은 정의되지 않는다.
    vector2 normalize() const {
        return vector2 (x/norm(),y/norm());
    }

    // x축의 양의 방향으로부터 이 벡터까지 반 시계 방향으로 잰 각도 
    double polar() const { return fmod(atan2(y,x) + 2*PI,2*PI); }

    // 내적/외적의 구현 
    double dot (const vector2& rhs) const { 
        return x * rhs.x + y * rhs.y;
    }

    double cross (const vector2& rhs) const {
        return x* rhs.y - rhs.x*y;
    }

    // 이 벡터를 rhs에 사영한 결과 
    vector2 project (const vector2& rhs) const {
        vector2 r = rhs.normalize();
        return r * r.dot(*this);
    }
};

// 점과 직선, 선분의 표현 
// 벡터를 이용하면 점과 직선 선분을 간편하게 표현할 수 있다. 
// 벡터를 기준으로 생각하는 것이 많은 경우 코드를 간결하게 하고 문제를 푸는 데 강력한 도구가 된다.
// 점 : 해당 점을 끝 점으로 갖는 벡터 
// 선분 : 두 개의 끝점을 두 개의 벡터로 표현 
// 직선 : 직선에 포함된 임의의 선분을 이용해 표현 

// 예를 들어, 세 개의 점 p,a,b가 주어졌을 때 a가 b보다 p에 얼마나 더 가까운지 반환하는 함수 

double howMuchCloser (vector2 p, vector2 a, vector2 b) {
    return (b - p).norm() - (a-p).norm();
}

double howMuchCloser (double px, double py, double ax, double ay, double bx, double xy) {
    return sqrt ((bx-px)*(bx-px) + (by-py) * (by-py)) - sqrt ((ax-px)*(ax-px) + (ay-py)*(ay-py));
}

// 벡터의 내적과 외적 
// 1. inner product 
// a dot b = ax * bx + ay* by = |a| * |b| * cosx 
// x = 두 벡터 사이의 각도 
// 용도 
// 1. 벡터의 사이각 구하기 
// x = acos ( (a dot b)/(|a| * |b|) ) 
// 2. 벡터의 직각 여부 확인하기 
// 내적이 0이면 두 벡터는 항상 직각이다. 
// 3. project 
// 벡터 b에 수직으로 빛이 내리쬘 때, 벡터 a가 b 위에 드리우는 그림자 
// 이 벡터의 길이 = |a|cosx = (a dot b)/|b| 

// 2. cross product 
// 3차원 벡터에 대해 정의되는 연산으로 3차원 벡터 a,b가 주어졌을 때 이 두 벡터에 모두 수직인 다른 벡터를 반환 
// 2차원 벡터에 대해서도 외적을 정의할 수 있다. (z = 0 고정) 
// a x b = ax * by - ay*bx = |a|*|b||sinx 
// 용도 
// 1. 면적 계산하기 
// 외적의 절대 값은 a,b를 두변으로 하는 평행 사변형의 넓이 
// 2. 두 벡터의 방향 판별 
// x는 단순히 두 벡터의 사이각이 아니라 a에서 b까지의 반시계 방향으로 얼마나 회전해야 하는가를 나타낸다. 
// a x b > 0 : b가 a로부터 반시계 방향으로 180도 이내에 있다.
// a x b < 0 : b가 a로부터 시계 방향으로 180도 이내에 있다. 

// 코드 15.2 두 벡터의 방향성을 판단하는 ccw() 함수의 구현 

// 원점에서 벡터 b가 벡터 a의 반시계 방향으로 양수, 시계 방향이면 음수 
// 평행이면 0을 반환한다.
double ccw (vector2 a, vector2 b) {
    return a.cross(b);
}

// 점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계 방향이면 음수 
// 평행이면 0을 반환한다.
double ccw (vector2 p, vector2 a, vector2 b) {
    return ccw(a-p,b-p);
}



