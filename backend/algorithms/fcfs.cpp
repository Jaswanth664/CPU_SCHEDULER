#include <iostream>
#include <vector>
#include <fstream>

int main() {
    int n;
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    input >> n;
    std::vector<int> arrival_time(n), burst_time(n);
    for (int i = 0; i < n; ++i) {
        input >> arrival_time[i] >> burst_time[i];
    }

    std::vector<int> wait_time(n), turn_time(n), resp_time(n);
    int time_elapsed = 0;

    for (int i = 0; i < n; ++i) {
        if (time_elapsed < arrival_time[i]) {
            time_elapsed = arrival_time[i];
        }
        wait_time[i] = time_elapsed - arrival_time[i];
        turn_time[i] = wait_time[i] + burst_time[i];
        resp_time[i] = wait_time[i];
        time_elapsed += burst_time[i];
    }

    double total_wait_time = 0.0, total_turn_time = 0.0, total_resp_time = 0.0;
    for (int i = 0; i < n; ++i) {
        total_wait_time += wait_time[i];
        total_turn_time += turn_time[i];
        total_resp_time += resp_time[i];
    }

    double avg_wait_time = total_wait_time / n;
    double avg_turn_time = total_turn_time / n;
    double avg_resp_time = total_resp_time / n;

    output << "Average Waiting Time: " << avg_wait_time << std::endl;
    output << "Average Turnaround Time: " << avg_turn_time << std::endl;
    output << "Average Response Time: " << avg_resp_time << std::endl;

    return 0;
}
