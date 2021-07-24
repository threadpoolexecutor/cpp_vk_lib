#include "cpp_vk_lib/keyboard/layout.hpp"

#include <gtest/gtest.h>

namespace keyboard = vk::keyboard;

TEST(keyboard, location_button)
{
    keyboard::layout l;
    l.add_row({keyboard::button::location()});
    l.serialize();

    #ifndef  _WIN32
    ASSERT_EQ(l.get(), R"({"buttons":[[{"action":{"type":"location","payload":"{\"button\":\"1\"}"}}]]})");
    #else
    ASSERT_EQ(l.get(), "{\"buttons\":[[{\"action\":{\"type\":\"location\",\"payload\":\"{\\\"button\\\":\\\"1\\\"}\"}}]]}");
    #endif
}

TEST(keyboard, open_app_layout)
{
    keyboard::layout l(keyboard::flag::one_time);
    l.add_row({keyboard::button::open_app(100, 200, "hash", "label")});
    l.serialize();

    ASSERT_EQ(
        l.get(),
        R"({"one_time":true,"buttons":[[{"action":{"type":"open_app","app_id":100,"owner_id":200,"hash":"hash","label":"label"}}]]})");
}

TEST(keyboard, text_layout)
{
    keyboard::layout l(keyboard::flag::one_time);
    l.add_row({keyboard::button::text(keyboard::color::blue, "1"), keyboard::button::text(keyboard::color::blue, "2")});
    l.serialize();

    #ifndef  _WIN32
    ASSERT_EQ(
        l.get(),
        R"({"one_time":true,"buttons":[[{"action":{"type":"text","payload":"{\"button\":\"1\"}","label":"1"},"color":"primary"},{"action":{"type":"text","payload":"{\"button\":\"1\"}","label":"2"},"color":"primary"}]]})");
    #else
        ASSERT_EQ(
        l.get(),
        "{\"one_time\":true,\"buttons\":[[{\"action\":{\"type\":\"text\",\"payload\":\"{\\\"button\\\":\\\"1\\\"}\",\"label\":\"1\"},\"color\":\"primary\"},{\"action\":{\"type\":\"text\",\"payload\":\"{\\\"button\\\":\\\"1\\\"}\",\"label\":\"2\"},\"color\":\"primary\"}]]}");
    #endif
}

TEST(keyboard, vk_pay_button)
{
    keyboard::layout l(keyboard::flag::one_time);
    l.add_row({keyboard::button::vk_pay("hash")});
    l.serialize();

    ASSERT_EQ(l.get(), R"({"one_time":true,"buttons":[[{"action":{"type":"vkpay","hash":"hash"}}]]})");
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
