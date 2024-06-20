#include <bits/stdc++.h>
#define SIZE(a) static_cast<int>((a).size())
#define uchar unsigned char

using namespace std; 
typedef long long ll;
typedef long double ld;

struct Task {
    int id;
    int arrivalTime;
    int burstTime;
    int finishTime;
    int turnaroundTime;
    int waitTime;
    int responseTime;
};

bool sortByArrival(const Task &a, const Task &b) {
    return a.arrivalTime < b.arrivalTime || (a.arrivalTime == b.arrivalTime && a.id < b.id);
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    int totalTasks, quantum;
    inputFile >> totalTasks;
    
    vector<Task> tasks(totalTasks);
    for (int i = 0; i < totalTasks; ++i) {
        inputFile >> tasks[i].id >> tasks[i].arrivalTime >> tasks[i].burstTime;
    }
    inputFile >> quantum;
    
    sort(tasks.begin(), tasks.end(), sortByArrival);
    queue<Task> taskQueue;
    unordered_map<int, int> finishTimeMap;
    unordered_map<int, int> firstExecMap;

    int currentTime = 0, taskIndex = 0;
    currentTime = max(currentTime, tasks[taskIndex].arrivalTime);
    
    while (taskIndex < totalTasks && tasks[taskIndex].arrivalTime <= currentTime) {
        taskQueue.push(tasks[taskIndex]);
        ++taskIndex;
    }
    
    while (!taskQueue.empty() || taskIndex < totalTasks) {
        if (taskQueue.empty()) {
            currentTime = tasks[taskIndex].arrivalTime;
            continue;
        }

        Task currentTask = taskQueue.front();
        taskQueue.pop();
        if (firstExecMap.find(currentTask.id) == firstExecMap.end()) {
            firstExecMap[currentTask.id] = currentTime;
        }

        bool isFinished = false;
        if (currentTask.burstTime <= quantum) {
            currentTime += currentTask.burstTime;
            isFinished = true;
            finishTimeMap[currentTask.id] = currentTime;
        } else {
            currentTime += quantum;
            currentTask.burstTime -= quantum;
        }
        
        while (taskIndex < totalTasks && tasks[taskIndex].arrivalTime <= currentTime) {
            taskQueue.push(tasks[taskIndex]);
            ++taskIndex;
        }

        if (!isFinished) {
            taskQueue.push(currentTask);
        }
    }

    for (auto &task : tasks) {
        task.finishTime = finishTimeMap[task.id];
        task.turnaroundTime = task.finishTime - task.arrivalTime;
        task.waitTime = task.turnaroundTime - task.burstTime;
        task.responseTime = firstExecMap[task.id] - task.arrivalTime;
    }
    
    ld totalWaitTime = 0, totalResponseTime = 0, totalTurnaroundTime = 0;
    for (const auto &task : tasks) {
        totalWaitTime += task.waitTime;
        totalResponseTime += task.responseTime;
        totalTurnaroundTime += task.turnaroundTime;
    }
    
    ld avgWaitTime = totalWaitTime / totalTasks;
    ld avgTurnaroundTime = totalTurnaroundTime / totalTasks;
    ld avgResponseTime = totalResponseTime / totalTasks;
    
    outputFile << avgWaitTime << endl;
    outputFile << avgTurnaroundTime << endl;
    outputFile << avgResponseTime << endl;

    return 0;
}
