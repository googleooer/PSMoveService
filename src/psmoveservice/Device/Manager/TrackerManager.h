#ifndef TRACKER_MANAGER_H
#define TRACKER_MANAGER_H

//-- includes -----
#include <memory>
#include "DeviceTypeManager.h"
#include "DeviceEnumerator.h"
#include "PSMoveProtocol.pb.h"

//-- typedefs -----

class ServerTrackerView;
typedef std::shared_ptr<ServerTrackerView> ServerTrackerViewPtr;

//-- definitions -----

class TrackerManager : public DeviceTypeManager
{
public:
    TrackerManager();

    static const int k_max_devices = 1;
    int getMaxDevices() const override
    {
        return TrackerManager::k_max_devices;
    }

    ServerTrackerViewPtr getTrackerViewPtr(int device_id);

protected:
    bool can_update_connected_devices() override;
    DeviceEnumerator *allocate_device_enumerator() override;
    void free_device_enumerator(DeviceEnumerator *) override;
    ServerDeviceView *allocate_device_view(int device_id) override;

    const PSMoveProtocol::Response_ResponseType getListUpdatedResponseType() override
    {
        return TrackerManager::k_list_udpated_response_type;
    }

private:
    static const PSMoveProtocol::Response_ResponseType k_list_udpated_response_type = PSMoveProtocol::Response_ResponseType_TRACKER_LIST_UPDATED;
};

#endif // TRACKER_MANAGER_H