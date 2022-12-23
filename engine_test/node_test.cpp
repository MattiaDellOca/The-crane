#include "pch.h"
#include "src/node.h"

/*
Test addChild and getChildren
*/
TEST(NODE_TEST, CHILDREN_COUNT) {
	glm::mat4 f( 1.f );
	Node parent{"parent",f };
	parent.addChild(new Node{ "child",f });
	EXPECT_EQ(parent.getChildren().size(), 1);
	parent.addChild(new Node{ "child2",f });
	EXPECT_EQ(parent.getChildren().size(), 2);
}

/*
Test removeChild
*/
TEST(NODE_TEST, CHILD_REMOVE) {
	glm::mat4 f(1.f);
	Node parent{ "parent",f };
	Node* child = new Node{ "child",f };
	parent.addChild(child);
	EXPECT_EQ(parent.getChildren().size(), 1);
	parent.removeChild(child);
	EXPECT_EQ(parent.getChildren().size(), 0);
}

/*
Test getChild
*/
TEST(NODE_TEST, CHILD_RETURN) {
	glm::mat4 f(1.f);
	Node parent{ "parent",f };
	Node* child = new Node{ "child",f };
	parent.addChild(child);
	EXPECT_EQ(parent.getChild(0), child);
}

/*
Test setParent getParent
*/
TEST(NODE_TEST, PARENT_SET) {
	glm::mat4 f(1.f);
	Node* parent = new Node{ "parent",f };
	Node* child = new Node{ "child",f };
	child->setParent(parent);
	EXPECT_EQ(parent->getChildren().size(), 1);
	EXPECT_EQ(parent->getChild(0), child);
	EXPECT_EQ(child->getParent(), parent);
}