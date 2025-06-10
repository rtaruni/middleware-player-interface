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


/**
 * @file WebvttSubtecDevInterface.cpp
 * @brief Implementation of the WebVTT subtitle interface using Subtec for rendering.
 */

#include "WebvttSubtecDevInterface.hpp"
#include "PlayerLogManager.h"
#include <sstream>

/**
 * @brief Constructs a WebvttSubtecDevInterface instance for WebVTT subtitle rendering.
 *
 * Initializes the interface with the specified screen dimensions and sets up the
 * communication channel with the Subtec subtitle engine.
 *
 * @param width The width of the video screen.
 * @param height The height of the video screen.
 *
 * @throws std::runtime_error if the subtitle communication channel fails to initialize.
 */
WebvttSubtecDevInterface::WebvttSubtecDevInterface(int width, int height) : m_channel(nullptr)
{
    m_channel = SubtecChannel::SubtecChannelFactory(SubtecChannel::ChannelType::TTML);
    if (!m_channel->InitComms())
    {
        MW_LOG_INFO("Init failed - subtitle parsing disabled");
        throw std::runtime_error("PacketSender init failed");
    }
    m_channel->SendResetAllPacket();
    m_channel->SendSelectionPacket(width, height);
    m_channel->SendMutePacket();
}

/**
 * @brief Sends WebVTT cue data to the subtitle rendering channel.
 *
 * Converts the input TTML string to a byte vector and sends it to the subtitle channel.
 *
 * @param ttml The TTML string containing subtitle cue data.
 */
void WebvttSubtecDevInterface::sendCueData(const std::string& ttml)
{
    std::vector<uint8_t> data(ttml.begin(), ttml.end());
    m_channel->SendDataPacket(std::move(data), 0);
}

/**
 * @brief Resets the subtitle rendering channel.
 *
 * Sends a reset packet to the subtitle channel to clear any existing subtitle data.
 */
void WebvttSubtecDevInterface::reset()
{
    m_channel->SendResetChannelPacket();
}

/**
 * @brief Updates the subtitle rendering channel with the current playback timestamp.
 *
 * Sends a timestamp packet to the subtitle channel to synchronize subtitle rendering
 * with the current playback position.
 *
 * @param positionMs The current playback position in milliseconds.
 */
void WebvttSubtecDevInterface::updateTimestamp(unsigned long long positionMs)
{
    MW_LOG_TRACE("timestamp: %lldms", positionMs );
    m_channel->SendTimestampPacket(positionMs);
}

/**
 * @brief Initializes the subtitle rendering channel with a base presentation timestamp (PTS).
 *
 * Sends a timestamp packet to the subtitle channel based on the provided base PTS.
 *
 * @param basePTS The base presentation timestamp (PTS) in microseconds.
 * @return true Always returns true upon successful initialization.
 */
bool WebvttSubtecDevInterface::init(unsigned long long basePTS)
{
    bool ret = true;
    m_channel->SendTimestampPacket(static_cast<uint64_t>(basePTS));
    return ret;
}

/**
 * @brief Mutes or unmutes subtitle rendering.
 *
 * Sends a mute or unmute packet to the subtitle rendering channel based on the input flag.
 * This is typically used to control subtitle visibility during playback.
 *
 * @param mute If true, subtitles are muted (hidden); if false, subtitles are unmuted (shown).
 */
void WebvttSubtecDevInterface::mute(bool mute)
{
    if (mute)
        m_channel->SendMutePacket();
    else
        m_channel->SendUnmutePacket();
}

/**
 * @brief Pauses or resumes subtitle rendering.
 *
 * Sends a pause or resume packet to the subtitle rendering channel based on the input flag.
 * This is typically used to synchronize subtitle behavior with media playback state.
 *
 * @param pause If true, subtitles are paused; if false, subtitles are resumed.
 */
void WebvttSubtecDevInterface::pause(bool pause)
{
    if (pause)
        m_channel->SendPausePacket();
    else
        m_channel->SendResumePacket();
}

