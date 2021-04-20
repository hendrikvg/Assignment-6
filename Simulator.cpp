#include "Simulator.h"

Simulator::~Simulator()
{
	std::cout << "Destroying Simulator object.\n";
}

std::thread Simulator::integrateThread(Matrix& x, CommonInput& u, double& t, double dt, int FPS, std::mutex& mtx, bool& quit)
{
	
	return std::thread([&, dt, FPS] {
		while (!quit) {
			double end = t + 1.0 / FPS;
			auto t1 = std::chrono::high_resolution_clock::now();
			mtx.lock();
			integrate(x, u, t, dt, end);
			mtx.unlock();
			auto t2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds remaining(10 - std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());
			if (remaining.count() <= 0) continue;
			std::this_thread::sleep_for(remaining);
		}
	});
}

void Simulator::saveState(double t, Matrix x, Matrix y)
{
	std::vector<double> state;
	state.push_back(t);
	for (unsigned row = 0; row < x.getRows(); row++)
	{
		state.push_back(x.getVector()[row]);
	}
	for (unsigned row = 0; row < y.getRows(); row++)
	{
		state.push_back(y.getVector()[row]);
	}
	this->states.push_back(state);
}

void Simulator::exportStates(std::string nameCSV = "StatesExport.csv")
{
	OutputCSV output;
	output.writeCSV(this->states, nameCSV);
}
