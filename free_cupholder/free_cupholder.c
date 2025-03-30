#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MBOXA(sTEXT) MessageBoxA(NULL, sTEXT, "Free Cupholder", MB_OK | MB_ICONERROR)


static inline void showFail(void);
static inline void showFailVerbose(LPCSTR sText);
static inline void showFailVerboseExit(LPCSTR sText, int retCode);
static BOOL ejectOpticalDrive(LPCSTR sDriveLetter);

static BOOL bVerbose = FALSE;


int main(int argc, char **argv)
{
	// detect args
	BOOL bDryrun = FALSE;

	if (argc > 1) {
		for (int i = 0; i < argc; i++) {
			if (strlen(argv[i]) != 2)
				continue;
			else if ((argv[i])[0] != '-')
				continue;
			else {
				switch ((argv[i])[1]) {
					case 'h':
						printf("-h --> show help\n-v --> be verbose\n-d --> dry-run (no Cupholder, dump collected info)\n");
						return 0;
						break;
					
					case 'v':
						bVerbose = TRUE;
						break;
					
					case 'd':
						bDryrun = TRUE;
						break;
					
					default:
					continue;
					break;
				}
			}
		}
	}

	// get drives
	DWORD dDrives = GetLogicalDrives();
	if (dDrives == 0) {
		showFailVerboseExit("No Drives detected!", 1);
	}

	// loop through bitmask and break at first optical drive
	PSTR sDriveLetter = (PSTR) calloc(3, sizeof(CHAR));
	if (sDriveLetter == NULL)
		showFailVerboseExit("Couldn't allocate memory for sDriveLetter!", 2);
	BOOL bDriveOptical = FALSE;
	for (DWORD i = 0; i < sizeof(DWORD) * 8; i++) {
		if (((dDrives >> i) & 0x1 ) != 0) {
			sprintf(sDriveLetter, "%c:", 'A' + i);
			if (GetDriveTypeA(sDriveLetter) == DRIVE_CDROM) {
				bDriveOptical = TRUE;
				break;
			}
		}
	}
	int ret = 3;
	if (!bDriveOptical) {
		showFailVerbose("No optical Drive detected.");
		goto cleanup;
	}
	
	// actually eject, or not
	ret = 4;
	if (bDryrun) {
		printf("Detected optical Drive %s\n", sDriveLetter);
		goto cleanup;
	} else if (ejectOpticalDrive(sDriveLetter)) {
		MessageBoxA(NULL, "Enjoy your free Cupholder!", "Free Cupholder", MB_OK | MB_ICONINFORMATION);
		ret = 0;
	}


	// cleanup
	cleanup:
	free((void *) sDriveLetter);
	return ret;
}


static BOOL ejectOpticalDrive(LPCSTR sDriveLetter)
{	
	// convert string
	PSTR sDriveHandle = (PSTR) calloc(7, sizeof(CHAR));
	if (sDriveHandle == NULL) {
		showFailVerbose("Couldn't allocate memory for sDriveHandle!");
		return FALSE;
	}
	sprintf(sDriveHandle, "\\\\.\\%s", sDriveLetter);
	
	BOOL ret = FALSE;
	HANDLE hDevice = CreateFileA(sDriveHandle, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	free((void *) sDriveHandle);
	if (hDevice == INVALID_HANDLE_VALUE) {
		showFailVerbose("Could not obtain handle!");
		goto end;
	}
	
	// DeviceIoControl needs either lpBytesReturned or lpBytesOverlapped to be non-NULL
	// we use lpBytesReturned
	DWORD bytes = 0;
	// lock Volume, will fail if it's in use
	ret = DeviceIoControl(hDevice, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &bytes, NULL);
	if (ret == FALSE) {
		showFailVerbose("Unable to lock Volume!");
		goto cleanend;
	}

	// dismount volume
	ret = DeviceIoControl(hDevice, FSCTL_DISMOUNT_VOLUME, NULL, 0, NULL, 0, &bytes, NULL);
	if (ret == FALSE) {
		showFailVerbose("Unable to dismount Volume!");
		goto cleanend;
	}

	// stop prevention of media removal
	PREVENT_MEDIA_REMOVAL prevent;
	prevent.PreventMediaRemoval = FALSE;
	ret = DeviceIoControl(hDevice, IOCTL_STORAGE_MEDIA_REMOVAL, &prevent, sizeof(PREVENT_MEDIA_REMOVAL), NULL, 0, &bytes, NULL);
	if (ret == FALSE) {
		showFailVerbose("Unable to prevent media removal!");
		goto cleanend;
	}

	// eject
	ret = DeviceIoControl(hDevice, IOCTL_STORAGE_EJECT_MEDIA, NULL, 0, NULL, 0, &bytes, NULL);
	if (ret == FALSE) {
		showFailVerbose("Unable to eject!");
		goto cleanend;
	}

	ret = TRUE;
	cleanend:
	CloseHandle(hDevice);
	end:
	return ret;
}


static inline void showFail(void)
{
	MBOXA("No Cupholder for you :(");
}


static inline void showFailVerbose(LPCSTR sText)
{
	if (bVerbose)
		MBOXA(sText);
	else
		showFail();
}


static inline void showFailVerboseExit(LPCSTR sText, int retCode)
{
	showFailVerbose(sText);
	exit(retCode);
}
