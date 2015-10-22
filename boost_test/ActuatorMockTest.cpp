/*
* Copyright 2015 BrewPi/Elco Jacobs.
*
* This file is part of BrewPi.
*
* BrewPi is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* BrewPi is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <boost/test/unit_test.hpp>

#include "runner.h"
#include <string>

#include "ActuatorInterfaces.h"
#include "ActuatorMocks.h"
#include "json_writer.h"
#include "json_reader.h"

BOOST_AUTO_TEST_SUITE(ActuatorMockTest)

BOOST_AUTO_TEST_CASE(serialize_ActuatorMock) {
    ActuatorBool act;
    std::string json;

    json = JSON::producer<ActuatorBool>::convert(act);
    BOOST_CHECK_EQUAL("{\"ActuatorBool\":{\"state\":false}}", json);

    act.setActive(true);
    json = JSON::producer<ActuatorBool>::convert(act);
    BOOST_CHECK_EQUAL("{\"ActuatorBool\":{\"state\":true}}", json);
}

BOOST_AUTO_TEST_CASE(serialize_ActuatorValue) {
    ActuatorValue act(10.0, 0.0, 30.0625);
    std::string json;

    json = JSON::producer<ActuatorValue>::convert(act);
    BOOST_CHECK_EQUAL("{\"ActuatorValue\":{\"value\":10.0000,\"minimum\":0.0000,\"maximum\":30.0625}}", json);
}


BOOST_AUTO_TEST_SUITE_END()
