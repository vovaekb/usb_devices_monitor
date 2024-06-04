#include <string>
#include <iostream>

#include <gtest/gtest.h>

#include "UsbDeviceMonitor.hpp"


namespace my_system_utils {

    TEST(UsbDeviceMonitorTest, Initial) {
        UsbDeviceMonitor device_monitor;
        ASSERT_TRUE(true);
    }

    // TEST(UsbDeviceMonitorTest, Start) {
    //     UsbDeviceMonitor device_monitor;
    //     device_monitor.run();
    //     ASSERT_TRUE(true);
    // }

    TEST(UsbDeviceMonitorTest, StartStop) {
        UsbDeviceMonitor device_monitor;
        device_monitor.run();
        device_monitor.stop();
        ASSERT_TRUE(true);
    }
}