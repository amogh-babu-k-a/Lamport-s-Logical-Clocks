#include "lamport_clock_simulator.h"
#include <iostream>
#include <vector>

std::vector<std::vector<Event>> generateRandomInput(int numProcesses, int numEvents, int seed)
{
    std::vector<std::vector<Event>> processes(numProcesses);
    for (int i = 0; i < numEvents; i++)
    {
        int process = rand() % numProcesses;
        int type = rand() % 10;
        if (type < 5)
        {
            processes[process].push_back({"send", process, "message", {rand() % numProcesses}, 0});
        }
        else if (type < 8)
        {
            processes[process].push_back({"recv", process, "message", {}, 0});
        }
        else
        {
            processes[process].push_back({"print", process, "message", {}, 0});
        }
    }
    for (int i = 0; i < numProcesses; i++)
    {
        processes[i].push_back({"end process"});
    }
    return processes;
}

int main()
{
    int numProcesses = 3;

    std::vector<std::vector<Event>> processes(numProcesses); // This is where you store the input

    /*
    begin process p1
print abc
recv p2 m2
send (p2, p3) m1
end process p1

begin process p2
recv p1 m1
print m1
send (p1, p3) m2
end process p2

begin process p3
recv p1 m1
recv p2 m2
print m2
end process p3
    */
    processes[0].push_back({"begin", 0, "", {}, 0}); // "begin process p1"
    processes[0].push_back({"print", 0, "abc", {}, 0}); // "print abc"
    processes[0].push_back({"recv", 0, "m2", {}, 1}); //"recv p2 m3"
    processes[0].push_back({"send", 0, "m1", {}, 0}); // "send (p2,p3) m1"
    processes[0].push_back({"send", 0, "m1", {}, 0});
    processes[0].push_back({"end", 0, "", {}, 0}); // "end process"

    processes[1].push_back({"begin", 1, "", {}, 0}); // "begin process p2"
    processes[1].push_back({"recv", 1, "m1", {}, 1}); //"recv p1 m1"
    processes[1].push_back({"print", 1, "m1", {}, 0}); // "print x1"
    processes[1].push_back({"send", 1, "m2", {}, 0}); // "send (p1,p3) m2"
    processes[1].push_back({"send", 1, "m2", {}, 0});
    processes[1].push_back({"end", 1, "", {}, 0}); // "end process p2"

    processes[2].push_back({"begin", 2, "", {}, 0}); // "begin process p3"
    processes[2].push_back({"recv", 1, "m1", {}, 0}); //"recv p2 m3"
    processes[2].push_back({"recv", 2, "m2", {}, 0}); //"recv p2 m3"
    processes[2].push_back({"print", 2, "m2", {}, 0}); // "print x3"
    processes[2].push_back({"end", 2, "", {}, 0
    }); // "end process p2"

    LamportClockSimulator simulator(numProcesses);
    simulator.simulate(processes);

    return 0;
}
