#include <catch2/catch_test_macros.hpp>

#include "EventProcessor.hpp"

TEST_CASE("EventProcessor sums tracks and energy deterministically") {
    csc2026::EventProcessor processor;
    auto events = csc2026::EventProcessor::generateSampleEvents(10);

    processor.processEvents(events);

    REQUIRE(processor.totalTracks() == 10 * 100);
    REQUIRE(processor.totalEnergy() > 0.0);
}
