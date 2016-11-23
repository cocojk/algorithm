
/*
   문제

   Best White is a mathematics graduate student at T1 University. Recently, he finished writing a paper and he decided to polish it. As he started to read it from the beginning, he realized that some of the formulas have problems: some of the brackets are mismatched! Since there are so many formulas in his paper, he decided to check their validity with a computer program.

   The following kinds of brackets are included in Best White’s paper.

   Round brackets are opened by a ( and closed by a ).
   Curly brackets are opened by a { and closed by a }.
   Square brackets are opened by a [ and closed by a ].
   A formula is said well-matched when the following conditions are met:

   Every bracket has a corresponding pair. ( corresponds to ), [ corresponds to ], et cetera.
   Every bracket pair is opened first, and closed later.
   No two pairs "*cross*" each other. For example, [(]) is not well-matched.
   Write a program to help Best White by checking if each of his formulas is well-matched. To make the problem easier, everything other than brackets are removed from the formulas.

   입력

   The first line of the input will contain the number of test cases C (1≤C≤100). Each test is given in a single line as a character string. The strings will only include characters in "[](){}" (quotes for clarity). The length of the string will not exceed 10,000.

   출력

   For each test case, print a single line "YES" when the formula is well-matched; print "NO" otherwise. (quotes for clarity)

   예제 입력

   3
   ()()
   ({[}])
   ({}[(){}])
   예제 출력

   YES
   NO
   YES
*/

// 스택을 이용한 짝이 맞지 않는 괄호 문제를 해결하는 알고리즘의 구현 

bool wellMatched (const string& formula) {
    // 여는 괄호 문자들과 닫는 괄호 문자들 
    const string opening("({["), closing (")}]");
    // 이미 열린 괄호들을 순서대로 담는 스택 
    stack<char> openStack;
    for (int i = 0; i < formula.size(); i++) 
    {
        // 여는 괄호인지 닫는 괄호인지 확인한다.
        if (opening.find(formula[i]) != -1)
            // 여는 괄호라면 무조건 스택에 집어 넣는다.
            openStack.push(formula[i]);
        else {
            // 이외의 경우 스택 맨 위의 문자와 맞춰보자.
            // 스택이 비어 있는 경우에는 실패 
            if (openStack.empty()) return false;
            // 서로 짝이 맞지 않아도 실패 
            if (opening.find(openStack.top()) != closing.find(formula[i]))
                return false;
            // 짝을 맞춘 괄호는 스택에서 뺀다.
            openStack.pop();
        }

    }

    // 닫히지 않은 괄호가 없어야 성공 
    return openStack.empty();
}


#include <stdio.h>
#include <stack>

#define LEFTROUND '('
#define RIGHTROUND ')'
#define LEFTCURLY '{'
#define RIGHTCURLY '}'
#define LEFTSQUARE '['
#define  RIGHTSQUARE ']'

using namespace std;

void solve()
{
    char buffer [10001];
    char* input = buffer;
    char match;
    stack <char> st;

    scanf("%s",buffer);
    while( *input !='\0')
    {
        if (*input == LEFTROUND || *input== LEFTCURLY || *input == LEFTSQUARE)
            st.push((*input));
        else
        {
            if (st.empty())
            {
                printf("NO\n");
                return;
            }

            match = st.top();
            st.pop();
            if ( !((match == LEFTROUND && *input == RIGHTROUND) || (match == LEFTCURLY && *input == RIGHTCURLY) || (match == LEFTSQUARE && *input == RIGHTSQUARE)))
            { 
                printf("NO\n");
                return;
            }
        }
    
        input++;
    }

    if (st.empty())
       printf("YES\n");
    else 
        printf("NO\n");
}

int main (void)
{
    int testcase;
    char temp;
    scanf("%d",&testcase);

    while(testcase--)
    {
        solve();
    }
}








