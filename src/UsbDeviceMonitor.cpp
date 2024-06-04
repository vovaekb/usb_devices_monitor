

#include "UsbDeviceMonitor.hpp"


namespace my_system_utils
{

    UsbDeviceMonitor::UsbDeviceMonitor(/* args */)
    {
    }

    UsbDeviceMonitor::~UsbDeviceMonitor() {
        std::cout << "Terminate from destructor\n";
        // TODO: terminate thread
        std::cout << "is_started: " << is_started << "\n";

        if(m_thread.joinable()) {
            std::cout << "terminate thread\n";
            if (is_started)
                stop();
            m_thread.join();
        }
        
    }

    void UsbDeviceMonitor::init() {
        context = udev_new();
        monitor = udev_monitor_new_from_netlink(context, "udev");
        is_started = true;

        // set filter for usb devices
        auto res1 = udev_monitor_filter_add_match_subsystem_devtype(monitor, SUBSYSTEM, nullptr);
        auto res2 = udev_monitor_enable_receiving(monitor);
        std::cout << res1 << " " << res2 << "\n";

    }

    void UsbDeviceMonitor::run() {
        std::cout << "Starting device monitor ... \n";
        init();
        startMonitor();
    }

    void UsbDeviceMonitor::startMonitor() {
        // get socket file descriptor associated with the monitor
        int fd = udev_monitor_get_fd(monitor);

        m_thread = std::thread([&] {
            while (1) {
                fd_set fds;
                FD_ZERO(&fds);
                FD_SET(fd, &fds);

                int ret = select(fd+1, &fds, nullptr, nullptr, nullptr);
                if (ret <= 0)
                    break;

                if (FD_ISSET(fd, &fds)) {
                    udev_device* dev = udev_monitor_receive_device(monitor);
                    // cout << "New usb device attached" << endl;
                    processDevice(dev);
                }
            }
        });
        

        
    }

    void UsbDeviceMonitor::processDevice(udev_device* device) {
        if (device) {
            // cout << "is dev" << endl;
            // check full file path to the device
            if (udev_device_get_devnode(device))
                printDeviceInfo(device);

            udev_device_unref(device);
        }
    }
    
    void UsbDeviceMonitor::printDeviceInfo(udev_device* device) {
        auto action = udev_device_get_action(device);

        std::cout << "action: " << action << std::endl;
        if (static_cast<std::string>(action) == "bind") {
            std::cout << "attached new device" << std::endl;

            auto vendor = udev_device_get_sysattr_value(device, "idVendor");
            if (vendor)
                std::cout << "vendor: " << vendor << std::endl;
        }
    }

    void UsbDeviceMonitor::stop() {
        std::cout << "Shutting down device monitor ... \n";
        // shutdown all the udev resources
        if (monitor) {
            udev_monitor_unref(monitor);
        }
        udev_unref(context);
        is_started = false;
    }


}; // namespace my_system_utils