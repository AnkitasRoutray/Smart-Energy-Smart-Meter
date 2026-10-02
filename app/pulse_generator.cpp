#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
    double interval = 1.0;

    if (argc >= 2)
        interval = atof(argv[1]);

    if (interval <= 0)
    {
        cerr << "Invalid interval.\n";
        return 1;
    }

    const string device = "/dev/smartmeter";

    cout << "====================================\n";
    cout << "     SMART METER PULSE GENERATOR\n";
    cout << "====================================\n";
    cout << "Pulse interval: " << interval << " seconds\n";
    cout << "Press Ctrl+C to stop.\n\n";

    while (true)
    {
        ofstream meter(device);

        if (!meter)
        {
            cerr << "Error: Cannot open " << device << endl;
            return 1;
        }

        meter << "1";
        meter.close();

        cout << "Pulse generated and sent to driver\n";

        this_thread::sleep_for(
            chrono::duration<double>(interval)
        );
    }

    return 0;
}
