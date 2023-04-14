#pragma once
#include <assert.h>
#include "../GLib/GLib.h"
#include "../JobSystem/Console/ConsolePrint.h"
#include "../JobSystem/JobSystem/JobSystem.h"
#include "../includes/nlohmann/json.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>



namespace Helper {
	void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);

	GLib::Sprite* CreateSprite(const char* i_pFilename);

	void ProcessFileContents(uint8_t* i_pFileContents, size_t i_sizeFileContents, std::function<void(uint8_t*, size_t)> i_Processor);

	void PrintFileContents(uint8_t* i_pFileContents, size_t i_sizeFileContents);

	class ProcessFile
	{
	public:
		ProcessFile(const char* i_pFilename, std::function<void(uint8_t*, size_t)> i_Processor, const Engine::HashedString i_QueueName = Engine::JobSystem::GetDefaultQueue(), Engine::JobSystem::JobStatus* i_pJobStatus = nullptr) :
			m_pFilename(i_pFilename),
			m_Processor(i_Processor),
			m_QueueName(i_QueueName),
			m_pJobStatus(i_pJobStatus)
		{
			assert(m_pFilename);
		}

		void operator() ()
		{
			if (m_pFilename)
			{
				size_t sizeFileContents = 0;
				uint8_t* pFileContents = LoadFile(m_pFilename, sizeFileContents);

				if (pFileContents && sizeFileContents)
				{
					if (!Engine::JobSystem::ShutdownRequested())
					{
						std::cout << "ProcessFile finished loading file.\n";

						// this works around C++11 issue with capturing member variable by value
						std::function<void(uint8_t*, size_t)> Processor = m_Processor;

						Engine::JobSystem::RunJob(
							m_QueueName,
							[pFileContents, sizeFileContents, Processor]()
							{
								ProcessFileContents(pFileContents, sizeFileContents, Processor);
							},
							m_pJobStatus,
								"ProcessFileContents"
								);
					}
					else
					{
						delete[] pFileContents;
					}
				}
			}
		}

		static uint8_t* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
		{
			assert(i_pFilename != NULL);

			FILE* pFile = NULL;

			errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
			if (fopenError != 0)
				return NULL;

			assert(pFile != NULL);

			int FileIOError = fseek(pFile, 0, SEEK_END);
			assert(FileIOError == 0);

			long FileSize = ftell(pFile);
			assert(FileSize >= 0);

			FileIOError = fseek(pFile, 0, SEEK_SET);
			assert(FileIOError == 0);

			uint8_t* pBuffer = new uint8_t[FileSize];
			assert(pBuffer);

			size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
			assert(FileRead == FileSize);

			fclose(pFile);

			o_sizeFile = FileSize;

			return pBuffer;
		}
	private:
		const char* m_pFilename;
		std::function<void(uint8_t*, size_t)>  m_Processor;
		Engine::HashedString m_QueueName;
		Engine::JobSystem::JobStatus* m_pJobStatus;
	};

}
