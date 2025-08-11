/*
 * If not stated otherwise in this file or this component's license file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#ifndef _PLAYER_JSON_OBJECT_H
#define _PLAYER_JSON_OBJECT_H

/**
 * @file PlayerJsonObject.h
 * @brief File to handle Json format 
 */


#include <string>
#include <vector>
#include <cstdint> // for uint8_t

#include <cjson/cJSON.h>

/**
 * @class PlayerJsonObject
 * @brief Utility class to construct a JSON string
 */
class PlayerJsonObject {
public:
	PlayerJsonObject();
	PlayerJsonObject(const std::string& jsonStr);
	PlayerJsonObject(const char* jsonStr);
	~PlayerJsonObject();
	PlayerJsonObject(const PlayerJsonObject&) = delete;
	PlayerJsonObject& operator=(const PlayerJsonObject&) = delete;
	PlayerJsonObject(PlayerJsonObject &&) = default;

	enum ENCODING
	{
		ENCODING_STRING,     /**< Bytes encoded as a string as-is */
		ENCODING_BASE64,     /**< Bytes base64 encoded to a string */
		ENCODING_BASE64_URL  /**< Bytes base64url encoded to a string */
	};

	/**
	 *  @fn add
	 *
	 *  @param name name for the value
	 *  @param value string value to add
	 *  @return true if successfully added, false otherwise
	 */
	bool add(const std::string& name, const std::string& value, const ENCODING encoding = ENCODING_STRING);

	/**
	 *  @fn add
	 *
	 *  @param name name for the value
	 *  @param value string value to add
	 *  @return true if successfully added, false otherwise
	 */
	bool add(const std::string& name, const char *value, const ENCODING encoding = ENCODING_STRING);

	/**
	 *  @fn add
	 *
	 *  @param name name for the array
	 *  @param values vector of strings to add as an array
	 *  @return true if successfully added, false otherwise
	 */
	bool add(const std::string& name, const std::vector<std::string>& values);

	/**
	 *  @fn add
	 *
	 *  @param name name for the value
	 *  @param values vector of bytes to add in the specified encoding
	 *  @param encoding how to encode the byte array
	 *  @return true if successfully added, false otherwise
	 */
	bool add(const std::string& name, const std::vector<uint8_t>& values, const ENCODING encoding = ENCODING_STRING);

	/**
	 *  @fn add
	 *
	 *  @param name name for the array
	 *  @param values vector of #PlayerJsonObject to add as an array
	 *  @return true if successfully added, false otherwise
	 */
	bool add(const std::string& name, std::vector<PlayerJsonObject*>& values);

	/**
	 *  @fn get
	 *
	 *  @param name name for the array
	 *  @param[out] values String Array
	 *  @return true if successfully added, false otherwise
	 */
	bool get(const std::string& name, std::vector<std::string>& values);

	/**
	 *  @fn get
	 *
	 *  @param name name for the property
	 *  @param[out] values int value
	 *  @return true if successfully added, false otherwise
	 */
	bool get(const std::string& name, int& value);

	/**
	 *  @brief Get a double value from JSON data
	 *  @param name name for the property
	 *  @param[out] value double value
	 *  @return true if successfully retrieved, false otherwise
	 */
	bool get(const std::string& name, double& value);

	/**
	 * @fn get
	 *
	 * @param name name of the property to retrieve
	 * @param value string to populate with the retrieved value
	 * @return true if successfully retrieved value, false otherwise
	 */
	bool get(const std::string& name, std::string& value);

	/**
	 * @fn fn
	 *
	 * @param name name of the property to retrieve
	 * @param values vector to populate with the retrieved value
	 * @param encoding the encoding of the string, used to determine how to decode the content into the vector
	 * @return true if successfully retrieved and decoded value, false otherwise
	 */
	bool get(const std::string& name, std::vector<uint8_t>& values, const ENCODING encoding = ENCODING_STRING);

	/**
	 * @fn get
	 *
	 * @param name Name of the internal json data
	 * @param value[out] reference Object which return as json object inside json data.
	 * @return true if successfully retrieved and decoded value, false otherwise
	 */
	bool get(const std::string& name, PlayerJsonObject &value);

	/**
	 *  @brief Get an array of objects from JSON data
	 *  @param name name for the property
	 *  @param[out] value JSON object array
	 *  @return true if successfully retrieved, false otherwise
	 */
	bool get(const std::string& name, std::vector<PlayerJsonObject> &values);

	/**
	 *  @fn print
	 *
	 *  @return JSON string
	 */
	std::string print();


	/**
	 *  @fn print_UnFormatted
	 *
	 *  @return JSON string
	 */
	std::string print_UnFormatted();

	/**
	 *  @fn print
	 *
	 *  @param[out] data - vector to output printed JSON to
	 *  @return	 void.
	 */
	void print(std::vector<uint8_t>& data);
	/**
	 *  @fn add
	 *
	 *  @param name name for the value
	 *  @param value bool to add
	 *  @return true if successfully added, false otherwise
	 */
	bool add(const std::string& name, bool value);	
	/**
	 *  @fn add
	 *
	 *  @param name name for the value
	 *  @param value int to add
	 *  @return true if successfully added, false otherwise
	 */
	bool add(const std::string& name, int value);

	/**
	 *  @fn add
	 *
	 *  @param name name for the value
	 *  @param value double to add
	 *  @return true if successfully added, false otherwise
	 */
	bool add(const std::string& name, double value);

	/**
	 *  @fn add
	 *
	 *  @param name name for the value
	 *  @param value long to add
	 *  @return true if successfully added, false otherwise
	 */
	bool add(const std::string& name, long value);

	bool add(const std::string& name, PlayerJsonObject& value);

	/**
	 *  @fn add
	 *
	 *  @param name name for the value
	 *  @param value long to add
	 *  @return true if successfully added, false otherwise
	 */
	bool add(const std::string& name, cJSON *value);

	/**
	 * @fn isArray
	 *
	 * @return true if it is Array or false
	 */
	bool isArray(const std::string& name);

	/**
	 * @fn isString
	 *
	 * @return true if it is String or false
	 */
	bool isString(const std::string& name);

	/**
	 * @fn isNumber
	 *
	 * @return true if it is Number or false
	 */
	bool isNumber(const std::string& name);

	/**
	 * @fn isObject
	 *
	 * @return true if it is Object or false
	 */
	bool isObject(const std::string& name);

private:
	bool set(PlayerJsonObject *parent, cJSON *object);
	bool add(const std::string& name);
	cJSON *mJsonObj;
	PlayerJsonObject *mParent;
};

/**
 * @class PlayerJsonParseException
 * @brief Handles the exception for JSON parser
 */
class PlayerJsonParseException : public std::exception
{
public:
	virtual const char* what() const throw() override
	{
		return "Failed to parse JSON string";
	}
};

#endif //_PLAYER_JSON_OBJECT_H

