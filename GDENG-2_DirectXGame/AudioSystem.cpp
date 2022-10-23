#include "AudioSystem.h"

AudioSystem::AudioSystem()
{
}

bool AudioSystem::init()
{
	HRESULT hr;

	hr = CoInitializeEx( nullptr, COINIT_MULTITHREADED );
	if (FAILED(hr))
	{
		return false;
	}

	if (FAILED(hr = XAudio2Create(&m_audio_system, 0, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		return false;
	}

	if (FAILED(hr = m_audio_system->CreateMasteringVoice(&m_master_voice)))
	{
		return false;
	}

	return true;
}

bool AudioSystem::loadAudioFile(const wchar_t* file_name)
{
    // Open the file
    HANDLE hFile = CreateFile(
    file_name,
    GENERIC_READ,
    FILE_SHARE_READ,
    NULL,
    OPEN_EXISTING,
    0,
    NULL);

    if(INVALID_HANDLE_VALUE == hFile)
    {
        return false;
    }

    if(INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
    {
        return false;
    }

    DWORD dwChunkSize;
    DWORD dwChunkPosition;
    //check the file type, should be fourccWAVE or 'XWMA'
    findChunk(hFile,fourccRIFF,dwChunkSize, dwChunkPosition);
    DWORD filetype;
    readChunkData(hFile,&filetype,sizeof(DWORD),dwChunkPosition);
    if (filetype != fourccWAVE)
    {
        return false;
    }

    //locate the 'fmt ' chunk
    findChunk(hFile,fourccFMT, dwChunkSize, dwChunkPosition);
    readChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

    //fill out the audio data buffer with the contents of the fourccDATA chunk
    findChunk(hFile,fourccDATA,dwChunkSize, dwChunkPosition);
    BYTE * pDataBuffer = new BYTE[dwChunkSize];
    readChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

    buffer.AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
    buffer.pAudioData = pDataBuffer;  //buffer containing audio data
    buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
}

bool AudioSystem::playAudio()
{
    HRESULT hr;
    if(FAILED(hr = m_audio_system->CreateSourceVoice(&m_source_voice, (WAVEFORMATEX*)&wfx)))
    {
        return false;
    }

    if(FAILED(hr = m_source_voice->SubmitSourceBuffer(&buffer)))
    {
        return false;
    }

    if (FAILED(hr = m_source_voice->Start(0)))
    {
        return false;
    }

    return true;
}

void AudioSystem::stopAudio()
{
    m_source_voice->Stop();
    m_source_voice->FlushSourceBuffers();
}

void AudioSystem::setVolume(float volume)
{
    m_master_voice->SetVolume(volume / 100.0f);
}

void AudioSystem::setPitch(float pitch)
{
    m_source_voice->SetFrequencyRatio(pitch);
}

bool AudioSystem::release()
{
	m_audio_system->Release();
	CoUninitialize();
	delete this;
	return true;
}

AudioSystem::~AudioSystem()
{
	
}

HRESULT AudioSystem::findChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;
    if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
        return HRESULT_FROM_WIN32( GetLastError() );

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if(0 == ReadFile( hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32( GetLastError() );

        if(0 == ReadFile( hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32( GetLastError() );

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if(0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                hr = HRESULT_FROM_WIN32( GetLastError() );
            break;

        default:
            if(INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
            return HRESULT_FROM_WIN32( GetLastError() );            
        }

        dwOffset += sizeof(DWORD) * 2;

        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;

        if (bytesRead >= dwRIFFDataSize) return S_FALSE;

    }

    return S_OK;
}

HRESULT AudioSystem::readChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
    if(INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());
    DWORD dwRead;
    if(0 == ReadFile( hFile, buffer, buffersize, &dwRead, NULL))
        hr = HRESULT_FROM_WIN32(GetLastError());
    return hr;
}