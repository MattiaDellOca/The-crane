#include "node_test.h"


void NodeTest::testAll(){
    testChildren();
}

void NodeTest::testChildren(){
    glm::mat4 f(1.f);
    Node parent{"parent",f};
    assert(parent.getChildren().size()==2);
    std::cout << "test done" << std::endl;
}
