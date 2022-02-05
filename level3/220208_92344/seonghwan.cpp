/*
    <1> (r1,c1)~(r2, c2)�� �����Ѵٰ� �������� ��, ��ǻ� ����2�� + ġ��2���� �̷�����ٰ� ������
        ���ε��,
            1. Area1 - (r1,c1)~(N, M)�� ����
            2. Area2 - (r2 + 1, c1) ~ (N, M)�� ġ��(1�� �����̶� ����Ű�� ����. ��� ���� �����ϸ� �ȵǴ� �����ݾ�?)
            3. Area3 - (r1, c2 + 1) ~ (N, M)�� ġ��(1�� �����̶� ����Ű�� ����. ��� ���� �����ϸ� �ȵǴ� �����ݾ�?)
            4. Area4 - (r2 + 1, c2 + 1) ~ (N, M)�� ����(���� ����1�� ���ϰ� ġ�� 2�� �������� �ٽ� ���� 1�� �� ��� �ƹ��ϵ� �� �Ͼ�� ��)
            5. ġ���� ���� �ݴ��!!

    <2> ���� Ȥ�� ġ���� ���۵Ǵ� ��ǥ�� �����̳� ġ���� ũ�⸦ ���� �迭�� ����(leftTopAccumulationDegree).
    <3> �����̳� ���� ���� �� leftTopAccumulationDegree �迭�� <1>�� ��Ģ���� �� 4���� ������ ���� point�� degree�� ��ô����
    <4> ��ų�� ���� ������ �� �� leftTopAccumulationDegree �迭�� ���� �� ���� ������ �Ʒ��� ���������� degree�� Ȯ����� ������ �Ѵ�.
            1. ������� ��ǥ�� ���� ���� ���� ���� �����ش�.(���� ����� ����)
            2. ������� ��ǥ�� ���� ���� ���� ���� �����ش�.(���� ����� ����)
            3. ������� ��ǥ�� ���� ���� ���� ���� �� �ش�. �̴� 1, 2�� �����ϸ鼭 �ߺ��ؼ� ���� �������� ����. �ٽø��ؼ� [i - 1][j - 1]�� �ִ�
               ���� [i][j]�� 1���� �������� �Ѵ�.
    <5> <4>���� ������ ���� leftTopAccumulationDegree���� �� ��ǥ�� �ִ� �ǹ����� ���� �� �������� �����. ����ٰ� �ǹ��� �������� ����
    <6> <5>���� �Ϸ��� ���� �ǹ��� �������� 1 �̻��̸� answer++ �ϰ� 0���ϸ� �͸����Ǽ�
*/

#include <string>
#include <vector>

using namespace std;

int leftTopAccumulationDegree[1000][1000] = { 0, };//<2>�κ�. �ش� �迭�� ����ִ� ���� �ǹ̴� �ش� ��ǥ���� (N, M)����
                                                  //���� Ȥ�� ���� �� ũ�⸦ ���Ѵ�. �̴� skill�� ���� ������ ��ô�ȴ�.

int solution(vector<vector<int>> board, vector<vector<int>> skill) {

    int answer = 0;
    int sizeY = board.size();
    int sizeX = board.at(0).size();

    //<3>�κ�
    for (int i = 0; i < skill.size(); i++) {
        if (skill[i][0] == 2) skill[i][5] = -skill[i][5];//���� ��쿣 �ݴ�� ������ ��� �Ѵ�.

        leftTopAccumulationDegree[skill[i][1]][skill[i][2]] -= skill[i][5];//Area1

        if (skill[i][3] + 1 < sizeY)//Area2�� ���� ��쵵 ����
            leftTopAccumulationDegree[skill[i][3] + 1][skill[i][2]] += skill[i][5];//Area2
        if (skill[i][4] + 1 < sizeX)//Area3�� ���� ��쵵 ����
            leftTopAccumulationDegree[skill[i][1]][skill[i][4] + 1] += skill[i][5];//Area3
        if (skill[i][3] + 1 < sizeY && skill[i][4] + 1 < sizeX)//Area4�� ���� ��쵵 ����
            leftTopAccumulationDegree[skill[i][3] + 1][skill[i][4] + 1] -= skill[i][5];//Area4
    }

    //<4>�κ�
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            if (i - 1 >= 0) {
                leftTopAccumulationDegree[i][j] += leftTopAccumulationDegree[i - 1][j];//<4> - 1�κ�
            }
            if (j - 1 >= 0) {
                leftTopAccumulationDegree[i][j] += leftTopAccumulationDegree[i][j - 1];//<4> - 2�κ�
            }
            if (i - 1 >= 0 && j - 1 >= 0) {
                leftTopAccumulationDegree[i][j] -= leftTopAccumulationDegree[i - 1][j - 1];//<4> - 3�κ�
            }
        }
    }

    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            if (leftTopAccumulationDegree[i][j] + board[i][j] >= 1) answer++;//<5>�κ�, <6>�κ�
        }
    }

    return answer;
}