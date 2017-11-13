#include <core/basic_sensors/TimeAverage.hpp>

#include <core/os/Thread.hpp>

namespace core {
namespace basic_sensors {
TimeAverage::TimeAverage(
    const char* name
) : CoreConfigurable<core::basic_sensors::TimeAverageConfiguration>::CoreConfigurable(name), _data(0.0f), _accumulator(0.0f), _counter(0) {}

bool
TimeAverage::configure()
{
    return isConfigured();
}

bool
TimeAverage::init()
{
    return true;
}

bool
TimeAverage::start()
{
	reset();
    return true;
}

bool
TimeAverage::stop()
{
    return true;
}

bool
TimeAverage::waitUntilReady()
{
    core::os::Thread::sleep(core::os::Time::ms(configuration().period));

    return true;
}

bool
TimeAverage::update()
{
    if (_counter == 0) {
        return false;
    }

    _data = _accumulator / (float)_counter;
    _accumulator = 0.0f;
    _counter     = 0;

    return true;
}

void
TimeAverage::get(
    DataType& data
)
{
    data = _data;
}

void
TimeAverage::reset() {
    _data = 0.0f;
    _accumulator = 0.0f;
    _counter     = 0;
}

}
}
