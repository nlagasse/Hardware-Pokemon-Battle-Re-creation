#include "sdcard.h"

FATFS FS_instance;
int theVolume = 2;
u8 *theBuffer = NULL;
size_t theBufferSize = 0;

char wavFiles[MAX_FILES][MAX_FILENAME_LENGTH] = {0};
int wavFileCount = 0;
u8 *buffers[MAX_FILES] = {0};

//char imageFiles[MAX_IMAGES][MAX_IMAGE_NAME_LENGTH] = {0};
//int imageFileCount = 0;
//u8 *imageBuffers[MAX_IMAGES] = {0};
//size_t imageBufferSizes[MAX_IMAGES] = {0};

typedef struct {
	u16 wFormatTag;
	u16 nChannels;
	u32 nSamplesPerSec;
	u32 nAvgBytesPerSec;
	u16 nBlockAlign;
	u16 wBitsPerSample;
	u16 cbSize;
	u16 wValidBitsPerSample;
	u32 dwChannelMask;
	u8 SubFormat[16];
} fmtChunk_t;

fmtChunk_t fmtChunks[MAX_FILES] = {0};

typedef struct {
	char riff[4];
	u32 riffSize;
	char wave[4];
} headerWave_t;

headerWave_t headerWaves[MAX_FILES] = {0};

typedef struct {
	char ckId[4];
	u32 cksize;
} genericChunk_t;

genericChunk_t genericChunks[MAX_FILES] = {0};

FIL files[MAX_FILES] = {0};
UINT nBytesRead[MAX_FILES] = {0};

u32 *imageIntArrays[MAX_IMAGES];
size_t imageIntArraySizes[MAX_IMAGES];

#define fatalError(msg) throwFatalError(__PRETTY_FUNCTION__,msg)

void throwFatalError(const char *func,const char *msg) {
	printf("%s() : %s\r\n",func,msg);
	for(;;);
}

void loadWavFiles(){
	printf("Loading %d .wav files..\r\n", wavFileCount);
	// load all .wav files into buffer arrays
	for(int i=0; i<wavFileCount; i++){

		FRESULT res = f_open(&files[i], wavFiles[i], FA_READ);
		if (res!=0) {fatalError("File not found");}
		res = f_read(&files[i],(void*)&headerWaves[i],sizeof(headerWaves[i]),&nBytesRead[i]);
		if (res!=0) {fatalError("Failed to read file");}
		if (memcmp(headerWaves[i].riff,"RIFF",4)!=0) {fatalError("Illegal file format. RIFF not found");}
		if (memcmp(headerWaves[i].wave,"WAVE",4)!=0) {fatalError("Illegal file format. WAVE not found");}

		// Walk through the chunks and interpret them
		for(;;) {
			// read chunk header
			res = f_read(&files[i],(void*)&genericChunks[i],sizeof(genericChunks[i]),&nBytesRead[i]);
			if (res!=0) {
				fatalError("Failed to read file");
			}
			if (nBytesRead[i]!=sizeof(genericChunks[i])) {
				break; // probably EOF
			}

			// The "fmt " is compulsory and contains information about the sample format
			if (memcmp(genericChunks[i].ckId,"fmt ",4)==0) {
				res = f_read(&files[i],(void*)&fmtChunks[i],genericChunks[i].cksize,&nBytesRead[i]);
				if (res!=0) {
					fatalError("Failed to read file");
				}
				if (nBytesRead[i]!=genericChunks[i].cksize) {
					fatalError("EOF reached");
				}
				if (fmtChunks[i].wFormatTag!=1) {
					fatalError("Unsupported format");
				}
				if (fmtChunks[i].nChannels!=2) {
					fatalError("Only stereo files supported");
				}
				if (fmtChunks[i].wBitsPerSample!=16) {
					fatalError("Only 16 bit per samples supported");
				}
			}
			// the "data" chunk contains the audio samples
			else if (memcmp(genericChunks[i].ckId,"data",4)==0) {
				buffers[i] = malloc(genericChunks[i].cksize);
				if (!buffers[i]){
					fatalError("Could not allocate memory");
				}
				theBufferSize = genericChunks[i].cksize;

				res = f_read(&files[i],(void*)buffers[i],theBufferSize,&nBytesRead[i]);
				if (res!=0) {
					fatalError("Failed to read file");
				}
				if (nBytesRead[i]!=theBufferSize) {
					fatalError("Didn't read the complete file");
				}
			}
			// Unknown chunk: Just skip it
			else {
				DWORD fp = f_tell(&files[i]);
				f_lseek(&files[i],fp + genericChunks[i].cksize);
			}
		}
		printf("Loaded [%d/%d] .wav files\r\n", i+1, wavFileCount);
		printf("Loaded wave file [%d/%d]: %s\r\n", i + 1, wavFileCount, wavFiles[i]);
	    f_close(&files[i]);
	}
	printf("Loaded all .wav files\r\n");
}

void sd_card_initialization(){
    setvbuf(stdin, NULL, _IONBF, 0);
	print("Mounting SD Card\r\n");
	FRESULT result = f_mount(&FS_instance,"0:/", 1);
	if (result != 0) {
		print("Couldn't mount SD Card. Press RETURN to try again\r\n");
		getchar();
	}

	wavFileCount = 0;

	// Look for *.wav files and copy file names to files[]
	DIR dir;
	FRESULT res = f_opendir(&dir, "0:/");
	if (res != FR_OK) {
		print("Couldn't read root directory. Press RETURN to try again\r\n");
		getchar();
	}
	for (;;) {
		FILINFO fno;
		res = f_readdir(&dir, &fno);
		if (res != FR_OK || fno.fname[0] == 0) {
			break;
		}
		if (fno.fattrib & AM_DIR) {                 // It's a directory
		}
		else if (strstr(fno.fname,".wav")!=NULL || strstr(fno.fname,".WAV")!=NULL) { // It's a WAV file
			strncpy(wavFiles[wavFileCount], fno.fname, MAX_FILENAME_LENGTH - 1);
			wavFiles[wavFileCount][MAX_FILENAME_LENGTH - 1] = '\0'; // Ensure null termination
			wavFileCount++;
		}
		else {										// It's a normal file
		}
		xil_printf("Detected file: %s\r\n", fno.fname);
	}
	f_closedir(&dir);

	if (wavFileCount == 0) {
		print("No WAV files found. Press RETURN to try again\r\n");
		getchar();
	}else{
		xil_printf("Found %d .wav files\r\n", wavFileCount);
	}

	// load all wav files into buffer
	loadWavFiles();

}

void playWavFile(int num) {
    if (buffers[num]) {

        // Crude in-place down-sampling: Basically taking every n'th of a sample
        // Jerobeam Fenderson's WAV files use a sampling rate of 192kHz (https://oscilloscopemusic.com)
        // Our sampling rate is actually 39.0625, so a 44.1kHz file will play a at 88.5% the speed (and lower in pitch).
    	double subSample = (double)fmtChunks[num].nSamplesPerSec/4410000;

//    	double subSample = 960000/44100;
    	if (subSample>1.6) {
    		int skip = (int)(subSample+0.5);
    		u32 nNewTotal = genericChunks[num].cksize/4/skip;
    		u32 *pSource = (u32*) buffers[num];
    		u32 *pDest = (u32*) buffers[num];
    		for(u32 i=0;i<nNewTotal;++i,pSource+=skip,pDest++) {
    			*pDest = *pSource;
    		}
    		genericChunks[num].cksize = nNewTotal*4;
    	}

    	// Changing the volume and swap left/right channel and polarity
    	{
    		u32 *pSource = (u32*) buffers[num];
    		for(u32 i=0;i<genericChunks[num].cksize/4;++i) {
    			short left  = (short) ((pSource[i]>>16) & 0xFFFF);
    			short right = (short) ((pSource[i]>> 0) & 0xFFFF);
    			int left_i  = -(int)left * theVolume / 4;
    			int right_i = -(int)right * theVolume / 4;
    			if (left>32767) left = 32767;
    			if (left<-32767) left = -32767;
    			if (right>32767) right = 32767;
    			if (right<-32767) right = -32767;
    			left = (short)left_i;
    			right = (short)right_i;
//    			pSource[i] = ((u32)right<<16) + (u32)left;

    			if(stop == 1){
    				stop = 0;
    				return;
    			}

    			for(int i=0;i<450;i++)
    				asm("NOP");
				Xil_Out32(I2S_DATA_TX_L_REG, left*VOLUME);
				Xil_Out32(I2S_DATA_TX_R_REG, right*VOLUME);
    		}
    		playing = 0;
    	}
    }
}
