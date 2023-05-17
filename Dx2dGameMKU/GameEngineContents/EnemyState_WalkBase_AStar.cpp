#include "PrecompileHeader.h"
#include "EnemyState_WalkBase.h"

#include <queue>

#include "BackGround.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"

struct BestRouth
{
	int TotalPoint = INT32_MAX;
	int Cost = INT32_MAX;
	std::pair<int, int> Pos;

	//�ּ���
	bool operator <(const BestRouth& _Other) const
	{
		return TotalPoint > _Other.TotalPoint;
	}
};

void EnemyState_WalkBase::FindPath()
{
	// ���� �ű��
		// F = G + H
		// F = ���� ���� (���� ���� ����, ��ο� ���� �޶���)
		// G = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ��� (���� ���� ����, ��ο� ���� �޶���)
		// H = ���������� �󸶳� �������, ���� �������� ���� �����Ÿ�(���� ���� ����, ����)

	FieldEnemyBase* EnemyPtr = GetEnemy();
	const std::pair<int, int> StartPos = EnemyPtr->GetGridPos();
	const std::pair<int, int>& DestPos = FieldPlayer::GetPtr()->GetGridPos();

	//<������ġ, ������ġ>
	static std::map<std::pair<int, int>, std::pair<int, int>> MovePath;
	MovePath.clear();


	//�湮 ����
	static std::set<std::pair<int, int>> IsVisted;
	IsVisted.clear();


	//�ش� ��ġ�� �ش�Ǵ� ����
	static std::map<std::pair<int, int>, int> BestPath;
	BestPath.clear();

	//������ �̵��� ���� �����Ѵ�
	std::priority_queue<BestRouth> PQ;


	int StartCost = 10 * (abs(StartPos.first - DestPos.first) + abs(StartPos.second - DestPos.second));
	BestPath[StartPos] = StartCost;
	MovePath[StartPos] = StartPos;
	PQ.push({ StartCost, 0, StartPos });
	
	while (false == PQ.empty())
	{
		BestRouth Now = PQ.top();
		int X = Now.Pos.first;
		int Y = Now.Pos.second;
		PQ.pop();

		//�̹� �湮�� ���̶�� �װ��� Ž������ ����
		if (IsVisted.end() != IsVisted.find(Now.Pos))
			continue;

		//�ش� ��ġ �湮
		IsVisted.insert(Now.Pos);

		//������ ����
		if (DestPos == Now.Pos)
			break;


		static const int Dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
		static const int Dy[] = { 0, 1, 0, -1, 1, -1, 1, -1 };
		static const int NeedCost[] = { 10, 10, 10, 10, 14, 14, 14, 14 };

		for (size_t i = 0; i < 8; ++i)
		{
			int NextX = Now.Pos.first + Dx[i];
			int NextY = Now.Pos.second + Dy[i];

			//�׸��� ���� ���϶�
			if (NextX < 0 || NextY < 0 || GridMapScale.first < NextX || GridMapScale.second < NextY)
				continue;

			//���� ���϶�
			if (true == BGPtr->IsBlockGrid(NextX, NextY))
				continue;

			//�̹� �湮�� ���϶�
			std::pair<int, int> NextPos = std::pair<int, int>(NextX, NextY);
			if (IsVisted.end() != IsVisted.find(NextPos))
				continue;


			//�̵��ϴ� �� �ʿ��� ���
			int NextCost = Now.Cost + NeedCost[i];
			//������������ �����Ÿ�
			int Distance = 10 * (abs(DestPos.first - NextX) + abs(DestPos.second - NextY));
			//��������
			int NextTotalPoint = NextCost + Distance;

			if (BestPath.end() == BestPath.find(NextPos))
			{
				BestPath[NextPos] = INT32_MAX;
			}
			std::map<std::pair<int, int>, int>::iterator NextPosIter = BestPath.find(NextPos);

			//������ �ش� ���������� �̵����
			int PrevCost = NextPosIter->second;

			//������ �̵� ��κ��� ������ �̵���ΰ� �� ������ ��Ȳ�϶�
			if (PrevCost < NextTotalPoint)
				continue;

			//�̵� ��� ���� �簻��
			NextPosIter->second = NextTotalPoint;
			PQ.push({ NextTotalPoint, NextCost,NextPos });
			MovePath[NextPos] = Now.Pos;
		}
	}


	PathStack.clear();
	if (PathStack.capacity() < IsVisted.size())
	{
		PathStack.reserve(IsVisted.size());
	}
	

	std::map<std::pair<int, int>, std::pair<int, int>>::iterator FindIter = MovePath.find(DestPos);
	if (MovePath.end() == FindIter)
	{
		std::string StartFieldPosStr = EnemyPtr->GetTransform()->GetWorldPosition().ToString();
		std::string StartGridPosStr = "(" + std::to_string(StartPos.first) + ", " + std::to_string(StartPos.second) + ")";
		std::string SendText = "Enemy�� �÷��̾�� �̵��� �� ���� ��ġ�� �ֽ��ϴ�\n";
		SendText += "���� ������ġ : " + StartFieldPosStr + "\n";
		SendText += "���� ���� �׸��� ��ġ : " + StartGridPosStr;
		MsgAssert(SendText);
		return;
	}

	std::pair<int, int> NextPos = FindIter->first;
	std::pair<int, int> PrevPos = FindIter->second;
	PathStack.push_back(NextPos);

	while (NextPos != PrevPos)
	{
		FindIter = MovePath.find(PrevPos);
		NextPos = FindIter->first;
		PrevPos = FindIter->second;

		PathStack.push_back(NextPos);
	}
}