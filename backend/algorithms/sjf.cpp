#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Task {
    int id;
    int arrivalTime;
    int burstTime;
};

bool compareBurstTime(Task a, Task b) {
    return a.burstTime < b.burstTime;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    int numTasks;
    inputFile >> numTasks;
    std::vector<Task> taskList(numTasks);
    for (int i = 0; i < numTasks; ++i) {
        inputFile >> taskList[i].id >> taskList[i].arrivalTime >> taskList[i].burstTime;
    }

    std::sort(taskList.begin(), taskList.end(), compareBurstTime);

    std::vector<int> waitingTime(numTasks), turnaroundTime(numTasks), responseTime(numTasks);
    int timeElapsed = 0;
    for (int i = 0; i < numTasks; ++i) {
        if (timeElapsed < taskList[i].arrivalTime) {
            timeElapsed = taskList[i].arrivalTime;
        }
        waitingTime[i] = timeElapsed - taskList[i].arrivalTime;
        turnaroundTime[i] = waitingTime[i] + taskList[i].burstTime;
        responseTime[i] = waitingTime[i];
        timeElapsed += taskList[i].burstTime;
    }

    double totalWaitTime = 0, totalTurnaroundTime = 0, totalResponseTime = 0;
    for (int i = 0; i < numTasks; ++i) {
        totalWaitTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        totalResponseTime += responseTime[i];
    }
    double avgWaitTime = totalWaitTime / numTasks;
    double avgTurnaroundTime = totalTurnaroundTime / numTasks;
    double avgResponseTime = totalResponseTime / numTasks;

    outputFile << avgWaitTime << std::endl;
    outputFile << avgTurnaroundTime << std::endl;
    outputFile << avgResponseTime << std::endl;

    return 0;
}
