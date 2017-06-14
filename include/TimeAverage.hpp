#pragma once

#include <core/utils/BasicSensor.hpp>
#include <core/common_msgs/Float32.hpp>
#include <core/basic_sensors/TimeAverageConfiguration.hpp>

namespace core {
namespace basic_sensors {
class TimeAverage:
    public core::utils::BasicSensor<float>,
    public core::mw::CoreConfigurable<core::basic_sensors::TimeAverageConfiguration>
{
public:
    TimeAverage(
        const char* name
    );

    virtual
    ~TimeAverage() {}

    bool
    init();

    bool
    start();

    bool
    stop();

    bool
    waitUntilReady();

    bool
    update();

    bool
    configure();

    void
    get(
        DataType& data
    );


    template <typename T>
    void
    addSample(
        T x
    );


protected:
    float _data;

private:
    float    _accumulator;
    uint32_t _counter;

public:
    struct Converter {
        using FROM = float;
        using TO   = core::common_msgs::Float32;

        static inline void
        _(
            const FROM& from,
            TO*         to
        )
        {
            to->value = from;
        }
    };
};

template <typename T>
void
TimeAverage::addSample(
    T x
)
{
    _accumulator += (float)x;
    _counter++;
}
}
}
