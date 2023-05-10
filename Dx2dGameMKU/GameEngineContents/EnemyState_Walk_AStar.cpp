#include "PrecompileHeader.h"
#include "EnemyState_Walk.h"

#include <queue>

#include "BackGround.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"

struct BestRouth
{
	int TotalPoint = INT32_MAX;
	int Cost = INT32_MAX;
	std::pair<int, int> Pos;

	//최소힙
	bool operator <(const BestRouth& _Other) const
	{
		return TotalPoint > _Other.TotalPoint;
	}
};

void EnemyState_Walk::FindPath()
{
	// 점수 매기기
		// F = G + H
		// F = 최종 점수 (작을 수록 좋음, 경로에 따라 달라짐)
		// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용 (작을 수록 좋음, 경로에 따라 달라짐)
		// H = 목적지에서 얼마나 가까운지, 벽을 생각하지 않은 직선거리(작을 수록 좋음, 고정)

	const std::pair<int, int> StartPos = BGPtr->GetGridFromPos(EnemyPtr->GetTransform()->GetWorldPosition());
	const std::pair<int, int>& DestPos = FieldPlayer::GetPtr()->GetGridPos();

	//<다음위치, 현재위치>
	static std::map<std::pair<int, int>, std::pair<int, int>> MovePath;
	MovePath.clear();

	//방문 여부
	static std::set<std::pair<int, int>> IsVisted;
	IsVisted.clear();


	//해당 위치에 해당되는 점수
	static std::map<std::pair<int, int>, int> BestPath;
	BestPath.clear();

	//다음에 이동할 곳을 예약한다
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

		//이미 방문한 곳이라면 그곳은 탐색하지 않음
		if (IsVisted.end() != IsVisted.find(Now.Pos))
			continue;

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
			if (true == BGPtr->IsBlockGrid(NextX, NextY))
				continue;

			//이미 방문한 곳일때
			std::pair<int, int> NextPos = std::pair<int, int>(NextX, NextY);
			if (IsVisted.end() != IsVisted.find(NextPos))
				continue;

			//이동하는 데 필요한 비용
			int NextCost = Now.Cost + NeedCost[i];
			//목적지까지의 직선거리
			int Distance = 10 * (abs(DestPos.first - NextX) + abs(DestPos.second - NextY));
			//최종점수
			int NextTotalPoint = NextCost + Distance;

			if (BestPath.end() == BestPath.find(NextPos))
			{
				BestPath[NextPos] = INT32_MAX;
			}
			std::map<std::pair<int, int>, int>::iterator NextPosIter = BestPath.find(NextPos);

			//기존의 해당 지점까지의 이동비용
			int PrevCost = NextPosIter->second;

			//기존이 이동 경로보다 지금의 이동경로가 더 안좋은 상황일때
			if (PrevCost < NextTotalPoint)
				continue;

			//이동 경로 점수 재갱신
			NextPosIter->second = NextTotalPoint;
			PQ.push({ NextTotalPoint, NextCost,NextPos });
			MovePath[NextPos] = Now.Pos;
		}
	}

	PathStack.clear();
	PathStack.reserve(MovePath.size());

	std::map<std::pair<int, int>, std::pair<int, int>>::iterator FindIter = MovePath.find(DestPos);
	if (MovePath.end() == FindIter)
	{
		std::string StartFieldPosStr = EnemyPtr->GetTransform()->GetWorldPosition().ToString();
		std::string StartGridPosStr = "(" + std::to_string(StartPos.first) + ", " + std::to_string(StartPos.second) + ")";
		std::string SendText = "Enemy가 플레이어에게 이동할 수 없는 위치에 있습니다\n";
		SendText += "적의 시작위치 : " + StartFieldPosStr + "\n";
		SendText += "적의 시작 그리드 위치 : " + StartGridPosStr;
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
