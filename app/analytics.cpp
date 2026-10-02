#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>

using namespace std;
using namespace chrono;

int main()
{
    const string device = "/dev/smartmeter";
    const string log_file = "../data/energy_log.csv";

    const double pulses_per_kwh = 1000.0;
    const double POWER_LIMIT_KW = 5.0;

    long long previous_pulses = -1;
    auto previous_time = steady_clock::now();

    // Open log file
    ofstream log(log_file, ios::app);

    if (!log)
    {
        cerr << "Error: Cannot open log file." << endl;
        return 1;
    }

    // Add CSV header if file is empty
    log.seekp(0, ios::end);

    if (log.tellp() == 0)
    {
        log << "Time,Pulses,Energy_kWh,Power_kW,Status\n";
    }

    cout << "====================================\n";
    cout << "       SMART METER ANALYTICS\n";
    cout << "====================================\n";

    while (true)
    {
        ifstream meter(device);

        if (!meter)
        {
            cerr << "Error: Cannot open " << device << endl;
            return 1;
        }

        long long pulses;
        meter >> pulses;
        meter.close();

        double energy_kwh = pulses / pulses_per_kwh;

        double power_kw = 0.0;

        auto current_time = steady_clock::now();

        if (previous_pulses >= 0 && pulses > previous_pulses)
        {
            long long pulse_difference =
                pulses - previous_pulses;

            double elapsed_seconds =
                duration<double>(
                    current_time - previous_time
                ).count();

            if (elapsed_seconds > 0)
            {
                double energy_difference =
                    pulse_difference / pulses_per_kwh;

                power_kw =
                    energy_difference * 3600.0
                    / elapsed_seconds;
            }
        }

        string status;

        if (power_kw > POWER_LIMIT_KW)
        {
            status = "HIGH_POWER";
        }
        else
        {
            status = "NORMAL";
        }

        // Current time
        time_t now = time(nullptr);
        tm *local_time = localtime(&now);

        char time_buffer[30];

        strftime(
            time_buffer,
            sizeof(time_buffer),
            "%Y-%m-%d %H:%M:%S",
            local_time
        );

        // Save reading
        log << time_buffer << ","
            << pulses << ","
            << fixed << setprecision(3)
            << energy_kwh << ","
            << power_kw << ","
            << status << "\n";

        log.flush();

        // Display dashboard
        cout << "\033[2J\033[H";

        cout << "====================================\n";
        cout << "       SMART METER ANALYTICS\n";
        cout << "====================================\n";

        cout << "Pulse Count : "
             << pulses << endl;

        cout << fixed << setprecision(3);

        cout << "Energy      : "
             << energy_kwh << " kWh" << endl;

        cout << "Power       : "
             << power_kw << " kW" << endl;

        cout << "Limit       : "
             << POWER_LIMIT_KW << " kW" << endl;

        if (power_kw > POWER_LIMIT_KW)
        {
            cout << "Status      : HIGH POWER ALERT!" << endl;
        }
        else
        {
            cout << "Status      : NORMAL" << endl;
        }

        cout << "====================================\n";
        cout << "Data saved to: ../data/energy_log.csv\n";
        cout << "Monitoring...\n";

        previous_pulses = pulses;
        previous_time = current_time;

        this_thread::sleep_for(seconds(1));
    }

    log.close();

    return 0;
}
