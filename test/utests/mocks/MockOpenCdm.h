/*
* If not stated otherwise in this file or this component's license file the
* following copyright and licenses apply:
*
* Copyright 2024 RDK Management
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

#ifndef PLAYER_MOCK_OPEN_CDM_H
#define PLAYER_MOCK_OPEN_CDM_H

#include "open_cdm.h"
#include <gmock/gmock.h>

struct _GstBuffer;
typedef struct _GstBuffer GstBuffer;

class MockOpenCdm
{
public:
	MOCK_METHOD(OpenCDMError, opencdm_session_decrypt,
				(struct OpenCDMSession * session, uint8_t encrypted[],
				 const uint32_t encryptedLength, const EncryptionScheme encScheme,
				 const EncryptionPattern pattern, const uint8_t* IV, uint16_t IVLength,
				 const uint8_t* keyId, const uint16_t keyIdLength, uint32_t initWithLast15));
	MOCK_METHOD(OpenCDMError, opencdm_destruct_system, (struct OpenCDMSystem* system));
    MOCK_METHOD(OpenCDMSystem*, opencdm_create_system, (const char keySystem[]));
	MOCK_METHOD(OpenCDMError, opencdm_construct_session,
				(struct OpenCDMSystem * system, const LicenseType licenseType,
				 const char initDataType[], const uint8_t initData[], const uint16_t initDataLength,
				 const uint8_t CDMData[], const uint16_t CDMDataLength,
				 OpenCDMSessionCallbacks* callbacks, void* userData,
				 struct OpenCDMSession** session));
	MOCK_METHOD(OpenCDMError, opencdm_session_update,
				(struct OpenCDMSession * session, const uint8_t keyMessage[],
				 const uint16_t keyLength));        
	MOCK_METHOD(OpenCDMError, opencdm_session_close, (struct OpenCDMSession* session));
	MOCK_METHOD(OpenCDMError, opencdm_destruct_session, (struct OpenCDMSession* session));
	MOCK_METHOD(KeyStatus, opencdm_session_status, (const struct OpenCDMSession* session, const uint8_t keyId[], const uint8_t length));

};

extern MockOpenCdm* g_mockopencdm;

#endif /* PLAYER_MOCK_OPEN_CDM_H */
