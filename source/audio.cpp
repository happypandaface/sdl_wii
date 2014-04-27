#include "audio.h"
#include "audio/tone.h"

#ifndef WINDOWS_BUILD
	#include <asndlib.h>
#endif

AudioPlayer::AudioPlayer()
{
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::init()
{
	#ifndef WINDOWS_BUILD
		ASND_Init();
		ASND_Pause(0);
	#endif
}

void AudioPlayer::placeholder_callback()
{
}

int AudioPlayer::playSound(int sound)
{
	#ifndef WINDOWS_BUILD
		ASND_SetVoice(0, VOICE_MONO_16BIT, 4440, 0, toneArray, sizeof(toneArray), MAX_VOLUME, MAX_VOLUME, NULL);
	#endif
	return 1;
}