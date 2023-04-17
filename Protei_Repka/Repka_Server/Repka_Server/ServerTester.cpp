#include "ServerSocket.h"
#include "gtest/gtest.h"

namespace {

TEST(CommandTest, PUT_first) {

    std::string expected_str = "OK\n";

    ServerSocket server (3777);

    std::string actual_str = server.process_command("PUT a b\n");
    EXPECT_EQ(expected_str, actual_str);

}

TEST(CommandTest, PUT_second) {

    std::string expected_str = "OK c\n";

    ServerSocket server (3777);
    server.process_command("PUT a c");
    std::string actual_str = server.process_command("PUT a b\n");
    EXPECT_EQ(expected_str, actual_str);

}

TEST(CommandTest, DEL_ok) {

    std::string expected_str = "OK c\n";

    ServerSocket server (3777);
    server.process_command("PUT a c");
    std::string actual_str = server.process_command("DEL a\n");
    EXPECT_EQ(expected_str, actual_str);

}

TEST(CommandTest, DEL_ne) {

    std::string expected_str = "OK c\n";

    ServerSocket server (3777);
    server.process_command("PUT a c");
    std::string actual_str = server.process_command("PUT a b\n");
    EXPECT_EQ(expected_str, actual_str);

}

TEST(CommandTest, COUNT) {

    std::string expected_str = "1\n";

    ServerSocket server (3777);
    server.process_command("PUT a c");
    std::string actual_str = server.process_command("COUNT\n");
    EXPECT_EQ(expected_str, actual_str);

}

}
