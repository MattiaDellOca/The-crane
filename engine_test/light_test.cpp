#include "pch.h"
#include "src/omnidirectionalLight.h"
#include "src/directionalLight.h"
#include "src/spotLight.h"

/*
	WARNING: the engine is not reloaded between the tests
*/


/*
	Test the correct incrementation of the id
*/
TEST(LIGHT_TEST, INCREMENTAL_ID_LIGHT) {
	glm::mat4 f(1.f);
	glm::vec4 value(1.f);
	OmnidirectionalLight omniLight0{"Light0",f, value ,value , value}; //Light id = 0
	ASSERT_EQ(omniLight0.getLightId(), 0);
	OmnidirectionalLight omniLight1{ "Light1",f, value ,value , value }; //Light id = 1
	ASSERT_EQ(omniLight1.getLightId(), 1);
}

/*
	Check if the type is correctly assigned 
*/
TEST(LIGHT_TEST, OMNIDIRECTIONAL_TYPE) {
	glm::mat4 f(1.f);
	glm::vec4 value(1.f);
	OmnidirectionalLight omniLight2{ "Light2",f, value ,value , value }; //Light id = 2
	ASSERT_EQ(omniLight2.getLightType(), LightType::OMNIDIRECTIONAL);
}

/*
	Check if the type is correctly assigned
*/
TEST(LIGHT_TEST, DIRECTIONAL_TYPE) {
	glm::mat4 f(1.f);
	glm::vec4 value(1.f);
	DirectionalLight directionalLight3{ "Light3",f, value ,value , value }; //Light id = 3
	ASSERT_EQ(directionalLight3.getLightType(), LightType::DIRECTIONAL);
}


/*
	Check if the type is correctly assigned
*/
TEST(LIGHT_TEST, SPOT_TYPE) {
	glm::mat4 f(1.f);
	glm::vec4 value(1.f);
	SpotLight spotLight4{"Light4",f, value ,value , value, 45.f, value }; //Light id = 4
	ASSERT_EQ(spotLight4.getLightType(), LightType::SPOT);
}

/*
	Check if the excpetion is correctly throwed with value greather than 90.f
*/
TEST(LIGHT_TEST, SPOT_CUTOFFOVER90) {
	glm::mat4 f(1.f);
	glm::vec4 value(1.f);
	try
	{
		SpotLight spotLight4{ "LightError0",f, value ,value , value, 91.f, value };
		FAIL();
	}
	catch (const std::invalid_argument& err)
	{
		// check exception
		ASSERT_STREQ("Cutoff angle error: LightError0", err.what());
	}
}

/*
	Check if the excpetion is correctly throwed with value lower than 0.f
*/
TEST(LIGHT_TEST, SPOT_CUTOFFLOWERTHAN90) {
	glm::mat4 f(1.f);
	glm::vec4 value(1.f);
	try
	{
		SpotLight spotLight4{ "LightError1",f, value ,value , value, -1.f, value };
		FAIL();
	}
	catch (const std::invalid_argument& err)
	{
		// check exception
		ASSERT_STREQ("Cutoff angle error: LightError1", err.what());
	}
}


/*
	Check if the excpetion is correctly throwed when the user try to create more lights than supported

	NOTE: this test assumes thast the maximum lights are 8!!!
*/
TEST(LIGHT_TEST, LIGHT_MAXSUPPORTED) {

	//Some lights to reach the maximum
	glm::mat4 f(1.f);
	glm::vec4 value(1.f);
	OmnidirectionalLight omniLight5{ "Light5",f, value ,value , value }; //Light id = 5
	OmnidirectionalLight omniLight6{ "Light6",f, value ,value , value }; //Light id = 6
	OmnidirectionalLight omniLight7{ "Light7",f, value ,value , value }; //Light id = 7

	//The next line light shout throw the expection
	try
	{
		OmnidirectionalLight omniLight8{ "Light8",f, value ,value , value }; //Light id = 8
		FAIL();
	}
	catch (const std::runtime_error& err)
	{
		// check exception
		ASSERT_STREQ("Maximum number of lights possible reached: Light8", err.what());
	}
}

