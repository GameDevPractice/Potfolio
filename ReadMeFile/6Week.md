## 6주차
### 목표 
적 AI 구현

### 달성도
AI Controller에 Perception Component 추가  
AISenseConfig_Sight를 사용하여 플레이어 발견 할 수 있게함  
적으로 인식해야 하기에 TeamID 부여  
그리고 Behavior Component 제작 후 추가  
이 Component는 AI 행동 제어를 위한 컴포넌트

플레이어가 적의 시야에 들어오면 적이 공격을 하게끔 BehaviorTree를 제작  
그러다 일정거리(Behavior Range)에 들어오면 도주 하게끔 함  
도주 경로는 플레이어에서 거리가 멀고 보이지 않는곳으로 EQS 제작
