/* COPYRIGHT (c) 2016-2018 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */
 
#pragma once

#include <core/utils/BasicSensor.hpp>
#include <core/common_msgs/Float32.hpp>

namespace core {
namespace basic_sensors {
    template<typename T, typename T2 = float, typename T3 = core::common_msgs::Float32>
class Last_:
    public core::utils::BasicSensor<T2>
{
public:
    	Last_(
        const char* name
    ) : _data(T2()), _accumulator(T()) {};

    virtual
    ~Last_() {}

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
        return true;
    }

    bool
    update(){
        _data = _accumulator;

        return true;
    }

    bool
    configure() {
    	return true;
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
    }

    template <typename TT>
    void
    addSample(
        TT x
    );


protected:
    T2 _data;

private:
    T _accumulator;

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
Last_<T, T2, T3>::addSample(
    TT x
)
{
    _accumulator = x;
}
}
}
