#include "TribePCH.h"
#include "Achievements.h"

Achievements::Achievements() :
    m_iAppID(0),
    m_bInitialized(false),
    m_CallbackAchievementStored(this, &Achievements::OnAchievementStored)
{
    m_iAppID = SteamUtils()->GetAppID();
    RequestStats();
}

Achievements::~Achievements()
{
}

bool Achievements::RequestStats()
{
	// Is Steam loaded? If not we can't get stats.
	if (NULL == SteamUserStats() || NULL == SteamUser())
	{
		return false;
	}
	// Is the user logged on?  If not we can't get stats.
	if (!SteamUser()->BLoggedOn())
	{
		return false;
	}
	// Request user stats.
	return SteamUserStats()->RequestCurrentStats();
}

bool Achievements::SetAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_bInitialized)
	{
		SteamUserStats()->SetAchievement(ID);
		return SteamUserStats()->StoreStats();
	}
	// If not then we can't set achievements yet
	return false;
}

void Achievements::AddAchievements(Achievement_t* Achievements, int NumAchievements)
{
	m_pAchievements = Achievements;
	m_iNumAchievements = NumAchievements;	
}

void Achievements::OnAchievementStored(UserAchievementStored_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == pCallback->m_nGameID)
	{
		OutputDebugString(LPCWSTR("Stored Achievement for Steam\n"));
	}
}