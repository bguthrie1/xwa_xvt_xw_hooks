#include "targetver.h"
#include "PA.h"
#include "XWAFramework.h"
#include <cstring>
#include <cstdlib>

int PAHook(int* params)
{
	int randNum1;
	int randNum2;
	int randNum3;
	int randNum4;
	int randModified;
	__int8 briefingLogo;
	QuickMissionData* QuickMissionDataPtr = *(QuickMissionData**)0x9EB8E0;

	switch (randXWA() % 24)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		goto Copy_Announcement_1Through9;
	case 6:
	case 7:
	case 8:
		randNum1 = randXWA();
		sprintf(*mainStringBuffer, "wave\\frontend\\T01PA1%d.wav", randNum1 % 3 + 1);
		break;
	case 9:
	case 10:
		if (!*campaignIncomplete)
			goto Copy_Independence_PA;
		briefingLogo = QuickMissionDataPtr->header.BriefingLogo;
		if (briefingLogo == BriefingLogo_Liberty2)
		{
			memcpy(*mainStringBuffer, "wave\\frontend\\T01PA14.wav", 0x1Au);
		}
		else if (briefingLogo == BriefingLogo_Independence2)
		{
		Copy_Independence_PA:
			memcpy(*mainStringBuffer, "wave\\frontend\\T01PA15.wav", 0x1Au);
		}
		else
		{
		Copy_Announcement_1Through9:
			randNum2 = randXWA();
			sprintf(*mainStringBuffer, "wave\\frontend\\T01PA0%d.wav", randNum2 % 6 + 3);
		}
		break;
	case 11:
	case 12:
	case 13:
	case 14:
		randNum3 = randXWA();
		randModified = ((randNum3 >> 31) ^ abs(randNum3) & 3) - (randNum3 >> 31) + 16;
		goto Copy_Almost_Any_Announcement;
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
		randNum4 = randXWA();
		randModified = ((randNum4 >> 31) ^ abs(randNum4) & 7) - (randNum4 >> 31) + 28;
	Copy_Almost_Any_Announcement:
		// Copy almost any announcement to the string buffer.
		sprintf(*mainStringBuffer, "wave\\frontend\\T01PA%d.wav", randModified);
		break;
	case 23:
		sprintf(*mainStringBuffer, "wave\\frontend\\T01PA37.wav");
		break;
	default:
		*(*mainStringBuffer) = 0;
		break;
	}

	params[-1] = 0x53B06C;

	return 0;
}