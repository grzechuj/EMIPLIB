/*
    
  This file is a part of EMIPLIB, the EDM Media over IP Library.
  
  Copyright (C) 2006-2016  Hasselt University - Expertise Centre for
                      Digital Media (EDM) (http://www.edm.uhasselt.be)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  
  USA

*/

/**
 * \file mipopusencoder.h
 */

#ifndef MIPOPUSENCODER_H

#define MIPOPUSENCODER_H

#include "mipconfig.h"

#ifdef MIPCONFIG_SUPPORT_OPUS

#include "mipoutputmessagequeue.h"
#include "miptime.h"
#include <list>

class MIPEncodedAudioMessage;

/** Compress audio using the Opus codec.
 *  Using this component, floating point mono raw audio messages and raw 16 bit raw audio
 *  messages can be compressed using the Opus codec. Messages generated by this component 
 *  are encoded audio messages with subtype MIPENCODEDAUDIOMESSAGE_TYPE_OPUS.
 */
class EMIPLIB_IMPORTEXPORT MIPOpusEncoder : public MIPOutputMessageQueue
{
public:
	/** Used to specify the mode in which the encoder should operate. */
	enum EncoderType 
	{ 
		/** Use this for voice communication. */
		VoIP, 
		/** Use this for general audio streaming. */
		Audio, 
		/** Only use this when the having the lowest possible codec delay is extremely important. */
		RestrictedLowDelay 
	};

	MIPOpusEncoder();
	~MIPOpusEncoder();

	/** Initialize the Opus encoding component.
	 *  This function initializes the Opus encoding component. 
	 *  \param inputSamplingRate Sampling rate incoming audio messages will have. 
	 *  \param channels The number of channels incoming audio messages will have.
	 *  \param application Specifies the encoder mode that should be selected.
	 *  \param interval Specifies the amount of time each incoming audio message will contain.
	 *  \param targetBitrate The codec should produce data corresponding to this bitrate (note that this does not
	 *                       include header overhead from IP/UDP/RTP when transmitting the data over the network).
	 *                       Specify 0 for the codec default, or select a value between 6000 and 510000.
	 */
	bool init(int inputSamplingRate, int channels, EncoderType application, MIPTime interval, int targetBitrate = 0);

	/** De-initializes the Opus encoder. */
	bool destroy();

	/** Sets the codec bitrate.
	 *  The codec should produce data corresponding to this bitrate (note that this does not
	 *  include header overhead from IP/UDP/RTP when transmitting the data over the network).
	 *  Specify 0 for the codec default, or select a value between 6000 and 510000. */
	bool setBitrate(int targetBitrate = 0);

	bool push(const MIPComponentChain &chain, int64_t iteration, MIPMessage *pMsg);
private:
	bool m_init;

	int m_inputSamplingRate, m_inputChannels;
	int m_inputFrames;
	void *m_pState;
	uint8_t *m_pBuffer;
	int m_bufLength;
};	

#endif // MIPCONFIG_SUPPORT_OPUS

#endif // MIPOPUSENCODER_H

