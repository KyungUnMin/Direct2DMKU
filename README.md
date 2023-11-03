# 프로젝트 소개
![스크린샷 2023-10-16 174828](https://github.com/KyungUnMin/Direct2DMKU/assets/86768610/0229db36-e5c4-496d-9433-fb19ca35ebf4)<br/>
C++과 DirectX 라이브러리를 활용하여 모작한 프로젝트입니다.<br/>

# 기술 소개
## A*를 적용한 몬스터 이동
![ezgif com-video-to-gif](https://github.com/KyungUnMin/Direct2DMKU/assets/86768610/e343d210-6b65-455a-b88b-d67218d617e4)
![e2zgif com-video-to-gif](https://github.com/KyungUnMin/Direct2DMKU/assets/86768610/a431fb89-e75c-4abb-aceb-11be33d48f72)<br/>

## 파일입출력을 이용한 몬스터 생성 툴
![Tool](https://github.com/KyungUnMin/Direct2DMKU/assets/86768610/ebac2e2b-0704-4d78-a32e-72cc1c58d7c0)<br/>
해당 툴은 regex와 filesystem 라이브러리를 사용하여 만들었습니다.

## DirectShow 라이브러리를 이용한 오프닝 영상 출력
![Dshow](https://github.com/KyungUnMin/Direct2DMKU/assets/86768610/a5dd781d-e5ae-4eb0-9cfe-805782d5075c)


##
![EnemySpawner](https://github.com/KyungUnMin/Direct2DMKU/assets/86768610/9fdc1643-4369-441e-9138-f31d1d414953)<br/>
모든 몬스터를 해치우면 사전에 저장된 콜백을 호출시킵니다.<br/>
위 영상에서는 모든 몬스터가 쓰러졌을때 화면 좌측 상단의 잠겨있던 문이 열립니다.<br/>
콜백함수는 std::function으로 관리하였습니다.<br/>

## 노이즈를 활용한 픽셀 쉐이더 연출
![PaperBurn](https://github.com/KyungUnMin/Direct2DMKU/assets/86768610/ec4257a4-8ade-41e6-92bb-d0d65e53a4a7)<br/>
노이즈가 만들어내는 값을 바탕으로 특정 상수버퍼 미만일때는 픽셀 쉐이더에서 clip시킵니다.

# 블로그/유튜브 가기
https://blog.naver.com/insetour/223178195243<br/>
https://www.youtube.com/watch?v=qfHc50egW_Q
