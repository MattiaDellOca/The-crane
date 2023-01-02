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

/*
Search Node
*/
TEST(NODE_TEST, SEARCH) {
	glm::mat4 f(1.f);
	Node* parent = new Node{ "parent",f };
	Node* child1 = new Node{ "child1",f };
	Node* child2 = new Node{ "child2",f };
	Node* nephew1 = new Node{ "nephew1",f };
	Node* nephew2 = new Node{ "nephew2",f };
	Node* nephew3 = new Node{ "nephew3",f };

	parent->addChild(child1);
	parent->addChild(child2);
	child1->addChild(nephew1);
	child1->addChild(nephew2);
	child2->addChild(nephew3);

	EXPECT_EQ(parent->searchNode("child1"), child1);
	EXPECT_EQ(parent->searchNode("child2"), child2);
	EXPECT_EQ(parent->searchNode("nephew1"), nephew1);
	EXPECT_EQ(parent->searchNode("nephew2"), nephew2);
	EXPECT_EQ(parent->searchNode("nephew3"), nephew3);

	EXPECT_EQ(child1->searchNode("nephew1"), nephew1);
	EXPECT_EQ(child1->searchNode("nephew2"), nephew2);

	EXPECT_EQ(child2->searchNode("nephew3"), nephew3);
}
