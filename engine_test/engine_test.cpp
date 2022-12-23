#include "pch.h"
#include "src/engine.h"

/*
	Testing possibility to call init only once (is already called in main)
*/
TEST(ENGINE_TEST, INCREMENTAL_ID_LIGHT) {
	ASSERT_EQ(Engine::init("engine_test", 0, 0, NULL, nullptr), false);
}