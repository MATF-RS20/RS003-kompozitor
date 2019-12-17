#ifndef KOMPOZITOR_RECORD_MANAGER_HPP
#define KOMPOZITOR_RECORD_MANAGER_HPP


class RecordManager {
public:
    [[nodiscard]]
    static RecordManager& get_instance();

    RecordManager(const RecordManager& other) = delete;
    RecordManager& operator=(const RecordManager& other) = delete;
    RecordManager(RecordManager&& other) = delete;
    RecordManager& operator=(RecordManager&& other) = delete;

    void start_recording();
    void stop_recording();

private:
    RecordManager() {

    }
};


#endif //KOMPOZITOR_RECORD_MANAGER_HPP
