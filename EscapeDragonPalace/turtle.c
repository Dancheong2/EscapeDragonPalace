#include "init.h"
#include "turtle.h"
#include "map.h"
#include "Rabbit.h"

Turtle g_Turtle;

static TurtleState g_State;

static unsigned int g_NextRushTime, g_PrepStartTime, g_RushEndTime; // ���� ����,�غ�,����
static bool g_ShowPrep;    // ���� �غ� �޽��� ȭ����� ����
static int g_RushCount;    // ���� 3�� ī��Ʈ
static int g_RushDir;      // ���� ����
static int g_InitialDir;   // �� ó�� ���� ���� ��->�� ù ���� ���� �� �ڶ� ���ʿ� ������ ��->��
static int g_LastRandIdx;  // ���� �ߺ����� ������

static bool g_ShowTarget = false;            //�̸����� ǥ�� ����
static unsigned int g_TargetPreviewEnd = 0;  //�̸����� ���� 
static int g_PendingTargetY = 0; // ������ ���� Y ��ǥ (�̸������)

int g_TargetFirstY = TURTLE_IDLE_Y + 1;             // �ٸ� ���ֱ⶧���� Y��ǥ +1
int g_TargetOptions[] = { 3, 11, 19 };               // �ڶ� �����Ҷ� ���� ��ǥ
int g_StartX[2] = { -TURTLE_WIDTH, SCREEN_WIDTH };  // ���� X ��ǥ ( ������ , ���� ) 

static bool g_WaterActive = false;           // ����� Ȱ�� ��Ȱ��
static unsigned int g_NextWaveStartTime = 0; // ���� ����� ����
static bool g_WaveActive = false;            // ����� ���������� Ȯ��
static unsigned int g_WaveEndTime = 0;       // ���� ����� ����
static unsigned int g_NextDropSpawnTime = 0; // ����� ���� ���� ����� ���� �ð�
static char g_WaterChar = '@';

static bool g_WaveWarnActive = false;         // ����� ���� 2�� �� ��� Ȱ������
static unsigned int g_WaveWarnStart = 0;      // ��� ���� �ð�
static unsigned int g_WaveWarnDelayUntil = 0; // ��� ������ �ð�

// ������� ��� �ٴڿ� ���� ������ ��ų ��� ����
static bool g_WaveDropsBlocking = false;
static bool g_HitWaveDrops = false; // ����￡ �¾Ҵ��� ����

// === ��Ÿ ���� ǥ�� ���� (����ڰ� ���� ������ �� �ֵ��� ���� ������ �и�) ===
static const int g_AttackPower = 2;        // ��Ÿ ���ݷ�
static const int g_AttackHalf = 10;        // ���� ����
static const int g_AttackHeight = 4;		// ��Ÿ ����
static const int g_AttackCenterRight = 22;  // ������ ���� �߽� X (���� ��ǥ)
static const int g_AttackCenterLeft = 58;   // ���� ���� �߽� X (���� ��ǥ)
// ���� ǥ�� Y ��ġ
static const int g_AttackRangeOffesetY= 5;

static WaterDrop g_WaterDrops[MAX_WATER_DROPS];

// �ڶ� ü�� ��ȯ
int GetTurtleHp() {
	return g_Turtle.mon.hp;
}

// �ڶ� ü�� �ʱ�ȭ
int ResetTurtleHp() {
	g_Turtle.mon.hp = 80;
}

// �ڶ� ������ �ʱ�ȭ
static void ClearWaterDrops(void) {
	for (int i = 0; i < MAX_WATER_DROPS; ++i) {
		g_WaterDrops[i].active = false;
		g_WaterDrops[i].lastMoveTime = 0;
		g_WaterDrops[i].pos.x = 0;
		g_WaterDrops[i].pos.y = 0;
	}
}

// ������ ����
static void SpawnWaterDropAt(unsigned int now) {
	for (int i = 0; i < MAX_WATER_DROPS; ++i) {
		if (!g_WaterDrops[i].active) {
			g_WaterDrops[i].active = true;
			// ȭ�� ������ ���� X�� ����
			g_WaterDrops[i].pos.x = randRange(0, SCREEN_WIDTH - 1);
			g_WaterDrops[i].pos.y = 0;
			g_WaterDrops[i].lastMoveTime = now;
			break;
		}
	}
}

// ������ ������Ʈ
static void UpdateWaterDrops(unsigned int now) {
	for (int i = 0; i < MAX_WATER_DROPS; ++i) {
		if (!g_WaterDrops[i].active) continue;

		// �̵� �ֱ⿡ ���� �� ĭ�� �Ʒ��� �̵�
		if (now - g_WaterDrops[i].lastMoveTime >= WATER_DROP_MOVE_MS) {
			g_WaterDrops[i].pos.y += 1;
			g_WaterDrops[i].lastMoveTime = now;
			// ȭ�� �Ʒ��� ����� ���� (�ٴڿ� �������� ����)
			if (g_WaterDrops[i].pos.y > SCREEN_HEIGHT + 5) g_WaterDrops[i].active = false;
		}

		// �÷��̾ ����￡ �¾Ҵ��� üũ
		if (g_WaterDrops[i].pos.y >= player.Pos.y && g_WaterDrops[i].pos.y <= player.Pos.y + RabbitY)
		{
			if (g_WaterDrops[i].pos.x >= (player.Pos.x + 7) && g_WaterDrops[i].pos.x <= (player.Pos.x + 12))
			{
				player.Health -= 1;	// �÷��̾� ü�� ����
				g_WaterDrops[i].active = false; // ����� ����
				g_HitWaveDrops = true; // ����� ���� ���� Ȱ��
			}
		}
		else
		{
			g_HitWaveDrops = false; // ����� ���� ���� �ʱ�ȭ
		}
	}
}

// Ȱ��ȭ�� ������� �ϳ��� �ִ��� üũ
static bool AnyWaterDropsActive(void) {
	for (int i = 0; i < MAX_WATER_DROPS; ++i) {
		if (g_WaterDrops[i].active) return true;
	}
	return false;
}

// ������ �׸���
static void DrawWaterDrops(void) {
	char s[2] = { g_WaterChar, '\0' };

	// ������� �Ķ������� �׸���
	_SetColor(E_Blue);
	for (int i = 0; i < MAX_WATER_DROPS; ++i) {
		if (!g_WaterDrops[i].active) continue;
		int dropX = g_WaterDrops[i].pos.x;
		int dropY = g_WaterDrops[i].pos.y;

		if (g_Turtle.mon.alive) {
			int tLeft = g_Turtle.pos.x;
			int tTop = g_Turtle.pos.y;
			int tLines = (g_State == TURTLE_STATE_RUSHING ? TURTLE_HEIGHT - 1 : TURTLE_HEIGHT);
			int tRight = tLeft + TURTLE_WIDTH - 1;
			int tBottom = tTop + tLines - 1;
			if (dropX >= tLeft && dropX <= tRight && dropY >= tTop && dropY <= tBottom) {
				// �ڶ� ������ �ִ� ������� ǥ������ ���� (�ð��� �浹 ȸ��)
				continue;
			}
		}

		_DrawText(dropX, dropY, s);
	}
	//�ڶ� ����� ������ ���� ���ϴ� ������� �ʱ�ȭ
	_SetColor(E_White);
}

// ���� ���� ��ȯ (min..max)
static unsigned int randRange(unsigned min, unsigned max) { return min + rand() % (max - min + 1); }

int g_NormalJumpY = 4;            // ���� ���� (y ����)

// �ܰ� ��: �ö� �� / ������ �� (���� >=1)
int g_TurtleAscentSteps = 2;      // base -> mid -> peak
int g_TurtleDescentSteps = 2;     // peak -> mid -> base

// �ö󰥶� / �������� ������ (ms)
unsigned int g_TurtleAscentFrameMs = 100;
unsigned int g_TurtleDescentFrameMs = 10;

// ���� ������ ���ߴ� �ð�(ms).
unsigned int g_TurtlePeakHoldMs = 1000;

static bool g_ExclaimActive = false;        // ! Ȱ��ȭ ����
static unsigned int g_ExclaimStart = 0;     // !�� ���� �ð�
static unsigned int g_LastExclaimBlink = 0; // ������ ������ �ð�
static bool g_ExclaimVisible = false;       // ���� ! ������ ����

// ��Ÿ ���� ���� ������
static bool g_JumpActive = false;
static unsigned int g_JumpStartTime = 0;
static unsigned int g_LastJumpFrameTime = 0;
static int g_JumpPhase = 0;
static int g_JumpBaseY = TURTLE_IDLE_Y;

static unsigned int g_LastAttackTime = 0; // ������ ��Ÿ ���� �ð� (��ٿ� üũ)

static unsigned int g_PeakHoldUntil = 0;

static unsigned int g_SkillLockUntil = 0;       // �� �ð� �������� ���� ��� ����
static const unsigned int g_SkillLockMs = 1000; // 1�� ��

extern Rect GetPlayerRect(void);

void SetTurtleJumpY(int y) {
	if (y < 0) y = 0;
	g_NormalJumpY = y;
}
void SetTurtleAscentSteps(int steps) {
	if (steps < 1) steps = 1;
	g_TurtleAscentSteps = steps;
}
void SetTurtleDescentSteps(int steps) {
	if (steps < 1) steps = 1;
	g_TurtleDescentSteps = steps;
}
void SetTurtleAscentFrameMs(unsigned int ms) {
	if (ms < 10) ms = 10;
	g_TurtleAscentFrameMs = ms;
}
void SetTurtleDescentFrameMs(unsigned int ms) {
	if (ms < 10) ms = 10;
	g_TurtleDescentFrameMs = ms;
}
void SetTurtlePeakHoldMs(unsigned int ms) {
	g_TurtlePeakHoldMs = ms;
}

void InitTurtle(unsigned int now) {
	srand((unsigned)time(NULL));
	g_Turtle.pos.x = 58;
	g_Turtle.pos.y = TURTLE_IDLE_Y;
	g_Turtle.speed = 1.0f;
	g_Turtle.dir = E_Left;
	g_Turtle.mon.hp = TURTLE_HP;
	g_Turtle.attack = 2;
	g_Turtle.mon.alive = true;
	g_Turtle.isDamaged = false;
	g_Turtle.mon.lastHitTime = now;
	g_State = TURTLE_STATE_IDLE;
	g_NextRushTime = now + randRange(10000, 15000);
	g_PrepStartTime = g_NextRushTime - 2000;
	g_ShowPrep = false;
	g_RushCount = 0;
	g_InitialDir = -1;
	g_RushDir = g_InitialDir;
	g_LastRandIdx = -1;

	g_ShowTarget = false;
	g_TargetPreviewEnd = 0;
	g_PendingTargetY = 0;

	// ����� �ý��� �ʱ�ȭ
	g_WaterActive = true;
	ClearWaterDrops();
	// ����� ���� �ð�: 8~12�� ���� ��Ÿ�� �� ù ����� ����
	g_WaveActive = false;
	g_NextWaveStartTime = now + randRange(WATER_WAVE_COOLDOWN_MIN_MS, WATER_WAVE_COOLDOWN_MAX_MS);
	g_WaveEndTime = 0;
	g_NextDropSpawnTime = 0;

	// ����� ��� �ʱ�ȭ
	g_WaveWarnActive = false;
	g_WaveWarnStart = 0;
	g_WaveWarnDelayUntil = 0;
	g_WaveDropsBlocking = false;

	// ��Ÿ �ʱ� ����
	g_ExclaimActive = false;
	g_ExclaimVisible = false;
	g_JumpActive = false;
	g_JumpPhase = 0;
	g_JumpBaseY = TURTLE_IDLE_Y;
	g_LastAttackTime = now; // �ʱ⿡�� ��Ÿ�� �˻� ���� �ð�
	g_PeakHoldUntil = 0;

	// ��ų �� �ʱ�ȭ
	g_SkillLockUntil = now;
}

//�÷��̾� ��ó ����
static bool IsPlayerNear(void) {
	Rect pr = GetPlayerRect();
	int playerLeft = pr.x;
	int playerRight = pr.x + pr.w - 1;

	// �ڶ��� �Ӹ� ȭ�� X ��ǥ ���
	int turtleScreenX = g_Turtle.pos.x;
	int headOffset = (g_Turtle.dir != E_Right) ? E_Left : TURTLE_WIDTH - 3; // dir==0: ������ �ٶ� dir!=0 : ���� �ٶ�
	int headScreenX = turtleScreenX + headOffset;

	if (player.Pos.y < g_Turtle.pos.y) return false;	// Y��ǥ�� ���
	if (playerRight < headScreenX - TURTLE_ATTACK_RANGE) return false;
	if (playerLeft > headScreenX + TURTLE_ATTACK_RANGE) return false;
	return true;
}

// ��Ÿ �ö󰡴°� �� �������°�
static int ComputeJumpYForPhase(int phase, int baseY) {
	int ascent = g_TurtleAscentSteps;
	int descent = g_TurtleDescentSteps;
	if (ascent < 1) ascent = 1;
	if (descent < 1) descent = 1;
	int total = ascent + descent;
	if (phase < 1) phase = 1;
	if (phase > total) phase = total;
	int jumpY = g_NormalJumpY;
	int peakY = baseY - jumpY;

	if (phase <= ascent) {
		int k = phase;
		int yOffset = (jumpY * k + (ascent / 2)) / ascent;
		return baseY - yOffset;
	}
	else {
		int d = phase - ascent;
		int yOffset = (jumpY * d + (descent / 2)) / descent;
		return peakY + yOffset;
	}
}

// �ڶ� ������Ʈ
void UpdateTurtle(unsigned long now) {
	if (!g_Turtle.mon.alive) return;
	if (g_Turtle.isDamaged && now - g_Turtle.mon.lastHitTime >= 1000)
		g_Turtle.isDamaged = false;


	// ���� �����ϴ� ��� ��Ÿ/���̺� �浹 ������
	const unsigned int PREP_MARGIN_MS = 50;
	bool prepImminent = (g_PrepStartTime <= now + PREP_MARGIN_MS);

	// ��ų �� Ȯ��: ������� �� ����� ������ ��ų ����
	bool skillLocked = (now < g_SkillLockUntil) || g_WaveDropsBlocking;

	// ���� �ڶ��� ��
	if (g_State == TURTLE_STATE_IDLE) {
		// ��Ÿ
		if (!g_ExclaimActive && !g_JumpActive) {
			// ��Ÿ ���� ����:
			// - ���� �ӹ�/���� �� ����
			// - ��ų �� ���� (��, ��� �߸� ��Ÿ�� ������Ŵ)
			// (����� ���̺갡 �־ ��Ÿ ���� �����ϰ� ����)
			if (!prepImminent && !skillLocked && IsPlayerNear() && (now - g_LastAttackTime >= TURTLE_ATTACK_COOLDOWN_MS)) {
				if (g_WaveWarnActive && now < g_WaveWarnDelayUntil) {
					g_ExclaimActive = true;
					g_ExclaimStart = g_WaveWarnDelayUntil; // ��� ���� �� 1�� ���� �غ� ����
					g_LastExclaimBlink = g_ExclaimStart;
					g_ExclaimVisible = true;
				}
				else {
					g_ExclaimActive = true;
					g_ExclaimStart = now;
					g_LastExclaimBlink = now;
					g_ExclaimVisible = true;
				}

				if (g_PrepStartTime <= g_ExclaimStart + 500) {
					g_PrepStartTime = g_ExclaimStart + 500;
				}
			}
		}

		if (g_ExclaimActive) {  // ����ǥ Ȱ��ȭ ����
			if (now >= g_ExclaimStart) {
				// ����ǥ Ȱ��ȭ �ð� ���Ŀ��� �����̰� ��
				if (now - g_LastExclaimBlink >= 300) {
					g_ExclaimVisible = !g_ExclaimVisible;
					g_LastExclaimBlink = now;
				}
				if (now - g_ExclaimStart >= 2000) {
					g_ExclaimActive = false;
					g_ExclaimVisible = false;

					// ���� ����
					g_JumpActive = true;
					g_JumpStartTime = now;
					g_LastJumpFrameTime = now;
					g_JumpPhase = 0;
					g_JumpBaseY = g_Turtle.pos.y;
					g_PeakHoldUntil = 0;
				}
			}
			else {
				// ��� ������ ����
				g_ExclaimVisible = false;
			}
		}
	}

	// �����
	if (g_WaterActive) {
		if (!g_WaveActive) {
			// ����� ���� �������� üũ
			if (now >= g_NextWaveStartTime) {
				// ���� �غ�/���� ���¿����� ���� ����
				if (g_State != TURTLE_STATE_PREPARE_RUSH && g_State != TURTLE_STATE_RUSHING && !skillLocked) {
					// ����
					g_WaveActive = true;
					g_WaveEndTime = now + randRange(WATER_WAVE_DURATION_MIN_MS, WATER_WAVE_DURATION_MAX_MS);
					g_NextDropSpawnTime = now;
					// ��� ����
					g_WaveWarnActive = false;
					g_WaveWarnDelayUntil = 0;
					// ����� ������ Ȱ��ȭ
					g_WaveDropsBlocking = false;
				}
				else {
					g_NextWaveStartTime = now + 500;
				}
			}
			else {
				// 2�� �� ��� üũ
				if (!g_WaveWarnActive) {
					// ��� �� ���� ���� ���� ���°� �ƴϰ� ��ų���� �ƴϾ�� ��
					if (g_State != TURTLE_STATE_PREPARE_RUSH && g_State != TURTLE_STATE_RUSHING && !skillLocked
						&& g_NextWaveStartTime > now && (g_NextWaveStartTime - now) <= 2000) {
						g_WaveWarnActive = true;
						g_WaveWarnStart = now;
						g_WaveWarnDelayUntil = now + 1000;
					}
				}
				else {
					// ���� �ڶ� ���� ���� ���°� �ǰų� ��ų���̸� ��� ���
					if (g_State == TURTLE_STATE_PREPARE_RUSH || g_State == TURTLE_STATE_RUSHING || skillLocked) {
						g_WaveWarnActive = false;
						g_WaveWarnDelayUntil = 0;
					}
				}
			}
		}
		else {
			// ���� ���ݿ� ���� ����� ����
			if (now >= g_NextDropSpawnTime) {
				SpawnWaterDropAt(now);
				// ���� ���� �ð��� 500~700ms ����
				g_NextDropSpawnTime = now + randRange(WATER_DROP_INTERVAL_MIN_MS, WATER_DROP_INTERVAL_MAX_MS);
			}
			// ���̺� ���� üũ
			if (now >= g_WaveEndTime) {
				// ������� ��Ȱ��ȭ������ ȭ�鿡 ���� ������� ��� ����� ������
				// �ٸ� ��ų�� �� ������ �ϱ�
				g_WaveActive = false;
				g_WaveWarnActive = false;
				g_WaveWarnDelayUntil = 0;
				if (AnyWaterDropsActive()) 
				{
					g_WaveDropsBlocking = true;
				}
				else 
				{
					if (g_SkillLockUntil < now + g_SkillLockMs) g_SkillLockUntil = now + g_SkillLockMs;
					g_WaveDropsBlocking = false;
				}
				// ���� ����� ���� �ð�: 8~12�� ���� ��Ÿ��
				g_NextWaveStartTime = now + randRange(WATER_WAVE_COOLDOWN_MIN_MS, WATER_WAVE_COOLDOWN_MAX_MS);
			}
		}
	}

	// ����� �̵� ó�� (�׻� ����)
	UpdateWaterDrops(now);

	// ���� ��� ������� �ٴڿ� �������� ���� & �ұԸ� �� ����
	if (g_WaveDropsBlocking) {
		if (!AnyWaterDropsActive()) {
			g_WaveDropsBlocking = false;
			if (g_SkillLockUntil < now + g_SkillLockMs) g_SkillLockUntil = now + g_SkillLockMs;
		}
	}

	// ��Ÿ ���� ó��
	if (g_JumpActive) {
		int ascent = (g_TurtleAscentSteps >= 1 ? g_TurtleAscentSteps : 1);
		int descent = (g_TurtleDescentSteps >= 1 ? g_TurtleDescentSteps : 1);
		int total = ascent + descent;

		if (g_JumpPhase == ascent && g_PeakHoldUntil != 0 && now < g_PeakHoldUntil) {
		}
		else {
			int nextPhase = g_JumpPhase + 1;
			unsigned int curFrameMs;
			if (nextPhase <= ascent) curFrameMs = g_TurtleAscentFrameMs;
			else curFrameMs = g_TurtleDescentFrameMs;

			if (now - g_LastJumpFrameTime >= curFrameMs) {
				g_LastJumpFrameTime = now;
				g_JumpPhase++;

				if (g_JumpPhase > total) {
					g_JumpActive = false;
					g_JumpPhase = 0;
					g_Turtle.pos.y = g_JumpBaseY;
					g_LastAttackTime = now; // ��Ÿ ������ �� ��ٿ� ����
					g_PeakHoldUntil = 0;
					if (g_SkillLockUntil < now + g_SkillLockMs) g_SkillLockUntil = now + g_SkillLockMs;
				}
				else {
					int newY = ComputeJumpYForPhase(g_JumpPhase, g_JumpBaseY);
					g_Turtle.pos.y = newY;

					if (g_JumpPhase == ascent && g_TurtlePeakHoldMs > 0) {
						g_PeakHoldUntil = now + g_TurtlePeakHoldMs;
					}
				}
			}
		}

		g_State = TURTLE_STATE_ATTACK; // ��Ÿ ���·� ����
	}

	// ��Ÿ �� ���� ��
	if (g_State == TURTLE_STATE_ATTACK && !g_JumpActive) {
		// �÷��̾�� ��Ÿ ���� �浹 üũ �� ������ ����
		int centerWorld = (g_Turtle.dir == E_Right) ? 0 : g_AttackCenterLeft - g_AttackHalf;
		Rect attackArea = { centerWorld, g_Turtle.pos.y, g_AttackHalf + TURTLE_WIDTH, TURTLE_HEIGHT };

		if (IsOverlap(GetPlayerRect(), attackArea)) {
			// �÷��̾ ��Ÿ ������ ���� ��
			player.Health -= g_AttackPower;// �÷��̾� ü�� ����
		}

		g_State = TURTLE_STATE_IDLE; // ��Ÿ ���¿��� �ٽ� ���÷� ���ư�
	}

	// ����
	switch (g_State) {
	case TURTLE_STATE_IDLE: // ������ ���
		// ���� �غ� ���� ����:
		// ����� ��Ȱ��
		// ��� ��Ȱ��
		// ��Ÿ ��Ȱ��
		// ��ų�� ����
		if (now >= g_PrepStartTime && !g_WaveActive && !g_WaveWarnActive && !g_ExclaimActive && !g_JumpActive && !skillLocked) {
			// ���� �غ�� �Ѿ ��: ��Ÿ/���/����� ���� �ʱ�ȭ (��ħ ����)
			g_ExclaimActive = false;
			g_ExclaimVisible = false;
			g_JumpActive = false;
			g_PeakHoldUntil = 0;
			g_WaveWarnActive = false;
			g_WaveWarnDelayUntil = 0;

			g_State = TURTLE_STATE_PREPARE_RUSH;
			g_PrepStartTime = now;
			g_ShowPrep = true;
		}
		break;
	case TURTLE_STATE_PREPARE_RUSH: // ���� �غ� ���� ���
		if (now - g_PrepStartTime >= 2000) {
			// ���� �غ� -> ������ ��ȯ �ÿ��� ��Ÿ/����ǥ/��� �ʱ�ȭ
			g_ExclaimActive = false;
			g_ExclaimVisible = false;
			g_JumpActive = false;
			g_PeakHoldUntil = 0;
			g_WaveWarnActive = false;
			g_WaveWarnDelayUntil = 0;

			g_State = TURTLE_STATE_RUSHING;
			g_ShowPrep = false;
			g_RushCount = 0;
			g_RushDir = g_InitialDir;
			g_Turtle.dir = (g_RushDir < E_Right ? E_Left : E_Right);
			g_Turtle.pos.y = g_TargetFirstY;
			g_Turtle.pos.x = (g_RushDir < E_Right ? g_StartX[E_Left] - 20 : g_StartX[E_Right] + 20);
			g_RushEndTime = now + 1000;
		}
		break;
	case TURTLE_STATE_RUSHING: {
		if (g_ShowTarget) {
			if (now < g_TargetPreviewEnd) {
				break;
			}
			else {
				g_ShowTarget = false;
				g_Turtle.pos.y = g_PendingTargetY;
				g_Turtle.pos.x = (g_RushDir < E_Right ? g_StartX[E_Left] - 20 : g_StartX[E_Right] + 20);
				g_RushEndTime = now + 900;
			}
		}

		int step = (int)(g_Turtle.speed * 3);
		g_Turtle.pos.x += (g_RushDir < E_Right ? -step : step);
		bool passed = (g_RushDir < E_Right)
			? (g_Turtle.pos.x + TURTLE_WIDTH < 0)
			: (g_Turtle.pos.x > SCREEN_WIDTH);
		if (passed && now >= g_RushEndTime) {
			g_RushCount++;
			if (g_RushCount < TURTLE_RUSH_COUNT) {
				g_RushDir = -g_RushDir;
				g_Turtle.dir = (g_RushDir < E_Right ? E_Left : E_Right);
				int opts = sizeof(g_TargetOptions) / sizeof(int);
				int idx;
				do { idx = randRange(0, opts - 1); } while (idx == g_LastRandIdx && opts > 1);
				g_LastRandIdx = idx;

				// ���� �� ���ǿ� ! ǥ��
				g_PendingTargetY = g_TargetOptions[idx];
				g_ShowTarget = true;
				g_TargetPreviewEnd = now + 1000; // 1�� �̸�����

			}
			else {
				if (g_SkillLockUntil < now + g_SkillLockMs) g_SkillLockUntil = now + g_SkillLockMs;

				// ���� ���� ���� ��Ÿ/����ǥ/���/���̺갡 �������� �ʵ��� Ȯ���� �ʱ�ȭ
				g_ExclaimActive = false;
				g_ExclaimVisible = false;
				g_JumpActive = false;
				g_PeakHoldUntil = 0;
				g_WaveWarnActive = false;
				g_WaveWarnDelayUntil = 0;
				g_WaveActive = false;

				g_State = TURTLE_STATE_IDLE;
				g_Turtle.pos.y = TURTLE_IDLE_Y;

				g_InitialDir = -g_InitialDir;

				if (g_InitialDir > E_Right) {
					g_Turtle.pos.x = g_StartX[E_Right] + 25;
					g_Turtle.dir = E_Right;
				}
				else {
					g_Turtle.pos.x = g_StartX[E_Left] - 22;
					g_Turtle.dir = E_Left;
				}

				g_NextRushTime = now + randRange(20000, 25000);
				g_PrepStartTime = g_NextRushTime - 2000;
			}
		}
		break;
	}
	}
}

void DrawTurtle(void) {
	if (!g_Turtle.mon.alive) return;

	// ����� �׸���
	if (g_WaterActive) DrawWaterDrops();

	// ����� ��� ǥ��
	if (g_WaveWarnActive) {
		const char* warn = "������� �������ϴ�!";
		int len = strlen(warn);
		_DrawText(SCREEN_WIDTH / 2 - len / 2, 5, warn);
	}

	// �ڶ� ���� ��ġ ǥ��
	if (g_ShowTarget) {
		int mx = SCREEN_WIDTH / 2 - 3;
		_DrawTextColor(mx + 3, g_PendingTargetY + 1, "!", E_BrightYellow);
	}

	// ����ǥ �����϶��� ���� ǥ��
	if (g_ExclaimActive && g_ExclaimVisible && !g_JumpActive) {
		int centerWorld = (g_Turtle.dir == E_Right) ? g_AttackCenterRight : g_AttackCenterLeft;
		int leftScreen = centerWorld - g_AttackHalf;
		int rightScreen = centerWorld + g_AttackHalf;

		if (leftScreen < 0) leftScreen = 0;
		if (rightScreen >= SCREEN_WIDTH) rightScreen = SCREEN_WIDTH - 1;
		if (rightScreen < leftScreen) rightScreen = leftScreen;

		int rangeY = g_Turtle.pos.y + g_AttackRangeOffesetY;
		if (rangeY < 0) rangeY = 0;
		if (rangeY >= SCREEN_HEIGHT) rangeY = g_Turtle.pos.y;

		char sRange[2] = { '-', '\0' };
		for (int sx = leftScreen; sx <= rightScreen; ++sx) {
			_DrawTextColor(sx, rangeY, sRange, E_BrightYellow);
		}
 		_DrawTextColor(leftScreen, rangeY, "[", E_BrightYellow);
		_DrawTextColor(rightScreen, rangeY, "]", E_BrightYellow);
	}

	// ��Ÿ �غ� ( ! )
	if (g_State == TURTLE_STATE_IDLE && g_ExclaimActive && g_ExclaimVisible) {
		int exX = (g_Turtle.pos.x) + (TURTLE_WIDTH / 2);
		int exY = g_Turtle.pos.y - 1;
		_DrawTextColor(exX, exY, "!", E_BrightWhite);
	}

	// ���� �߿� �ڶ� ȭ�� ������ ������ ������ �׸��� ����
	if (g_State == TURTLE_STATE_RUSHING &&
		(g_Turtle.pos.x < 5 || g_Turtle.pos.x + TURTLE_WIDTH > 75)) return;


	int posX = g_Turtle.pos.x;
	if (g_State == TURTLE_STATE_PREPARE_RUSH) {
		const char* m = "�ڶ� ������ �غ����Դϴ�!";
		int l = strlen(m);
		_DrawText(SCREEN_WIDTH / 2 - l / 2, 5, m);
	}

	int idx = (g_Turtle.dir == E_Right ? E_Right : E_Left);
	int height = (g_State == TURTLE_STATE_RUSHING ? TURTLE_HEIGHT - 1 : TURTLE_HEIGHT);

	// �ǰ� �����̰� �����ð�(1��) �̳��� ������
	_SetColor(g_Turtle.isDamaged ? E_Red : E_White);

	// �ڶ� ��� ���
	for (int y = 0; y < height; ++y) 
	{
		int line = strlen(g_TurtleGraphic[g_Turtle.dir][y]);
		for (int x = 0; x < line; x++)
		{
			// �׸����� ���ڰ� ������ ��� �ǳʶٱ�
			if (g_TurtleGraphic[g_Turtle.dir][y][x] == ' ' &&
				(x <= 3 || x >= line - 3)) continue;
			{
				_DrawText(posX + x, g_Turtle.pos.y + y, (char[]) { g_TurtleGraphic[idx][y][x], 0 });
			}
		}

	}

	TurtleHitP(g_Turtle.pos.x, g_Turtle.pos.y); //���⼭ �ź��� ��ǥ�� �޾ƿ�

	// �ڶ� ���� ü�� �׸���
	_DrawTextColor(38, 2, "�ڶ�", E_BrightWhite);
	for (int i = 0; i < (int)(TURTLE_HP * 0.5); i++)
	{
		if (i <= (int)(g_Turtle.mon.hp * 0.5))
			_DrawTextColor(i + 20, 3, "|", E_BrightRed);
		else
			_DrawTextColor(i + 20, 3, "|", E_Gray);
	}
}

// �ڶ� -> �÷��̾� �ǰ�
void TurtleHitP(int posX, int posY) { //������ 1�� ����
	Rect PlayerPos = GetPlayerRect();
	Rect MosterPos = { posX + 4, posY, TURTLE_WIDTH - 10, TURTLE_HEIGHT - 1 };
	// - 1: �ڶ� ���� �� �䳢 �Ͱ� �ڶ� ��� ������ ���� �ʵ��� ó��
	DWORD now = GetTickCount();

	if ((IsOverlap(PlayerPos, MosterPos)) == false)
		return;

	// ���� �ð� üũ
	if (now - player.lastHitTime < INVINCIBLE_TIME) {
		return; // ���� ���� ���¸� ������ ����
	}

	// �ڶ� ���� ���� ��
	if (g_State == TURTLE_STATE_RUSHING)
	{
		// 4ĭ ����
		player.Health -= 4; // �÷��̾� ü�� ����
	}
	else
	{
		player.Health -= 1;
	}

	// �ڶ� ����� ����߸� ��
	if (g_State == TURTLE_STATE_IDLE && g_WaterActive)
	{
		// �÷��̾ ������� �¾��� ���
		if (AnyWaterDropsActive() && g_HitWaveDrops) {
			g_HitWaveDrops = false; // ����� �¾����� false�� �ʱ�ȭ
			--player.Health; // �÷��̾� ü�� ����
		}
	}

	player.lastHitTime = now; // ������ �ǰ� �ð� ����
}

// �÷��̾� -> �ڶ� �ǰ�
void PlayerHitTurtle()
{
	DWORD now = GetTickCount();
	Rect PlayerWeaponPos = GetWeaponRect();

	int posX = g_Turtle.pos.x;
	int posY = g_Turtle.pos.y;
	Rect MosterPos = { posX, posY, TURTLE_WIDTH, TURTLE_HEIGHT + 2 };

	if (!player.IsAttacking) return;

	if (g_Turtle.isDamaged) return; // ���Ͱ� ���� ������ ��� �Ѿ��

	if (!(IsOverlap(PlayerWeaponPos, MosterPos))) return;

	if (now - g_Turtle.mon.lastHitTime < MONSTER_INVINCIBLE_TIME) return;
 	g_Turtle.mon.hp -= player.HeldWeapon->attack; // ����� ü�� ����
	g_Turtle.isDamaged = true; // ���� ���·� ����
	g_Turtle.mon.lastHitTime = now; // ������ �ǰ� �ð� ����

	if (g_Turtle.mon.hp <= 0) {
		g_Turtle.mon.alive = false;
	}
}