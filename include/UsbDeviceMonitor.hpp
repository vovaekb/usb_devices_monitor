#include <iostream>
#include <thread>

#include <libudev.h>

namespace my_system_utils
{

    class UsbDeviceMonitor
    {
    private:
        /// 
        constexpr static auto SUBSYSTEM = "usb";
        /// 
        udev* context;
        /// Device event source
        udev_monitor* monitor;
        /// Socket file descriptor associated with the monitor
        int socket_fd;
        /// Flag for status of readiness
        bool is_started = false;
        /// Thread object
        std::thread m_thread;

        /**
         * @brief Initialize all required resources for devices monitoring
         * */
        void init();

        /**
         * @brief Start procedure for device monitoring
         * */
        void startMonitor();
        /**
         * @brief Downsample point cloud
         * */
        void processDevice(udev_device* device);
        /**
         * @brief Downsample point cloud
         * */
        void printDeviceInfo(udev_device* device);
    public:
        UsbDeviceMonitor(/* args */);
        ~UsbDeviceMonitor();

        void run();

        void stop();

        // TODO: Implement method stop() to terminate the monitoring process
    };

}; // namespace my_system_utils


