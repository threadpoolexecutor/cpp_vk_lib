#include "../../lib/include/cpp_vk_lib/events/message_new.hpp"
#include "../../lib/include/cpp_vk_lib/events/wall_post_new.hpp"
#include "../../lib/include/cpp_vk_lib/events/wall_reply_new.hpp"
#include "cpp_vk_lib/events/common_event.hpp"
#include "simdjson.h"

#include <gtest/gtest.h>

#ifdef _WIN32
#define IF_WIN(a, b) a
#else
#define IF_WIN(a, b) b
#endif

//TODO: FIX WINDOWS BUILD
TEST(message_new, default_event)
{
    simdjson::dom::parser parser;
    simdjson::dom::element event_object = parser.load(IF_WIN("../../../../json_schema/message_new.json", "json_schema/message_new.json"));
    vk::event::message_new event(std::move(event_object));
    ASSERT_EQ("123", event.text());
    ASSERT_EQ(499047616, event.from_id());
    ASSERT_EQ(2000000008, event.peer_id());
    ASSERT_EQ(120470, event.conversation_message_id());
    ASSERT_EQ(false, event.has_action());
    ASSERT_EQ(false, event.has_fwd_messages());
    ASSERT_EQ(false, event.has_reply());
}

TEST(message_new, event_attachments)
{
    simdjson::dom::parser parser;
    simdjson::dom::element event_object = parser.load(IF_WIN("../../../../json_schema/message_new.json", "json_schema/message_new.json"));
    vk::event::message_new event(std::move(event_object));
    auto photo_attachment = event.attachments()[0];
    ASSERT_EQ(1, event.attachments().size());
    ASSERT_EQ("photo", photo_attachment->type());
    ASSERT_EQ("photo499047616_457273210", photo_attachment->value());
}

TEST(wall_post_new, default_event)
{
    simdjson::dom::parser parser;
    simdjson::dom::element event_object = parser.load(IF_WIN("../../../../json_schema/wall_post_new.json", "json_schema/wall_post_new.json"));
    vk::event::wall_post_new event(std::move(event_object));
    ASSERT_EQ(309, event.id());
    ASSERT_EQ(-192764727, event.from_id());
    ASSERT_EQ(-192764727, event.owner_id());
    ASSERT_FALSE(event.marked_as_ads());
    ASSERT_EQ("123", event.text());
    ASSERT_TRUE(event.can_edit());
    ASSERT_TRUE(event.can_delete());
    ASSERT_EQ(1, event.attachments().size());
    ASSERT_EQ("photo-192764727_457350091", event.attachments()[0]->value());
}

TEST(wall_reply_new, default_event)
{
    simdjson::dom::parser parser;
    simdjson::dom::element event_object = parser.load(IF_WIN("../../../../json_schema/wall_reply_new.json", "json_schema/wall_reply_new.json"));
    vk::event::wall_reply_new event(std::move(event_object));
    ASSERT_EQ(312, event.id());
    ASSERT_EQ(499047616, event.from_id());
    ASSERT_EQ(310, event.post_id());
    ASSERT_EQ(-192764727, event.owner_id());
    ASSERT_EQ("123", event.text());
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
