/*
    1. �ð� : 0.01ms~0.38ms
    2. �޸� : 4.33MB
    <Ǯ�� ���>
    task�� ó���Ǵ� �ð��� ���� ������ ���� ó�� �Ǿ����(�׷��� �ڿ� ��ٸ��� �ֵ��� ���ð� ����� �ּҰ� ��)
    =>�켱���� ť ���
    1. ���� �ð��� �ֱٿ� ���� task ���̿� �ִ� task���� ���� queue�� ����.
    2. queue�� �� �� ���� �۾��� ó�� �� �� task�� ���� �ð��� ���� �ð����� �� �ɸ� �ð� answer�� �߰�(���߿� ��������)
    3. queue�� �ִ� �۾��� ���� ó���� �� ����ð� update �� �ٽ� update�� ����ð��� ������ ���� task���̿� �ִ� task���� ���� queue�� ����(1�� ����)
    4. task�� ���δ� queue�� ���� �� ���� �ݺ� �� �ٽ� queue�� �� �� ���� task ó�� �ݺ�
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void ProcessRemainTask();
void ProcessAllTask();

// ���� �ð��뿡 ���� task�� �� �۾��ð��� ª�� �ֵ��� �տ� �;� �ϹǷ� ������ �����ε����� ������ �켱������
struct cmp {
    bool operator()(vector<int> a, vector<int> b) {
        return a[1] > b[1];
    }
};

priority_queue<vector<int>, vector<vector<int>>, cmp> diskQueue;//ó���� �۾��� �ִ� �켱����ť(top�� �� ����)
vector<vector<int>> jobs;
int answer = 0;
int processignTime = 0;   // ���� ���μ����� ó���ǰ��ִ� �ð�
int i = 0;

int solution(vector<vector<int>> jobsTemp) {
    sort(jobsTemp.begin(), jobsTemp.end()); // �۾��� ��û�Ǵ� ������ ���� ������ ����
    jobs = jobsTemp;

    ProcessAllTask();//��� task�� diskQueue�� �־� �׽�Ʈ�Ѵ�.
    answer = (int)(answer / jobs.size());

    return answer;  // ��� �ð� ��ȯ
}

void ProcessAllTask() {
    while (i < jobs.size()) {//task���� �� �ֱ� ������ �ݺ�
        if (jobs[i][0] <= processignTime) {// ���� �ð����� ������ ���� task���� ���� �켱����ť�� ����
            diskQueue.push(jobs[i]);
            i++;
            continue;
        }
        ProcessRemainTask();//�켱���� ť�� �ִ� �ֵ� �� ó����
    }
    while (!diskQueue.empty())
        ProcessRemainTask();//������ task���� ���� �� �켱����ť�� �����ִ� task ó����
}

void ProcessRemainTask() {
    if (!diskQueue.empty()) {// �켱����ť�� ó���ؾ� �� task�� �������� ��
        processignTime += diskQueue.top()[1];//���� �۾��� ó���� ������ ����ð��� �۾��� ������ �ð����� ����
        answer += (processignTime - diskQueue.top()[0]);//�ɸ��ð� �߰����ֱ�
        diskQueue.pop();
    }
    else processignTime = jobs[i][0];// task ������ �۾��� ���� ��� ���� �۾��� ������ �ð����� ����ð� ����  
}
