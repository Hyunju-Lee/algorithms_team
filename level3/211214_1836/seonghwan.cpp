#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> boardTemp;
vector<tuple<char, int, int>> sortedNameInCurrentBoard;
string answerTemp;
int mTemp;
int nTemp;



void SortName();
void FindAnswer();
bool CheckConnection(int, int, int, int, int);
bool CheckGoVertical(int, int, int, int);
bool CheckGoHorizontal(int, int, int, int);




string solution(int m, int n, vector<string> board) {

    ////////////////�������� �ʱ�ȭ ����///////////////
    string answer = "";
    boardTemp = board;
    answerTemp = answer;
    mTemp = m;
    nTemp = n;
    vector<tuple<char, int, int>> resetVector;
    sortedNameInCurrentBoard = resetVector;
    ////////////////////////////////////////////////

    SortName();
    FindAnswer();

    answer = answerTemp;

    return answer;
}

void SortName() {//���ĺ��� ���ĵǰ�, �� ���� ������ ���ĺ��� ������ ���� �ȴ�.

    for (int i = 0; i < mTemp; i++) {
        for (int j = 0; j < nTemp; j++) {
            if (boardTemp[i][j] != '.' && boardTemp[i][j] != '*') {
                sortedNameInCurrentBoard.push_back({ boardTemp[i][j], i, j });
            }
        }
    }

    sort(sortedNameInCurrentBoard.begin(), sortedNameInCurrentBoard.end());
}

void FindAnswer() {

    for (int i = 0; i < sortedNameInCurrentBoard.size(); i = i + 2) {
        if (CheckConnection(get<1>(sortedNameInCurrentBoard.at(i)), get<1>(sortedNameInCurrentBoard.at(i + 1)),
            get<2>(sortedNameInCurrentBoard.at(i)), get<2>(sortedNameInCurrentBoard.at(i + 1)), i) == true)//�� ��ǥ�� ���ᰡ���ϸ�
        {
            sortedNameInCurrentBoard.erase(sortedNameInCurrentBoard.begin() + i);//���ĺ� ����
            sortedNameInCurrentBoard.erase(sortedNameInCurrentBoard.begin() + i);//�ΰ� �����״� �ѹ� �� ����
            i = -2;//������ ���ĺ��� ����� �ٽ� ù ���ĺ����� �˻��ϱ� ����
        }//�� ��ǥ�� ���� �Ұ��� �ϸ� ���� ���ĺ����� �Ѿ
    }

    if (sortedNameInCurrentBoard.size() != 0) {
        answerTemp = "IMPOSSIBLE";//���� �� ���� ���ĺ��� ���������� �� �� �����
    }

}

bool CheckConnection(int y1, int y2, int x1, int x2, int nameLocation) {

    //���η� ���ڷ� �����ִ� ���
    if (y1 != y2 && x1 == x2) {
        int yLow;
        int yHigh;
        if (y1 > y2) {
            yLow = y2;
            yHigh = y1;
        }
        else {
            yLow = y1;
            yHigh = y2;
        }
        for (int i = yLow + 1; i <= yHigh - 1; i++) {
            if (boardTemp[i][x1] == '.')continue;
            else return false;//���߿� �ٸ� ���ĺ��̳� ���� ���� �߰� �� ��� ����! �ε�Ź
        }
        answerTemp = answerTemp + boardTemp[y1][x1];
        boardTemp[y1][x1] = '.';
        boardTemp[y2][x2] = '.';
        return true;
    }

    //���η� ���ڷ� �����ִ� ���
    if (y1 == y2 && x1 != x2) {
        int xLow;
        int xHigh;
        if (x1 > x2) {
            xLow = x2;
            xHigh = x1;
        }
        else {
            xLow = x1;
            xHigh = x2;
        }
        for (int i = xLow + 1; i <= xHigh - 1; i++) {
            if (boardTemp[y1][i] == '.')continue;
            else return false;
        }
        answerTemp = answerTemp + boardTemp[y1][x1];
        boardTemp[y1][x1] = '.';//�� ���� �Դٴ� �� ��ֹ��� �����ٴ� ���̹Ƿ� ����~
        boardTemp[y2][x2] = '.';
        return true;
    }



    if (y1 != y2 && x1 != x2) {
        if (CheckGoHorizontal(y1, y2, x1, x2) == true) return true;
        else if (CheckGoVertical(y1, y2, x1, x2) == true)return true;
        else return false;
    }


}

//y1,x1 ��ǥ���� �������� ����ϴ� ��� ����
bool CheckGoVertical(int y1, int y2, int x1, int x2) {


    if (y2 > y1 && x2 > x1) {             //y1,x1 ���� ���� y2,x2 ���� ��� ����
        for (int i = y1 + 1; i <= y2; i++) {
            if (boardTemp[i][x1] == '.') continue;
            else return false;
        }
        for (int i = x1 + 1; i < x2; i++) {
            if (boardTemp[y2][i] == '.') continue;
            else return false;
        }
        answerTemp = answerTemp + boardTemp[y1][x1];
        boardTemp[y1][x1] = '.';
        boardTemp[y2][x2] = '.';
        return true;
    }
    else if (y2 > y1 && x1 > x2) {       //y1,x1 ���� ���� y2,x2 ���� ��� ����
        for (int i = y1 + 1; i <= y2; i++) {
            if (boardTemp[i][x1] == '.') continue;
            else return false;
        }
        for (int i = x1 - 1; i > x2; i--) {
            if (boardTemp[y2][i] == '.') continue;
            else return false;
        }
        answerTemp = answerTemp + boardTemp[y1][x1];
        boardTemp[y1][x1] = '.';
        boardTemp[y2][x2] = '.';
        return true;
    }
    else if (y1 > y2 && x1 > x2) {       //y1,x1 ���� ���� y2,x2 ���� ��� ����
        for (int i = y1 - 1; i >= y2; i--) {
            if (boardTemp[i][x1] == '.') continue;
            else return false;
        }
        for (int i = x1 - 1; i > x2; i--) {
            if (boardTemp[y2][i] == '.') continue;
            else return false;
        }
        answerTemp = answerTemp + boardTemp[y1][x1];
        boardTemp[y1][x1] = '.';
        boardTemp[y2][x2] = '.';
        return true;
    }
    else {                              //y1,x1 ���� ���� y2,x2 ���� ��� ����
        for (int i = y1 - 1; i >= y2; i--) {
            if (boardTemp[i][x1] == '.') continue;
            else return false;
        }
        for (int i = x1 + 1; i < x2; i++) {
            if (boardTemp[y2][i] == '.') continue;
            else return false;
        }
        answerTemp = answerTemp + boardTemp[y1][x1];
        boardTemp[y1][x1] = '.';
        boardTemp[y2][x2] = '.';
        return true;
    }
}

//y1,x1 ��ǥ���� �������� ����ϴ� ��� ����
bool CheckGoHorizontal(int y1, int y2, int x1, int x2) {

    if (y2 > y1 && x2 > x1) {             //y1,x1 ���� ���� y2,x2 ���� ��� ����
        for (int i = x1 + 1; i <= x2; i++) {
            if (boardTemp[y1][i] == '.') continue;
            else return false;
        }
        for (int i = y1 + 1; i < y2; i++) {
            if (boardTemp[i][x2] == '.') continue;
            else return false;
        }
        answerTemp = answerTemp + boardTemp[y1][x1];
        boardTemp[y1][x1] = '.';
        boardTemp[y2][x2] = '.';
        return true;
    }
    else if (y2 > y1 && x1 > x2) {       //y1,x1 ���� ���� y2,x2 ���� ��� ����
        for (int i = x1 - 1; i >= x2; i--) {
            if (boardTemp[y1][i] == '.') continue;
            else return false;
        }
        for (int i = y1 + 1; i < y2; i++) {
            if (boardTemp[i][x2] == '.') continue;
            else return false;
        }
        answerTemp = answerTemp + boardTemp[y1][x1];
        boardTemp[y1][x1] = '.';
        boardTemp[y2][x2] = '.';
        return true;
    }
    else if (y1 > y2 && x1 > x2) {       //y1,x1 ���� ���� y2,x2 ���� ��� ����
        for (int i = x1 - 1; i >= x2; i--) {
            if (boardTemp[y1][i] == '.') continue;
            else return false;
        }
        for (int i = y1 - 1; i > y2; i--) {
            if (boardTemp[i][x2] == '.') continue;
            else return false;
        }
        answerTemp = answerTemp + boardTemp[y1][x1];
        boardTemp[y1][x1] = '.';
        boardTemp[y2][x2] = '.';
        return true;
    }
    else {                              //y1,x1 ���� ���� y2,x2 ���� ��� ����
        for (int i = x1 + 1; i <= x2; i++) {
            if (boardTemp[y1][i] == '.') continue;
            else return false;
        }
        for (int i = y1 - 1; i > y2; i--) {
            if (boardTemp[i][x2] == '.') continue;
            else return false;
        }
        answerTemp = answerTemp + boardTemp[y1][x1];
        boardTemp[y1][x1] = '.';
        boardTemp[y2][x2] = '.';
        return true;
    }
}


