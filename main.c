#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "include/discord_rpc.h"

const char* APPLICATION_ID = "671691503026044938";

const char ext[32][12] = {
	"bash",
	"c",
	"cpp",
	"cs",
	"css",
	"docker",
	"git",
	"go",
	"h",
	"hs",
	"htm",
	"java",
	"js",
	"json",
	"kt",
	"log",
	"lua",
	"md",
	"npmrc",
	"php",
	"py",
	"rb",
	"rs",
	"sass",
	"sh",
	"svg",
	"swift",
	"travis",
	"vim",
	"xml",
	"yml"
};

int binary_search(const char (*list)[12], char item[], int n) {

	int last = n - 1;
	int fir = 0;
	int mid = (fir + last) / 2;

	while(fir <= last) {

		if(strcmp(list[mid], item) < 0) {
			fir = mid + 1;
		} else if(strcmp(list[mid], item) == 0) {
			return mid;
		} else {
			last = mid - 1;
		}

		mid = (fir + last) / 2;
	}

	return -1;
}

void InitDiscord() {
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

void UpdatePresence(char *details, char *state, char *largeImageKey, char *largeImageText, time_t timestamp) {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));

	discordPresence.details = details;
	discordPresence.state = state;

	int len = sizeof(ext) / sizeof(ext[0]);
	int index = binary_search(ext, largeImageKey, len);

	if(index == -1) {
		int b = 0;
		    len -= 1;

		for(int i = len; i != 0; i--) {
			if(ext[i][0] == largeImageKey[0] && b == 0) {
				if(strstr(largeImageKey, ext[i])) {
					discordPresence.largeImageKey = ext[i];
					b = 1;
					break;
				}
			}
		}

		if(!b) discordPresence.largeImageKey = "default";
	} else {
		discordPresence.largeImageKey = ext[index];
	}

	discordPresence.largeImageText = largeImageText;
	discordPresence.startTimestamp = timestamp;

	Discord_UpdatePresence(&discordPresence);
}

void MainLoop() {
	time_t start = time(0);

	while(!sleep(5)) {
		FILE *f = fopen("/tmp/vdrpc", "r");
		if(!f) return;

		char buffer[3][256];

		if(!fgets(buffer[0], sizeof(buffer[0]), f)) continue;   // get details

		char *details = buffer[0];
		char *state;

		if(!strcmp(details, "Editing \n")) {
			details = "Editing an unnamed file.";
		}

		fgets(buffer[1], sizeof(buffer[1]), f);                 // get state

		if(fgets(buffer[2], sizeof(buffer[2]), f) != NULL) {    // get size
			state = strcat(buffer[2], " bytes");
		} else {
			state = buffer[1];
		}

		char largeImageKey[32];
		char largeImageText[128] = "text";

		int i, j, b = 0;

		for(i = j = 0; details[i] != '\0'; i++) {
			if(details[i - 1] == '.') {	// if [i - 1] -> .c = c
				b = 1;
			}
			if(b) {
				largeImageKey[j++] = details[i];
			}
		}

		largeImageKey[strlen(largeImageKey + 1)] = '\0';	// add zero byte

		UpdatePresence(details, state, largeImageKey, largeImageText, start);

		fclose(f);
	}
}

int main( void ) {
	InitDiscord();
	MainLoop();
	Discord_Shutdown();
	return 0;
}
