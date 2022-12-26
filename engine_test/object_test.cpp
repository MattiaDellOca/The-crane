#include "pch.h"
#include "src/object.h"
#include "src/node.h"



/*
Test incremental ID
WARNING: this test is executed before the others because the static id is incremented in every test (if a node is instantiated).
*/
TEST(OBJECT_TEST, INCREMENTAL_ID) {
	glm::mat4 f(1.f);
	Node node1{ "node1",f };
	EXPECT_EQ(node1.getId(), 1);
	Node node2{ "node2",f };
	EXPECT_EQ(node2.getId(), 2);
}

