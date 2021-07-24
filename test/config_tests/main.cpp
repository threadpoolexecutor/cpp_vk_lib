#include "cpp_vk_lib/config/loader.hpp"

#include <gtest/gtest.h>

TEST(config, field_access)
{
    #ifndef  _WIN32
        vk::config::load("json_schema/sample_config.json");
    #else
        vk::config::load("../../../../json_schema/sample_config.json");
    #endif

    ASSERT_EQ(vk::config::access_token(), "access_token");
    ASSERT_EQ(vk::config::user_token(), "user_token");

    vk::config::set_user_token("new_token");

    ASSERT_EQ(vk::config::user_token(), "new_token");

    ASSERT_EQ(vk::config::username(), "login@gmail.com");
    ASSERT_EQ(vk::config::password(), "password");

    ASSERT_EQ(vk::config::num_workers(), 8);
    
    ASSERT_EQ(vk::config::error_logpath(), "/tmp/errors.log");
    ASSERT_EQ(vk::config::event_logpath(), "/tmp/events.log");
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
