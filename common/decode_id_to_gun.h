#include <cstdint>
#include <map>
#include <string>


class DecodeIdToGun {

private:
    std::map<uint8_t, std::string> id_to_gun;


public:
    DecodeIdToGun();
    std::string get_gun(const uint8_t& id);
    void decode_id_to_gun(int id);
    ~DecodeIdToGun();
};
