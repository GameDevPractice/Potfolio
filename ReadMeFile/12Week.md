### 목표  
**1. 게임 클리어를 위한 아이템**  
**2. 게임 BGM(적이 플레이어를 발견 하면 바뀜)**  
**3. 게임 클리어 시 나오는 시네마틱 영상 제작**  
**4. 영상이 끝나고 나오는 UI**

### 달성도
목표 달성
#### 게임 클리어을 위한 아이템
|사진|설명|
|---|---|
|<img src = Image/VictoryItem.pngLogic.png  width = 400px Height = 400px>|Overlap이 되어야 Gamemode에 있는 함수를 실행하여 점수를 올린다|
|<img src = Image/VictoryItem.pngLogic2.png  width = 400px Height = 400px>|일정 점수를 넘으면 엔딩이 실행이 된다.엔딩은 BlueprintImplementableEvent을 이용하여 BP에서 만든다|
|<img src = Image/GameMode.png  width = 400px Height = 400px>|시네마틱을 재생하기 위해 GameMode를 상속받아 Bp로 만들어 엔딩을 장식한다, Widget은 부모에서 받는다.|

#### 게임 BGM
1. MainMap의 레벨 BP로 실행한다.
2. 시작 시 Audio Component로 평범, 전투 할 때 재생할 Sound Cue를 스폰한다.
3. 시작 시 맵에 존재하는 모든 AI Controller를 저장한다.
4. Tick으로 AI Controller가 존재하는지 검사하며 Player를 발견했는지 검사한다.
5. Player를 발견하였다면 현재 재생하고 있는 노래를 검사하고 알맞는 노래로 변경한다.  

|순서|사진|
|:---:|---|
|1.BeginPlay|<img src = Image/LevelBP_BeginPlay.png width = 400px>|
|2.Tick|<img src = Image/LevelBP_Tick.png width = 400px>|
|3.PlayBGM|<img src = Image/LevelBP_PlayBGM.png width = 400px>|

### 결과
|사진|설명|
|---|---|
|<img src= Image/VictoryItem.png width = 200px Height = 200px>|**게임 클리어를 위한 아이템 4개를 모으면 게임이 클리어**|
|<img src =Image/VictoryEnding.png width = 400px Height = 400px>|**게임 클리어시 나오는 UI**|


### ToDo
## 끝
