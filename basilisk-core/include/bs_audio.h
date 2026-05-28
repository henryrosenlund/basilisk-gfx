 
 /**
  bs_audio.h
  Sounds
  */

#ifndef BS_AUDIO_H
#define BS_AUDIO_H

#include <bs_types.h>



  /*==============================================================================
   * Audio
   *============================================================================*/

   /**
    Plays a sound
	@param sound
	@param volume
    */
	BSAPI bs_Result
	bs_playSound(
		bs_Sound* sound,
		float volume);
	
	BSAPI bs_Result
	bs_sound(
		bs_Resource* resource, 
		bs_U32 flags);

   /**
    Initialize audio, needs to be done once before playing sounds
    */
	BSAPI bs_Result
	bs_iniAudio();

#endif
