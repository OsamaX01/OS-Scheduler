#include <iostream> 
#include <algorithm>
#include <vector>
#include <set>

typedef long long int_64;
using namespace std;

struct Process {
    string name;
    int arrival_time;
    int processing_time;
    int priority;
    int index;

    struct Compare final {
        bool operator() (const Process &left, const Process& right) const {
            if (left.priority == right.priority) {
                if (left.arrival_time == right.arrival_time) {
                    return left.index < right.index;
                }
                return left.arrival_time < right.arrival_time;
            }
            return left.priority > right.priority;
        }
    };
};

struct ProcessStatistics {
    string name;
    int_64 responseTime;
    int_64 turnAroundTime;
    int_64 delay;
};

vector<Process> processes;
vector<ProcessStatistics> history;

void scheduler() {
    int n; 
    cin >> n;
    cout << n << '\n';
    
    processes.resize(n);
    for (int i = 0; i < n; i++) {
        auto &[name, at, pt, pr, idx] = processes[i];
        cin >> name >> at >> pt >> pr;
        idx = i;
    }

    // prepare procceses memory 
    sort(processes.begin(), processes.end(), 
        [&](const Process &a, const Process &b) {
            return a.arrival_time < b.arrival_time;
        }
    );

    set<Process, Process::Compare> readyState;

    int_64 time = 0;
    int currentProcess = 0;
    int numOFIterations = 0;

    auto addAvalilabeleProcesses = [&]() {
        while (currentProcess < n && processes[currentProcess].arrival_time <= time) {
            readyState.emplace(processes[currentProcess]);
            currentProcess++;
        }
    };

    auto getProcessFromReadyState = [&]() {
        Process cur = *readyState.begin();
        readyState.erase(readyState.begin());
        return cur;
    };

    auto addToHistory = [&](const Process &cur) {
        ProcessStatistics p;
        p.name = cur.name;
        p.responseTime = time - cur.arrival_time;
        p.turnAroundTime = time + cur.processing_time - cur.arrival_time;
        p.delay = p.turnAroundTime - cur.processing_time;
        history.push_back(p);
    };

    auto executeProcess = [&](const Process &cur) {
        addToHistory(cur);
        time += cur.processing_time;
    };

    auto shift = [&]() {
        time = processes[currentProcess].arrival_time;
        addAvalilabeleProcesses();
    };

    while (currentProcess < n || !readyState.empty()) {
        addAvalilabeleProcesses();
        if (readyState.empty()) {
            shift();
        }

        Process curProcess = getProcessFromReadyState();
        executeProcess(curProcess);
        numOFIterations++;
    }

    for (auto p : history) {
        cout << p.name << ' ';
    } 
    cout << '\n';
    for (auto p : history) {
        cout << p.name << ":(response = " << p.responseTime << ", ";
        cout << "turnaround = " << p.turnAroundTime << ", ";
        cout << "delay = " << p.delay << ")\n";
    } 

    cout << "num Of Iterations = " << numOFIterations << '\n';
    cout << "FinalTime = " << time << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    scheduler();

    return 0;
}