#include "pch.h"
#include "src/node.h"

TEST(NODE_TEST, CHILDREN_COUNT) {
	glm::mat4 f( 1.f );
	Node parent{"parent",f };
	Node child{"child",f };
	parent.addChild(&child);
	EXPECT_EQ(parent.getChildren().size(), 1);
	Node child2{ "child2",f };
	parent.addChild(&child2);
	EXPECT_EQ(parent.getChildren().size(), 2);
}