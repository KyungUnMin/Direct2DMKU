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
	std::pair<int, int> Pos;	//X, Y

	//최소힙
	bool operator <(const BestRouth& _Other) const
	{
		return TotalPoint > _Other.TotalPoint;
	}
};

void EnemyState_WalkBase::FindPath()
{
	// 점수 매기기
		// F = G + H
		// F = 최종 점수 (작을 수록 좋음, 경로에 따라 달라짐)
		// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용 (작을 수록 좋음, 경로에 따라 달라짐)
		// H = 목적지에서 얼마나 가까운지, 벽을 생각하지 않은 직선거리(작을 수록 좋음, 고정)

	FieldEnemyBase* EnemyPtr = GetEnemy();
	const std::pair<int, int> StartPos = EnemyPtr->GetGridPos();
	const std::pair<int, int>& DestPos = FieldPlayer::GetPtr()->GetGridPos();

	//<다음위치, 현재위치>, 경로를 탐색하면서 이 위치가 어떤 부모 위치로부터 왔는지 기록
	static std::map<std::pair<int, int>, std::pair<int, int>> Parent;
	Parent.clear();


	//방문 여부(확정 위치)
	static std::set<std::pair<int, int>> CloseList;
	CloseList.clear();


	//해당 위치에 해당되는 점수(예약위치)
	static std::map<std::pair<int, int>, int> OpenList;
	OpenList.clear();

	//예약한 위치중에 F의 값이 최소인 경로
	std::priority_queue<BestRouth> PQ;

	//시작 위치의 G, (H는 당연히 0)
	int StartCost = 10 * (abs(StartPos.first - DestPos.first) + abs(StartPos.second - DestPos.second));	

	//시작 위치 등록
	OpenList[StartPos] = StartCost;

	//경로를 다 탐색하고 역으로 부모경로를 추적할 때, 시작위치임을 알림
	Parent[StartPos] = StartPos;

	//경로 예약
	PQ.push({ StartCost, 0, StartPos });
	while (false == PQ.empty())
	{
		BestRouth Now = PQ.top();
		int X = Now.Pos.first;
		int Y = Now.Pos.second;
		PQ.pop();

		//이미 방문한 곳이라면 그곳은 탐색하지 않음
		if (CloseList.end() != CloseList.find(Now.Pos))
			continue;

		//해당 위치 방문
		CloseList.insert(Now.Pos);

		//목적지 도착
		if (DestPos == Now.Pos)
			break;


		static const int Dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
		static const int Dy[] = { 0, 1, 0, -1, 1, -1, 1, -1 };
		static const int NeedCost[] = { 10, 10, 10, 10, 14, 14, 14, 14 };

		for (size_t i = 0; i < 8; ++i)
		{
			int NextX = Now.Pos.first + Dx[i];
			int NextY = Now.Pos.second + Dy[i];

			//그리드 영역 밖일때
			if (NextX < 0 || NextY < 0 || GridMapScale.first < NextX || GridMapScale.second < NextY)
				continue;

			//막힌 곳일때
			if (true == GetBackGround()->IsBlockGrid(NextX, NextY))
				continue;

			//이미 방문한 곳일때
			std::pair<int, int> NextPos = std::pair<int, int>(NextX, NextY);
			if (CloseList.end() != CloseList.find(NextPos))
				continue;


			//이동하는 데 필요한 비용(G)
			int NextCost = Now.Cost + NeedCost[i];
			//목적지까지의 직선거리(H)
			int Distance = 10 * (abs(DestPos.first - NextX) + abs(DestPos.second - NextY));
			//최종점수(F)
			int NextTotalPoint = NextCost + Distance;

			//이전에는 예약하지 않았던 위치인 경우
			if (false == OpenList.contains(NextPos))
			{
				OpenList[NextPos] = INT32_MAX;
			}

			//기존의 해당 지점까지의 이동비용
			int& PrevCost = OpenList[NextPos];

			//기존이 이동 경로보다 지금의 이동경로가 더 안좋은 상황일때
			if (PrevCost < NextTotalPoint)
				continue;

			//이동 경로 점수 재갱신
			PrevCost = NextTotalPoint;
			PQ.push({ NextTotalPoint, NextCost,NextPos });
			Parent[NextPos] = Now.Pos;
		}
	}


	PathStack.clear();
	if (PathStack.capacity() < CloseList.size())
	{
		PathStack.reserve(CloseList.size());
	}
	

	//예외처리, 몬스터가 플레이어에게 이동할 수 없는 위치인 경우
	if (false == Parent.contains(DestPos))
	{
		std::string StartFieldPosStr = EnemyPtr->GetTransform()->GetWorldPosition().ToString();
		std::string StartGridPosStr = "(" + std::to_string(StartPos.first) + ", " + std::to_string(StartPos.second) + ")";
		std::string SendText = "Enemy가 플레이어에게 이동할 수 없는 위치에 있습니다\n";
		SendText += "적의 시작위치 : " + StartFieldPosStr + "\n";
		SendText += "적의 시작 그리드 위치 : " + StartGridPosStr;
		MsgAssert(SendText);
		return;
	}

	std::map<std::pair<int, int>, std::pair<int, int>>::iterator FindIter = Parent.find(DestPos);
	std::pair<int, int> NextPos = FindIter->first;
	std::pair<int, int> PrevPos = FindIter->second;
	PathStack.push_back(NextPos);

	//처음 시작위치에 도달할때 까지 탐색 경로를 역으로 추적
	while (NextPos != PrevPos)
	{
		FindIter = Parent.find(PrevPos);
		NextPos = FindIter->first;
		PrevPos = FindIter->second;

		PathStack.push_back(NextPos);
	}
}
