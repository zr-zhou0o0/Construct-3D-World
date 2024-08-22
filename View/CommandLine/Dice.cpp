
/*************************************************************************
���ļ�����                 Dice.hpp
������ģ���Ŀ�ġ�         ���Ӷ�������
�������߼����ڡ�           ������֮���� 2022/7/16
�����ӡ�	   https ://www.zhihu.com/question/386347847/answer/2576561977
����Դ��				   ֪��
�����ļ�¼��               ��
*************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <windows.h> 
#include <thread>
#include <iostream>
#include <ctime>

#include "Dice.hpp"


/*************************************************************************
���������ơ�       Dice::Dice
���������ܡ�       ���캯������ʼ��Dice����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
Dice::Dice() {}

/*************************************************************************
���������ơ�       Dice::~Dice
���������ܡ�       ��������������Dice����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
Dice::~Dice() {}

/*************************************************************************
���������ơ�       Dice::StartDice
���������ܡ�       �������Ӷ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         bool - ����true��ʾ�����ɹ�
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
bool Dice::StartDice() {
	m_RunDice = true;
	m_DiceThread = std::thread([this]() { this->RenderFrame(); });
	return true;
}

/*************************************************************************
���������ơ�       Dice::StopDice
���������ܡ�       ֹͣ���Ӷ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         bool - ����true��ʾֹͣ�ɹ�
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
bool Dice::StopDice() {
	m_RunDice = false;
	if (m_DiceThread.joinable()) {
		m_DiceThread.join();
	}
	std::cout << "\033[" << SCREEN_HEIGHT + 1 << ";1H";
	return true;
}

/*************************************************************************
���������ơ�       Dice::RandomDice
���������ܡ�       ������Ӷ���
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         bool - ����true��ʾ�����ɹ�
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
bool Dice::RandomDice() {
	StartDice();
	srand(unsigned int(time(0)));
	int iDiceTime = 4000 + rand() % (5000);
	Sleep(iDiceTime); // millisecond
	StopDice();
	std::cout << "time:" << iDiceTime << std::endl;
	return true;
}

/*************************************************************************
���������ơ�       Dice::JudgeFace
���������ܡ�       �ж�������
����ڲ�����       int ID, double rX, double rY
�����ڲ�����       ��
������ֵ��         int - �����������Ӧ��ֵ
�������߼����ڡ�   ������֮���� 2022/7/16
�����ļ�¼��       ��
*************************************************************************/
int Dice::JudgeFace(int iID, double rX, double rY) {
	return FACE[iID][(int)(3.f * rY)][(int)(3.f * rX)];
}

/*************************************************************************
���������ơ�       Dice::Initialize
���������ܡ�       ��ʼ������������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ������֮���� 2022/7/16
�����ļ�¼��       ��
*************************************************************************/
void Dice::Initialize() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			double rX = m_Cube[i][j][0];
			double rY = m_Cube[i][j][1];
			double rZ = m_Cube[i][j][2];

			m_Cube[i][j][0] = (sqrt(3) / 6.f + 0.5) * rX 
				- sqrt(3) / 3.f * rY 
				+ (-0.5 + sqrt(3) / 6.f) * rZ;
			m_Cube[i][j][1] = (sqrt(3) / 3.f) * rX 
				+ (sqrt(3) / 3.f) * rY 
				+ (sqrt(3) / 3.f) * rZ;
			m_Cube[i][j][2] = (-0.5 + sqrt(3) / 6.f) * rX 
				+ (-sqrt(3) / 3.f) * rY 
				+ (sqrt(3) / 6.f + 0.5) * rZ;
		}
	}
}

/*************************************************************************
���������ơ�       Dice::PlatformSleep
���������ܡ�       ���ݲ���ϵͳѡ��˯�ߺ���
����ڲ�����       unsigned int milliseconds
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/14
�����ļ�¼��       ��
*************************************************************************/
void Dice::PlatformSleep(unsigned int milliseconds) {
#ifdef _WIN32
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}

/*************************************************************************
���������ơ�       Dice::RenderFrame
���������ܡ�       ��Ⱦ���Ӷ���֡
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ������֮���� 2022/7/16
�����ļ�¼��       ��
*************************************************************************/
void Dice::RenderFrame()
{
	Initialize();
	double rTime = 0;
	while (m_RunDice) {
		rTime = rTime + 0.01;
		double rZBuffer[SCREEN_HEIGHT + 1][SCREEN_WIDTH + 1];
		for (int i = 0; i <= SCREEN_HEIGHT; i++)
			for (int j = 0; j <= SCREEN_WIDTH; j++)
				rZBuffer[i][j] = -100;
		char cOutPut[SCREEN_HEIGHT + 1][SCREEN_WIDTH + 1];
		memset(cOutPut, ' ', sizeof(cOutPut));

		for (int i = 0; i < 6; i++)
		{
			for (double u = 0.f; u < 1.f; u = u + 0.01)
				for (double v = 0.f; v < 1.f; v = v + 0.01)
				{
					double rM_X = (m_Cube[i][1][0] - m_Cube[i][0][0]);
					double rM_Y = (m_Cube[i][1][1] - m_Cube[i][0][1]);
					double rM_Z = (m_Cube[i][1][2] - m_Cube[i][0][2]);
						   
					double rN_X = (m_Cube[i][2][0] - m_Cube[i][0][0]);
					double rN_Y = (m_Cube[i][2][1] - m_Cube[i][0][1]);
					double rN_Z = (m_Cube[i][2][2] - m_Cube[i][0][2]);


					double rX = rM_X * u + rN_X * v + m_Cube[i][0][0];
					double rY = rM_Y * u + rN_Y * v + m_Cube[i][0][1];
					double rZ = rM_Z * u + rN_Z * v + m_Cube[i][0][2];

					double rRotation_x = cos(rTime) * rX - sin(rTime) * rZ;
					double rRotation_y = rY;
					double rRotation_z = sin(rTime) * rX + cos(rTime) * rZ;

					double rNormal_x = (m_Cube[i][3][0]) * cos(rTime) 
						- sin(rTime) * (m_Cube[i][3][2]);
					double rNormal_y = m_Cube[i][3][1];
					double rNormal_z = (m_Cube[i][3][0]) * sin(rTime) 
						+ cos(rTime) * (m_Cube[i][3][2]);

					int iScreen_x = int((rRotation_x 
						/ (1 - rRotation_z / C) + 1.f) / 2 * SCREEN_WIDTH);
					int iScreen_y = int((rRotation_y 
						/ (1 - rRotation_z / C) + 1.f) / 2 * SCREEN_HEIGHT);
					double rScreen_z = rRotation_z / (1 - rRotation_z / C);

					double rL = rNormal_z;
					if (rL > 0) {
						if (rZBuffer[iScreen_y][iScreen_x] < rScreen_z)
						{
							rZBuffer[iScreen_y][iScreen_x] = rScreen_z;
							if (JudgeFace(i, u, v) == 1)
							{
								double rTemp_u = u - (double)((int)(u * 3.f)) 
									* 1.f / 3.f;
								double rTemp_v = v - (double)((int)(v * 3.f))
									* 1.f / 3.f;
								if ((rTemp_u - 1.f / 6.f) 
									* (rTemp_u - 1.f / 6.f) 
									+ (rTemp_v - 1.f / 6.f) 
									* (rTemp_v - 1.f / 6.f) 
									<= 1.f / 36.f)
								{
									rL = 0;
								}
								else
									rL = (rL + 0.1) * sqrt(2);
							}
							else
								rL = (rL + 0.1) * sqrt(2);
							int iLuminanceIndex = int(rL * 8);
							if (iLuminanceIndex > 11)
								iLuminanceIndex = 11;
							cOutPut[iScreen_y][iScreen_x] 
								= ".,-~:;=!*#$@"[iLuminanceIndex];
						}
					}
					else
						if (rZBuffer[iScreen_y][iScreen_x] < rScreen_z)
							rZBuffer[iScreen_y][iScreen_x] = rScreen_z;
				}
		}
		for (int j = SCREEN_HEIGHT; j >= 0; j--) {
			for (int i = 0; i <= SCREEN_WIDTH; i++) {
				putchar(cOutPut[j][i]);
			}
			putchar('\n');
		}
		PlatformSleep(15);
		printf("\x1b[26A");
	}
}

