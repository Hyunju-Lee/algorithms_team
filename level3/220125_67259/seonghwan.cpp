/*
    ����ð� : 0.01ms~0.48ms, �޸� : 3.67MB~4.35MB
    1. bfs�� Ǯ����.
    2. ���θ� �Ǽ��Ѵٱ� ����, ���� �̵��ϸ� ����Ḧ ���ٰ� �����ϴ°� ��������(���� : 100��, �ڳ� : 500���� ����� ����)
    2. ������� �����ִ� bfs�� �����ؾ��ϸ�, Ư�� ��ǥ���� ���µ��� ��� cost�� ���� �˻����� ������
       �۴ٰ� �ϴ��� ���� ������ �ֱ� ������ ������� �Բ� �ؼ� ��� �� ��� �Ѵ�.
    3. ���� y, x, ������� �����ִ� 3���� �迭�� Ȱ����.(25x25x4 = 2500�̶� ���� ũ�� �ʱ⶧��)
*/

#include <string>
#include <vector>
#include <queue>

using namespace std;

void ResetTotalCostBoard();

enum {
    up,
    down,
    left,
    right,
    none = -1
};

typedef struct {         //�ڵ����� ������ ����
    int y;              //���� y��ǥ
    int x;              //���� x��ǥ
    int direction;      //���� ���� �޸��� �ִ� ����()
    int totalCost;      //�� ��ġ�� �� �� ���� ��� ���(���� �Ǽ����)
} Car;

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };//�����¿�
int totalCostBoard[25][25][4];//Ư�� ��ǥ�� Ư�� ���⿡�� ���� ���� ��, �� ���� �� ������� ���� �� �ּڰ��� �����ϴ� �迭
                              //y, x, �ش� ��ǥ�� ������ ���� �ڵ��� ����(enum�̶� ����)


int solution(vector<vector<int>> board) {
    int answer = 10000000; int boardSize = board.size();
    queue<Car> q;
    Car carTemp = { 0, 0, none, 0 };                //�� ó�� ���� ��� ��ġ
    q.push(carTemp);

    ResetTotalCostBoard();                          

    while (q.empty() != true) {
        carTemp = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {               //�����¿�
            Car car;                                //�� ���� �� ��ǥ�� ���� ���� ��(carTemp�� ���� ��ǥ�� �ִ� ��)
            car.y = carTemp.y + dy[i];              //���� ���� �� ��ǥ�� ����(���� �� �� ������ ��)
            car.x = carTemp.x + dx[i];
            car.direction = i;                      //���� ���� ��ǥ���� ���� �� ��ǥ�� �������� ����

            if (car.y < 0 || car.x < 0 || car.y >= boardSize || car.x >= boardSize) continue;//���� ���̴� �о�
            if (board[car.y][car.x] == 1) continue;                                          //���� ������ �о�

            if (carTemp.direction == none || carTemp.direction == car.direction) //ó�� ���(none)�� ���, ������ ���
                car.totalCost = carTemp.totalCost + 100;                         //���� �Ǽ������ �����ش�.
            else                                                                 //�װ� �ƴ϶�� �ڳ��̱� ������
                car.totalCost = carTemp.totalCost + 100 + 500;                   //�ڳ� �Ǽ���� + ���� �Ǽ������ �����ش�.

            if (totalCostBoard[car.y][car.x][car.direction] > car.totalCost) {   //���� �� ��ǥ�� ���� �������� �Դ� �ְ� �Ǽ������ �� ũ�ٸ�
                totalCostBoard[car.y][car.x][car.direction] = car.totalCost;     //���� �� ��ǥ�� �� �Ǽ������ �������ش�.
                q.push(car);
            }
        }
    }


    for (int i = 0; i < 4; i++) {//���������� ��ǥ���� �����¿� �������� ������ �� ���� ��� �� ���� cost�� ã�Ƽ� ������ �ؾ���
        if (totalCostBoard[boardSize - 1][boardSize - 1][i] < answer)
            answer = totalCostBoard[boardSize - 1][boardSize - 1][i];
    }

    return answer;
}

void ResetTotalCostBoard() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            for (int k = 0; k < 4; k++) {
                totalCostBoard[i][j][k] = 10000000;//i, j�� ���� y, x�� ��ǥ, k�� �ش� ��ǥ�� ���� ������ ���� ����(enum����)
            }
        }
    }
}