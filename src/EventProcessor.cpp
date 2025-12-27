// CSC Latin America 2026 - Event Processor implementation
#include "EventProcessor.hpp"
#include <random>

#ifdef _OPENMP
#include <omp.h>
#endif

namespace csc2026 {

void EventProcessor::processEvent(const Event& event) {
    for (const auto& particle : event.particles) {
        m_totalTracks++;
        m_totalEnergy += particle.energy();
    }
}

void EventProcessor::processEvents(const std::vector<Event>& events) {
    int tracks = 0;
    double energy = 0.0;
    
    #pragma omp parallel for reduction(+:tracks,energy)
    for (size_t i = 0; i < events.size(); ++i) {
        for (const auto& particle : events[i].particles) {
            tracks++;
            energy += particle.energy();
        }
    }
    
    m_totalTracks += tracks;
    m_totalEnergy += energy;
}

void EventProcessor::reset() {
    m_totalTracks = 0;
    m_totalEnergy = 0.0;
}

std::vector<Event> generateSampleEvents(int nEvents, int particlesPerEvent) {
    std::vector<Event> events;
    events.reserve(nEvents);
    
    std::mt19937 gen(42); // Fixed seed for reproducibility
    std::uniform_real_distribution<> px_dist(-50.0, 50.0);
    std::uniform_real_distribution<> py_dist(-50.0, 50.0);
    std::uniform_real_distribution<> pz_dist(-100.0, 100.0);
    std::uniform_real_distribution<> mass_dist(0.0, 1.0);
    
    for (int i = 0; i < nEvents; ++i) {
        Event event;
        event.eventNumber = i;
        event.particles.reserve(particlesPerEvent);
        
        for (int j = 0; j < particlesPerEvent; ++j) {
            event.particles.emplace_back(
                px_dist(gen), py_dist(gen), pz_dist(gen), mass_dist(gen)
            );
        }
        events.push_back(std::move(event));
    }
    
    return events;
}

} // namespace csc2026
