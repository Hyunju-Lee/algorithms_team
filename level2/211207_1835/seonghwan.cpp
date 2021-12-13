#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void ArrangeDFS(int depth);
void CheckArrangementState();

bool isAlreadySat[8] = { false }; //�̹� �ɾ��ִ��� Ȯ��

char name[8] = { 'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T' };//��� �̴ϼ� ������� ����
char satName[8];//�ش� ��ȣ�� �ڸ��� ���� ��� �̴ϼ� ����


//���������� ����
int nTemp;
int answerTemp;
vector<string> dataTemp;

// ���� ������ ������ ��� �Լ� ���� �ʱ�ȭ �ڵ带 �� �ۼ����ּ���. �� ����
int solution(int n, vector<string> data) {
    //���������� ������ �̵�
    answerTemp = 0;
    nTemp = n;
    dataTemp = data;
    int answer;

    //��� ����Ǽ��� ã�´�. Permutation(8!)
    ArrangeDFS(0);

    //���� �Ű�����
    answer = answerTemp;

    return answer;
}


void ArrangeDFS(int depth) {

    if (depth == 8) {//���� �� ��ġ�� ���
        CheckArrangementState();//��� ������ �����ϴ� �༮���� Ȯ��
        return;
    }

    for (int i = 0; i < 8; i++) {       //i�� �ڸ���ȣ�� ����. �� ù��° �ڸ��������� Ȯ��
        if (isAlreadySat[i] == false) { //�������
            isAlreadySat[i] = true;     //������
            satName[i] = name[depth];   //�̸� ����ϰ�
            ArrangeDFS(depth + 1);      //���� �༮ ������!
            isAlreadySat[i] = false;    //�ǵ��ƿͼ� ���� ���� ����
        }
    }
}

void CheckArrangementState() {
    unordered_map<char, int> location;  //������ ����� �� ��° ���ڿ� �ɾҴ��� ����ϴ� �ؽø�

    for (int i = 0; i < 8; i++) {
        location[satName[i]] = i;       //���� �� ��°�� �ɾҴ°�?
    }

    int loc1, loc2;     //�� �༮�� ��ġ
    int distance;       //�� �༮ ���̿� �� �� �ִ���

    for (int i = 0; i < nTemp; i++) {
        //��ġ���� ����
        loc1 = location[dataTemp[i][0]];
        loc2 = location[dataTemp[i][2]];

        //�Ÿ� ���
        if (loc1 >= loc2) {
            distance = loc1 - loc2 - 1;
        }
        else {
            distance = loc2 - loc1 - 1;
        }

        //���� �����ϴ��� Ȯ��. �ϳ��� ���� ���ϸ� �ٷ� �Լ� ���� �� ���� ������ ������ ����.
        switch (dataTemp[i][3]) {
        case '=': if (distance != ((int)dataTemp[i][4] - 48)) return; break;
        case '<': if (distance >= ((int)dataTemp[i][4] - 48)) return; break;
        case '>': if (distance <= ((int)dataTemp[i][4] - 48)) return; break;
        default:                                                      break;
        }
    }
    answerTemp++; //�̱��� �Դٸ� ��� ������ ������ ���̴� ����++
}