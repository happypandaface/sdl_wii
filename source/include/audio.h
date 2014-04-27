#ifndef _AUDIO_H_
#define _AUDIO_H_

#define SND_TONE 1

class AudioPlayer
{
	public:
		AudioPlayer();
		~AudioPlayer();
		void init();
		int playSound(int sound);
		void placeholder_callback();
	private:
		int var;
};

#endif