#include <iostream>
#include <thread>

#include <libudev.h>

namespace my_system_utils
{

    class UsbDeviceMonitor
    {
    private:
        /// Filter for USB devices
        constexpr static auto SUBSYSTEM = "usb";
        /// Context for monitor
        udev* context = nullptr;
        /// Device event source
        udev_monitor* monitor = nullptr;
        /// Socket file descriptor associated with the monitor
        int socket_fd;
        /// Flag for status whether the service if terminated
        bool m_terminate = true;
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
         * @brief Process single device
         * */
        void processDevice(udev_device* device);
        /**
         * @brief Print information for single device
         * */
        void printDeviceInfo(udev_device* device);
    public:
        UsbDeviceMonitor();
        ~UsbDeviceMonitor();

        /**
         * @brief Run the device monitoring process
         * */
        void run();

        /**
         * @brief Terminate the device monitoring process
         * */
        void stop();

    };

}; // namespace my_system_utils


