#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

struct Task {
    int taskId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    int taskCount;
    inputFile >> taskCount;
    std::vector<Task> taskList(taskCount);
    for (int i = 0; i < taskCount; ++i) {
        inputFile >> taskList[i].taskId >> taskList[i].arrivalTime >> taskList[i].burstTime;
        taskList[i].remainingTime = taskList[i].burstTime;
    }

    std::vector<int> waitingTimes(taskCount), turnaroundTimes(taskCount), responseTimes(taskCount, -1);
    int currentTime = 0, completedTasks = 0;

    while (completedTasks < taskCount) {
        int currentTaskIndex = -1;
        int shortestRemaining = INT_MAX;

        for (int i = 0; i < taskCount; ++i) {
            if (taskList[i].arrivalTime <= currentTime && taskList[i].remainingTime > 0 && taskList[i].remainingTime < shortestRemaining) {
                shortestRemaining = taskList[i].remainingTime;
                currentTaskIndex = i;
            }
        }

        if (currentTaskIndex != -1) {
            if (responseTimes[currentTaskIndex] == -1) {
                responseTimes[currentTaskIndex] = currentTime - taskList[currentTaskIndex].arrivalTime;
            }
            currentTime++;
            taskList[currentTaskIndex].remainingTime--;
            if (taskList[currentTaskIndex].remainingTime == 0) {
                completedTasks++;
                waitingTimes[currentTaskIndex] = currentTime - taskList[currentTaskIndex].arrivalTime - taskList[currentTaskIndex].burstTime;
                turnaroundTimes[currentTaskIndex] = currentTime - taskList[currentTaskIndex].arrivalTime;
            }
        } else {
            currentTime++;
        }
    }

    double totalWaitingTime = 0, totalTurnaroundTime = 0, totalResponseTime = 0;
    for (int i = 0; i < taskCount; ++i) {
        totalWaitingTime += waitingTimes[i];
        totalTurnaroundTime += turnaroundTimes[i];
        totalResponseTime += responseTimes[i];
    }
    double averageWaitingTime = totalWaitingTime / taskCount;
    double averageTurnaroundTime = totalTurnaroundTime / taskCount;
    double averageResponseTime = totalResponseTime / taskCount;

    outputFile << averageWaitingTime << std::endl;
    outputFile << averageTurnaroundTime << std::endl;
    outputFile << averageResponseTime << std::endl;

    return 0;
}
