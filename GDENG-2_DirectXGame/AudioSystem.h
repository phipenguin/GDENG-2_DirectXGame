#pragma once
#include <xaudio2.h>

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

class AudioSystem
{
public:
	AudioSystem();
	bool init();

	bool loadAudioFile(const wchar_t* file_name);
	bool playAudio();

	void setVolume(float volume);
	void setPitch(float pitch);

	bool release();
	~AudioSystem();
private:
	HRESULT findChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
	HRESULT readChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);

	IXAudio2* m_audio_system = nullptr;
	IXAudio2MasteringVoice* m_master_voice = nullptr;
	IXAudio2SourceVoice* m_source_voice;

	WAVEFORMATEXTENSIBLE wfx = {0};
	XAUDIO2_BUFFER buffer = {0};
};