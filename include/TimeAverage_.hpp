#pragma once

#include <core/utils/BasicSensor.hpp>
#include <core/common_msgs/Float32.hpp>
#include <core/basic_sensors/TimeAverageConfiguration.hpp>

namespace core {
namespace basic_sensors {
    template<typename T, typename T2 = float, typename T3 = core::common_msgs::Float32>
class TimeAverage_:
    public core::utils::BasicSensor<T2>,
    public core::mw::CoreConfigurable<core::basic_sensors::TimeAverageConfiguration>
{
public:
    TimeAverage_(
        const char* name
    ) : CoreConfigurable<core::basic_sensors::TimeAverageConfiguration>::CoreConfigurable(name), _data(0.0f), _accumulator(0.0f), _counter(0) {};

    virtual
    ~TimeAverage_() {}

    bool
    init() {return true;}

    bool
    start(){
        _data = T2();
        _accumulator = T();
        _counter     = 0;
        return true;
    }


    bool
    stop() {return true;}

    bool
    waitUntilReady(){
        core::os::Thread::sleep(core::os::Time::ms(configuration().period));

        return true;
    }

    bool
    update(){
        if (_counter == 0) {
            return false;
        }

        _data = _accumulator / _counter;
        _accumulator = T();
        _counter     = 0;

        return true;
    }

    bool
    configure() {
    	return isConfigured();
    };

    void
    get(
        T2& data
    ){
        data = _data;
    }


    template <typename TT>
    void
    addSample(
        TT x
    );


protected:
    T2 _data;

private:
    T        _accumulator;
    uint32_t _counter;

public:
    struct Converter {
        using FROM = T2;
        using TO   = T3;

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

template <typename T, typename T2, typename T3>
template <typename TT>
void
TimeAverage_<T, T2, T3>::addSample(
    TT x
)
{
    _accumulator += x;
    _counter++;
}
}
}
