#ifndef SoundManager_H_
#define SoundManager_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>



enum sound_type{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager {

	//instancia para el singleton
	static SoundManager* s_pInstance;
	
	//maps para identificar los sonidos
	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;

	SoundManager();
public:
	~SoundManager();

	static SoundManager* Instance(){

		if (s_pInstance == 0){
			s_pInstance = new SoundManager();
		}
		return s_pInstance;
	}

	
	bool load(std::string fileName, std::string id, sound_type
		type);

	void playSound(std::string id, int loop);

	void playMusic(std::string id, int loop);


//private:

	//SoundManager(const SoundManager&);
	//SoundManager& operator=(const SoundManager&);

};
//typedef SoundManager TheSoundManager;



#endif // !SoundManager_H_

