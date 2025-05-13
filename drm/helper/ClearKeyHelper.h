/*
 * If not stated otherwise in this file or this component's license file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
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
#ifndef _CLEARKEY_HELPER_H
#define _CLEARKEY_HELPER_H

/**
 * @file ClearKeyHelper.cpp
 * @brief Implemented Clear key helper functions
 */

#include <memory>

#include "DrmHelper.h"

/**
 * @class ClearKeyHelper
 * @brief Class handles the clear key license operations
 */
class ClearKeyHelper : public DrmHelper
{
public:
	const std::string& ocdmSystemId() const override;

	void createInitData(std::vector<uint8_t>& initData) const override;

	bool parsePssh(const uint8_t* initData, uint32_t initDataLen) override;

	bool isClearDecrypt() const override { return true; }

	void getKey(std::vector<uint8_t>& keyID) const override;

	virtual int getDrmCodecType() const override { return CODEC_TYPE; }

	void generateLicenseRequest(const ChallengeInfo& challengeInfo, LicenseRequest& licenseRequest) const override;

	void transformLicenseResponse(std::shared_ptr<DrmData> licenseResponse) const override;

	virtual const std::string& friendlyName() const override { return FRIENDLY_NAME; };

	ClearKeyHelper(const struct DrmInfo& drmInfo) : DrmHelper(drmInfo), mInitData(), mKeyID(), mPsshStr(),
		CLEARKEY_KEY_ID("1"), FRIENDLY_NAME("Clearkey"), CODEC_TYPE(0), CLEARKEY_DASH_KEY_ID_OFFSET(32u),
		CLEARKEY_DASH_KEY_ID_LEN(16u), KEY_ID_OFFSET(12), KEY_PAYLOAD_OFFSET(14), BASE_16(16)
	{}

	~ClearKeyHelper() { }

private:
	static const std::string CLEARKEY_OCDM_ID;
	const std::string CLEARKEY_KEY_ID;
	const std::string FRIENDLY_NAME;
	const int CODEC_TYPE;
	const size_t CLEARKEY_DASH_KEY_ID_OFFSET; // Offset in the PSSH to find the key ID for DASH
	const size_t CLEARKEY_DASH_KEY_ID_LEN; // Length of the key ID for DASH
	const int KEY_ID_OFFSET;
	const int KEY_PAYLOAD_OFFSET;
	const int BASE_16;

	std::string mPsshStr;
	std::vector<uint8_t> mInitData;
	std::vector<uint8_t> mKeyID;
};

/**
 * @class ClearKeyHelperFactory
 * @brief Helper Factory class to maintain Player DRM data
 */

class ClearKeyHelperFactory : public DrmHelperFactory
{
public:
	static const int CLEARKEY_WEIGHTING = DEFAULT_WEIGHTING * 2;

	DrmHelperPtr createHelper(const struct DrmInfo& drmInfo) const;

	void appendSystemId(std::vector<std::string>& systemIds) const;

	bool isDRM(const struct DrmInfo& drmInfo) const;

public:
	ClearKeyHelperFactory() : DrmHelperFactory(CLEARKEY_WEIGHTING) {};
};

#endif //_CLEARKEY_HELPER_H
