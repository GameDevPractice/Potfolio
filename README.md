# 언리얼 엔진(C++)을 활용한 게임 개발
# 목차  
1. [영상](#영상)<br/>
2. [개요](#개요)<br/>
3. [기술문서](#기술문서)<br/>
4. [일지](#일지)<br/>

## 영상

[![Portfolio-1-썸네일](https://github.com/user-attachments/assets/a3de8a77-f8d9-44fa-8275-ceecd24b6bbd)](https://youtu.be/7g2pprpEhlY) <br/>


## 개요
- 목표 : 어쌔신크리드와 비슷한 잠입 액션 게임을 개발<br/>
![TriplePush_1000x540](https://github.com/user-attachments/assets/43f5ce22-3904-4fd8-b0c1-35dc0b2d1b08) <br/>
- 개발 시간 : 2024.08 ~ 2024.10<br/>
- 사용한 기술 : C++, 블루프린트, AI시스템, 애니메이션<br/>
- 중점 목표 : 어쌔신크리드의 후방 기습과 파쿠르를 자연스럽게 가능하게 제작
![image](https://github.com/user-attachments/assets/5880cc18-bb17-401c-86ca-4761be286e0e)

- 게임의 흐름 <br/>
  ![image](https://github.com/user-attachments/assets/c48908df-5c2d-4fde-a04a-d0e2bf33e204) <br/>





## 기술문서
![image](https://github.com/user-attachments/assets/daf36e40-5a1e-4818-b95f-51aad6757421)


1. [Component](#Components)<br/>
2. [Actions](#Actions)<br/>
3. [Interface](#interface-stealtakedown)<br/>
4. [AI](#AI)<br/>
5. [Player](#Player)<br/>
### Components
![image](https://github.com/user-attachments/assets/c7c33f50-76e5-41a8-bb2d-7105ccaae1fb)<br/>
- [AttributeComponent](#AttributeComponent)<br/>
- [StateComponet](#StateComponent)<br/>
- [ActionComponent](#ActionComponent)<br/>
- [MontageComponent](#MontageComponent)<br/>
- [PatrolComponent](#PatrolComponent)<br/>  
- [BehaviorComponent](#BehaviorComponent)<br/>
#### AttributeComponent
![image](https://github.com/user-attachments/assets/04f97678-ba4e-4124-afb5-22074ed2a2c9)<br/>


Character들의 가지고 있는 기본 능력치를 조정하는 Component 입니다.<br/>
Character의 기본 최대체력, 걸음 속도(Sneak, walk, Run)을 엔진에서 정할 수 있게 했습니다.<br/>
[AttributeComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CAttributeComponent.cpp)<br/>
[AttributeComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CAttributeComponent.h)<br/>

#### StateComponent
![image](https://github.com/user-attachments/assets/60154ca6-68a3-4d24-a47d-b9fe19881fbf) <br/>
![image](https://github.com/user-attachments/assets/04b16e8e-dcd7-4419-841a-ded3a397f0ff) <br/>


Character들의 상태를 관리하는 Component입니다.<br/>
EStateType(Enum 타입)으로 Character들의 상태를 정의합니다.<br/>
함수를 통해 상태를 변경할 수 있으며, 현재 상태를 검사할 수 도 있습니다.<br/>
상태를 변경할 시 Delegate를 사용하여 상태에 맞는 행동을 하게 하였습니다.<br/>
많은 타입이 있지만 가장 대표적인 Type은 Idle 입니다. 이 Idle은 어떠한 행동도 하지 않은 상태를 의미합니다.<br/>
다양한 Type들이 존재하며 상태에 맞는 행동을 하기 전에 상태를 변경하며 이 행동을 하는 동안에는 다른 행동이 불가합니다.<br/> Ex)공격중인 상태(Action)에서 무기를 장착 또는 해제(Equip, UnEquip)를 할 수 없습니다.<br/>
[StateComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CStateComponent.cpp)<br/>
[StateComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CStateComponent.h)<br/>

#### ActionComponent
![image](https://github.com/user-attachments/assets/2406086e-5e3a-4358-b3d9-4d46d251ee26)

<br/>

Character들이 가지고 있는 무기에 따라 행하는 행동을 제어하는 Component입니다.<br/>
가지고 있는 무기를 ActionType(Enum)으로 판단하며 Player는 이 ActionType을 통해 무기를 변경 할 수 있습니다.<br/>
행하는 행동들은 ActionData(DataAsset)에 저장되어 있는 정보를 사용하여 실행 합니다.<br/>
[ActionComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CActionComponent.cpp)<br/>
[ActionComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CActionComponent.h)<br/>
<br/>



#### MontageComponent  
![image](https://github.com/user-attachments/assets/53547ced-5721-4239-8b33-8ab6caf2beac)<br/>
![image](https://github.com/user-attachments/assets/4a053df6-4e9b-4e5d-b7c9-600c2965a379)<br/>


Character들이 공동으로 행해야하는 Montage를 관리하는 Component 입니다.<br/>
Montage가 재생되려면 위에 서술한 StateComponent를 통해 재생이 됩니다.<br/>
재생될 Montage들은 데이터 테이블로 저장하여 관리합니다.<br/>
 데이터 테이블은 EStateType, UAnimMotage, PlayRate(float Type), StartSection(FName)을 가지고 있습니다.<br/>
저장한 구조체에서 EStateType에 맞는 Montage를 재생합니다.<br/>
[MontageComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CMontageComponent.cpp)<br/>
[MontageComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CMontageComponent.h)<br/>

#### PatrolComponent
![image](https://github.com/user-attachments/assets/6fbba850-8a6d-4b5b-9b33-c23c5fb899a4)<br/>
![image](https://github.com/user-attachments/assets/42550cc0-76ca-493b-b86e-c92ee299f69f)<br/>

AI 전용 Component 입니다.<br/>
BehaviorType이 Patrol일 경우 사용되는 Component입니다.<br/>
플레이어를 발견하기 전까지 정해진 경로를 돌아다니게 하는 Component로 사용하였습니다.<br/>
경로는 PatrolPath를 사용하였습니다.<br/>
[PatrolComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CPatrolComponent.cpp)<br/>
[PatrolComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CPatrolComponent.h)<br/>

#### PatrolPath
AI가 순찰하는 경로로 사용하는 Actor입니다.<br/>
SplineComponent를 가지고 있습니다.<br/>
공개 변수 bClosedLoop를 통해 SplineComponent가 루프를 할지 말지를 정합니다.<br/>
잘 보이기 위해 TextRender를 주었습니다.<br/>
[PatrolPath.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CPatrolPath.cpp)<br/>
[PatrolPath.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CPatrolPath.h)<br/>


#### BehaviorComponent
![image](https://github.com/user-attachments/assets/87446317-a6f1-47a3-81f4-8f532dff3e71)<br/>
![image](https://github.com/user-attachments/assets/566b7bb1-2e0c-4af8-8f7a-94a7e982e850)<br/>

AI 전용 Component 입니다.<br/>
BehaviorTree를 상태에 맞게 사용하기 위한 Component 입니다.<br/>
BehaviorType이라는 Enum 변수를 만들어 상황에 맞게 사용합니다.<br/>
예를 들어 플레이어를 쫒아가야 하는 상황이라면 BehaviorType을 Approch로 변경하여 이 정보를 BehaviorTree로 보냅니다.<br/>
보내진 정보를 사용해 AI의 움직임을 조정 할 수 있습니다.<br/>
[BehaviorComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CBehaviorComponent.cpp)<br/>
[BehaviorComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CBehaviorComponent.h)<br/>


### Actions
![image](https://github.com/user-attachments/assets/f826acbe-7fcc-4c73-a4ec-e402e4abce2e)
<br/>

- [ActiondData](#ActionData)<br/>
- [Attachment](#Attachment)<br/>
- [Equipment](#Equipment)<br/>
- [DoAction](#DoAction)<br/>
- [DoAction_Katana](#DoAction_Katana)<br/>
- [DoAction_Pistol](#DoAction_Pistol)<br/>
- [DoAction_Rifle](#DoAction_Rifle)<br/>
#### ActionData
![image](https://github.com/user-attachments/assets/d202a064-3574-42e5-b082-8aff505e7d6b)<br/>

Actor 타입인 Attachment,DoAction, Equipment를 저장하고 이용하는 DataAseet입니다.<br/>
[ActionData.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CActionData.cpp)<br/>
[ActionData.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CActionData.h)<br/>

#### Attachment
Character에게 장착되는 무기를 담당하는 Actor이며 BP로 자식을 만들어 사용하였습니다.<br/>
Collision을 사용하여 Overlap이 실행 되었을 때를 Delegate를 사용하여 실행 할 수 있게끔 하였습니다.<br/>
무기가 장착될 때 해제될 때는 BP로 처리 할 수 있게끔 BlueprintImplementableEvent를 사용하였습니다.<br/>
[Attachment.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CAttachment.cpp)<br/>
[Attachment.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CAttachment.h)<br/>

#### Equipment
Character가 무기를 장착, 해제를 담당하는 Actor이며 BP로 자식을 만들어 사용하였습니다.<br/>
장착, 해제를 시작할 때는 StateComponent를 사용하여 움직임을 제한하였고<br/>
AttributeComponent를 사용하여 정면만 바라보는지 아닌지를 정하게 하였습니다.<br/>
장착, 해제가 마무리가 되면 Delegate를 사용하도록 하였습니다.<br/>
시작과 끝은 Notify를 이용하여 정하였습니다.<br/>
[Equipment.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CEquipment.cpp)<br/>
[Equipment.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CEquipment.h)<br/>

#### DoAction
![image](https://github.com/user-attachments/assets/20fd6a8e-9677-4004-8fee-74b28df19124)<br/>

Character가 무기를 장착한 상태에서 행하는 행동을 담당을 하는 Actor이며 CPP로 자식을 만들어 사용하였습니다.<br/>
ActionData에 저장되어 있는 정보에 따라 행동합니다.<br/>
[DoAction.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CDoAction.cpp)<br/>
[DoAction.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CDoAction.h)<br/>


#### DoAction_Katana
![image](https://github.com/user-attachments/assets/88669306-e64a-4ffe-aef2-663f4a86fc31) <br/>

![image](https://github.com/user-attachments/assets/db819a69-e6e4-4ace-aaed-71d19f183f2f) <br/>
![image](https://github.com/user-attachments/assets/2c035568-4442-4d00-87e9-dd2c7c6d8ff6) <br/>


DoAction을 상속받은 자식입니다.<br/>
칼(Katana)를 장착하고 있을 시 공격이 가능한 DoAction입니다.<br/>
마우스 좌클릭을 하면 공격이 나가게끔 만들었습니다.<br/>
공격이 나가면서 콤보 가능한 타이밍에 한 번 더 누르면 다음 콤보가 나오게끔 하였습니다.<br/>
이 타이밍은 NotifyState를 이용하였습니다.<br/>
다단히트를 처리하기 위해서 공격에 맞은 적들을 저장할 배열과 그 배열의 총 크기를 저장할 int32 타입의 변수(NumberOfHittedCharacters)를 만들어 해결했습니다.<br/> 
Overlap이 실행될 때 변수(NumberOfHittedCharacters)를 배열의 크기로 저장하고 배열에 공격에 맞은 적을 저장합니다.<br/>
저장한 후 배열의 크기가 변수보다 클때 적에게 대미지를 가하게 하였습니다.<br/>
[DoAction_Katana.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CDoAction_Katana.cpp)<br/>
[DoAction_Katana.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CDoAction_Katana.h)<br/>

#### DoAction_Pistol
DoAction을 상속받은 자식입니다.<br/>
권총(Pistol)을 장착하고 있을 시 공격이 가능하며 플레이어 전용 DoAction입니다.<br/>
![image](https://github.com/user-attachments/assets/0070f5a9-aca6-46c4-8fb8-2509adcae3bc)<br/>

###### 조준
***
![image](https://github.com/user-attachments/assets/370f7723-8593-4c6a-960e-21092bf03f34)<br/>

마우스 우클릭을 하면 조준을 하게끔 만들었습니다.<br/>
조준 할 때는 [Aim.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/Aim.h) , [Aim.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/Aim.cpp)를 사용하였습니다.<br/>
UI는 HUD를 사용하였습니다.<br/>
###### 공격
***
![image](https://github.com/user-attachments/assets/5b85597e-32cd-4d38-a884-949d67f3dd4f)<br/>
![image](https://github.com/user-attachments/assets/8779a161-b1d4-4eaf-9ad5-16618142f664)<br/>



마우스 좌클릭을 하면 공격이 나가게끔 만들었습니다.<br/>
조준을 하고 있지 않으면 공격이 나가지 않습니다.<br/>
공격을 할 때 카메라의 위치를 시작 점 카메라의 위치에서 카메라 전방 1000M를 끝 지점으로 삼아 LineTrace를 하였으며 Line이 충돌되었다면<br/>
끝지점을 충돌된 위치로 변경하였습니다.<br/>
끝지점과 소환될 위치를 사용하여 소환될 총알의 방향을 잡아주었습니다.<br/>
소환된 총알의 Collision에 Delegate을 사용하여 충돌 시 대미지를 주게 하였습니다.<br/>
공격을 할 때 카메라를 흔들림, 파열음, 발사 했을 때 Paricle을 주어 몰입감을 주었습니다.<br/>
카메라 쉐이크,Paricle은 ActionData에 저장되어있으며 파열음과 같은 소리는 Attachment에 저장되어 있습니다.<br/>
###### 재장전
***
![image](https://github.com/user-attachments/assets/8f8d89d1-c41c-488b-a3f1-42abf8edb8b3)
<br/>
![image](https://github.com/user-attachments/assets/e733d0cc-441f-488e-a694-5e5cd4c8d99d)<br/>
![image](https://github.com/user-attachments/assets/dce5c200-fa3d-4f2e-a34e-dc8270241891)<br/>

공격을 하던 중 총알이 부족하면 재장전을 하게 만들었습니다.<br/>
총알은 현재 장전되어 있는 총알 수 / 가지고 있는 최대 총알 수 입니다.<br/>
장전을 하면 장전되어 있는 총알 수가 늘어나며 최대 총알 수는 줄어듭니다.<br/>
최대 총알 수가 0이라면 장전은 할 수 없습니다.<br/>
[DoAction_Pistol.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CDoAction_Pistol.cpp)<br/>
[DoAction_Pistol.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CDoAction_Pistol.h)<br/>




#### DoAction_Rifle
DoAction을 상속받은 자식입니다.<br/>
Rifle를 가지고 있는 AI가 공격할 수 있는 DoAction입니다.<br/>
AI의 BehaviorType이 Action일 경우 실행이 됩니다.<br/>
공격의 DoAction_Pistol의 공격과 구조는 같으며, 총알을 다 사용하면 장전을 하게 하였습니다.<br/>
연사를 하길 바라였기 때문에 BehaviorTree에서 Loop를 사용하였습니다.<br/>
[DoAction_Rifle.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CDoAction_Rifle.cpp)<br/>
[DoAction_Rifle.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CDoAction_Rifle.h)<br/>


### Interface (StealTakeDown)
![image](https://github.com/user-attachments/assets/494310bc-d6f3-44f1-9b97-f9730f3ed4bd)<br/>
![image](https://github.com/user-attachments/assets/6980b64b-7133-40e9-8576-b2656d558a10)
<br/>


StealTakeDown을 위한 Interface입니다.<br/>
플레이어는 몰래 적을 기습할 때, 적은 기습을 당할 때 실행되게 만들었습니다.<br/>
플레이어의 무기 상태가 Unarmed와 Katana일때만 실행이 가능합니다.<br/>
또한 Katana일시 앉아서도 기습이 가능하게 하였습니다.<br/>
매개변수로 앉았는지 확인하는 bool 변수(InCrouch) 와 무기상태를 확인하는 변수 EActionType 변수(InActionType)를 받습니다.<br/>
[Player.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Character/Player/CPlayer.cpp) 258번째 줄입니다.<br/>
[Enemy.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Character/Enemy/CEnemy.cpp) 85번째 줄입니다.<br/>
<br/>

![image](https://github.com/user-attachments/assets/c9bbe373-c8da-4992-9e38-01f4076f085f)<br/>

StealTakeDown의 Montage관리는 데이터테이블을 사용하였습니다.<br/>


### AI
- [AIController](#AIController)
- [BTService_RifleEnemy](#BTService_RifleEnemy)
- [BTService_MeleeEnemy](#BTService_MeleeEnemy)

#### AIController
AI가 가지고 있는 Controller입니다<br/>
AI에게 감각를 주기 위해 PerceptionComponent를 사용하였으며 오감 중 시야를 주기위해 UAISenseConfig_Sight를 사용하였습니다.<br/>
또한,일정 거리에 들어오면 특정 행동(공격, 도망)을 할 수 있게 하였습니다.<br/>
플레이어가 시야에 잡히면 플레이어를 Blackboard에 값으로 보냅니다.<br/>
[AIController.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CAIController.cpp)<br/>
[AIController.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CAIController.h)<br/>

#### BTService_RifleEnemy
![image](https://github.com/user-attachments/assets/f177a3dc-4e49-4d87-9177-84a972fa2191)<br/>

Rifle를 가진 적 전용 Service입니다.<br/>
시야에 플레이어가 잡히면 공격을 하고 플레이어가 일정 거리 안으로 들어온다면 도망가도록 하였습니다.<br/>
이 때 EQS를 사용하여 플레이어에게는 멀고 방향은 반대로 움직이게 하였습니다.<br/>
[BTService_RifleEnemy.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTService_Enemy.cpp)<br/>
[BTService_RifleEnemy.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTService_Enemy.h)<br/>

#### BTService_MeleeEnemy
Katana를 가진 적 전용 Service입니다.<br/>
시야에 플레이어가 잡히면 플레이어를 쫒아옵니다.<br/>
그러다 일정 공간에 들어오면 플레이어에게 공격을 시작합니다.<br>
[BTService_MeleeEnemy.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTService_MeleeEnemy.cpp)<br/>
[BTService_MeleeEnemy.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTService_MeleeEnemy.h)<br/>

***

#### BTTaskNode_Attack
AI의 BehaviorType가 Attack일때 실행되는 Node입니다.<br/>
[BTTaskNode_Attack.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTTaskNode_Attack.cpp)<br/>
[BTTaskNode_Attack.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTTaskNode_Attack.h)<br/>

#### BTTaskNode_Reload
Rifle을 가진 적이 총알을 소진 했을 시 실행되는 Node입니다.<br/>
[BTTaskNode_Reload.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTTaskNode_Reload.cpp)<br/>
[BTTaskNode_Reload.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTTaskNode_Reload.h)<br/>

#### BTTaskNode_Patrol
AI가 플레이어를 찾지 못했을 시 Behaviortype이 Patrol일때 실행되는 Node입니다.<br/>
[BTTaskNode_Patrol.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTTaskNode_Patrol.cpp)<br/>
[BTTaskNode_Patrol.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTTaskNode_Patrol.h)<br/>

#### BTTaskNode_Speed
AI의 행동이 추격일 때와 순찰일 때 속도를 정하기 위해 만든 Node입니다.<br/>
[BTTaskNode_Speed.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTTaskNode_Speed.cpp)<br/>
[BTTaskNode_Speed.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/AI/CBTTaskNode_Speed.h)<br/>



### Player
플레이어가 조종할 수 있는 Character입니다.<br/>
위에 서술한 대부분 기술들을 사용하여 만들었습니다.<br/>
player는 좌Shift를 누르고 있으면 속도가 빨라져 달리게 됩니다.<br/>
그러나 Katana를 장착하고 있으면 누르면 회피를 하게 만들었습니다.<br/>
회피를 하고도 계속 누르고 있으면 달리게 만들었습니다.<br/>
또한 Tick을 사용하여 Player가 달리는 도중 앞을 가로 막는 장애물이 있다면 뛰어넘게 만들었습니다.<br/>
[Player.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Character/Player/CPlayer.cpp)<br/>
[Player.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Character/Player/CPlayer.h)<br/>

## 일지 
[1주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/1Week.md)  
[2주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/2Week.md)  
[3주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/3Week.md)  
[4주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/4Week.md)  
[5주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/5Week.md)  
[6주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/6Week.md)  
[7주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/7Week.md)  
[8주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/8Week.md)  
[9주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/9Week.md)  
[10주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/10Week.md)  
[11주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/11Week.md)  
[12주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/12Week.md)  
