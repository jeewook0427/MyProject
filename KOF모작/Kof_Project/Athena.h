#pragma once
#include "GameNode.h"


class Image;
class Athena : public GameNode
{
	float posX;
	float posY;
	float skillposX;
	float skillposY;
	float skillpos2X;
	float skillpos2Y;
	float theta[2];
	FPOINT effectpos;

	int width;
	int height;
	int maxFrameX;
	int maxFrameY;

	int currentframex, currentframey;
	int actionframex, actionframey;
	int effectframex, effectframey;
	int skillframex, skillframey;
	int skillframe2x, skillframe2y;
	int hitframex, hitframey;

	int hittime;
	int comtime;
	int actiontime;
	int commandtime;
	int skilltime;
	int effecttime;
	int damage;
	int insdamage;
	int playerNum;

	float speed;
	float skillspeed;

	float scale;
	bool goFoward, goBackward;
	bool rightPunch, leftKick;
	bool isAction;
	bool isReverse;
	bool isHit;
	bool isDead;
	bool isWin;
	bool gameStart;
	bool gameOver;
	bool keyDownCheck;
	bool keyFowardCheck;
	bool keyBackCheck;
	bool commandA;
	bool commandB;
	bool skillA;
	bool isSkill;
	bool isEffect;
	bool isLaunch;
	bool launchSkillA;
	bool SkillOnHit;
	bool skilldirect;
	bool isGuard;
	bool isGuarded;
	bool isSkillIsHit;
	bool skillB;
	bool launchSkillB;
	bool roll;
	bool direction;
	bool sitDown;

	Image* img;
	Image* profile;
	Image* midBackBuffer;
	Image* skillBackBuffer;
	Image* skillBackBuffer2;
	Image* effectBackBuffer;
	Image* skillBackBuffer3;
	Image* superskillimg;

	MCI_OPEN_PARMS mciOpenParam_StartMostion;
	MCI_OPEN_PARMS mciOpenParam_Win;
	MCI_OPEN_PARMS mciOpenParam_Die;

	MCI_PLAY_PARMS mciPlayParam_StartMostion;
	MCI_PLAY_PARMS mciPlayParam_Win;
	MCI_PLAY_PARMS mciPlayParam_Die;

	DWORD wDeviceID_StartMostion;
	DWORD wDeviceID_Win;
	DWORD wDeviceID_Die;


	struct HitBox
	{
		FPOINT attackPos;
		FPOINT bodyPos;
		FPOINT armPos;
		FPOINT legPos;
		FPOINT skillAPos;
		FPOINT guardPos;

		int guardWidth, guardHeight;
		int attackWidth, attackHeight;
		int skillAWidth, skillAHeight;
		int bodyWidth, bodyHeight;
		int rightpunchWidth, rightpunchHeight;
		int leftkickWidth, leftkickHeight;
		int legWidth, legHeight;

	};

	struct Key
	{
		int rightPunch;
		int leftKick;
		int goRight;
		int goLeft;
		int sitDown;
	};

	enum STATE
	{
		STATE_STANDING,
		STATE_GOFOWARD,
		STATE_GOBACKWARD,
		STATE_RIGHTPUNCH,
		STATE_LEFTKICK,
		STATE_HIT,
		STATE_DEAD,
		STATE_MOTION
	};


	Key key;
	HitBox hitbox;

public:

	virtual HRESULT Init();	 // 문법적으로 잘못되었을 때 예외처리를 위해 필요
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void InputKey();
	virtual bool CheckAction();
	virtual void ActionUpdate();
	virtual void MakeHitbox();
	virtual void HitBoxInit();

	void KeyInit();
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }
	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }
	void SetScale(float _scale) { scale = _scale; }
	void SetDamage(int _damage) { damage = _damage; }
	void SetIsReverse(bool _reverse) { isReverse = _reverse; }
	int GetDamage() { return damage; }
	void SetInsDamage(int _damage) { insdamage = _damage; }
	int GetInsDamage() { return insdamage; }
	void SetIsWin(bool iswin) { isWin = iswin; }
	void SetSkillOnHit(bool skillonhit) { SkillOnHit = skillonhit; }
	void MakeSkill();
	void SetIsGard(bool isgard) { isGuard = isgard; }
	void SetIsGarded(bool isgarded) { isGuarded = isgarded; }
	void SetIsSkillisHit(bool skillishit) { isSkillIsHit = skillishit; }
	void SetPlayerNum(int playernum) { playerNum = playernum; }
	int GetActionFrameX() { return actionframex; }
	void SetCurrentFrameX(int framex) { currentframex = framex; }
	bool CheckGameOver();
	void SetGameOver(bool gameover) { gameOver = gameover; }


	void SetIsHit(bool _ishit) { isHit = _ishit; }
	void MakeHitBoxPos(float bodyx1, float bodyy1, float bodyx2, float bodyy2, float legx1, float legy1, float legx2, float legy2);
	bool CheckCommand(bool &firstkey, bool &secondkey, bool commnad);
	bool MakeCommand(bool movecommand, bool actioncommnad);
	void CommandTimeCheck(bool &commnad);
	void CheckSkill(bool &firstkey, bool &secondky, bool &command, bool &actioncommand, bool&skillcommand);
	bool CheckIsLaunch();

	bool GetRightPunch() { return rightPunch; }
	bool GetLeftKick() { return leftKick; }
	bool GetIsHit() { return  isHit; }
	bool GetIsDead() { return isDead; }
	bool GetGameStart() { return gameStart; }
	bool GetLaunchSkillA() { return launchSkillA; }
	bool GetSkillOnHit() { return SkillOnHit; }
	bool GetLaunchSkillB() { return launchSkillB; }
	bool CheckIsSkill();

	HitBox GetHitBox() { return hitbox; }


	Athena();
	~Athena();
};

