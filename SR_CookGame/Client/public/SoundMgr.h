#pragma once
#include "Base.h"

BEGIN(Client)
class CSoundMgr final : public CBase
{
	DECLARE_SINGLETON(CSoundMgr)
public:
	enum CHANNELID {BGM, PLAYER, MONSTER, DASH ,EFFECT, UI, MAXCHANNEL};
private:
	explicit CSoundMgr();
	virtual  ~CSoundMgr() = default;
public:
	void Initialize(); 
public:
	void PlaySound(TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void StopAll();
private:
	void LoadSoundFile(); 
private:
	map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL]; 
	FMOD_SYSTEM* m_pSystem; 
public:
	virtual void Free() override;
};
END
