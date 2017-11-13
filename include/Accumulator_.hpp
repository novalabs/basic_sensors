#pragma once

#include <core/utils/BasicSensor.hpp>
#include <core/common_msgs/Float32.hpp>
#include <core/basic_sensors/AccumulatorConfiguration.hpp>

namespace core {
namespace basic_sensors {
    template<typename T, typename T2 = float, typename T3 = core::common_msgs::Float32>
class Accumulator_:
    public core::utils::BasicSensor<T2>,
    public core::mw::CoreConfigurable<core::basic_sensors::AccumulatorConfiguration>
{
public:
    Accumulator_(
        const char* name
    ) : CoreConfigurable<core::basic_sensors::AccumulatorConfiguration>::CoreConfigurable(name), _data(0.0f), _accumulator(0.0f), _counter(0) {};

    virtual
    ~Accumulator_() {}

    bool
    init() {return true;}

    bool
    start(){
        reset();
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
        _data = _accumulator;
        _counter     = 0;

        return _counter != 0;
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

    void
	reset() {
        _data = T2();
        _accumulator = T();
        _counter     = 0;
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
Accumulator_<T, T2, T3>::addSample(
    TT x
)
{
    _accumulator += x;
    _counter++;
}
}
}
