# Potforio
## MarkDown 사용법
https://github.com/kimasill/MarkDown/blob/main/README.md?plain=1

## 목차  
### 일지 
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


## 기술 문서
[1.Component](#Components)<br/>
[2.Actions](#Actions)<br/>
### Components
#### ActionComponent
Character들이 가지고 있는 무기에 따라 행하는 행동을 제어하는 Component입니다.<br/>
가지고 있는 무기를 ActionType(Enum)으로 판단하며 Player는 이 ActionType을 통해 무기를 변경 할 수 있습니다.<br/>
행하는 행동들은 ActionData(DataAsset)에 저장되어 있는 정보를 사용하여 실행 합니다.<br/>
[ActionComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CActionComponent.cpp)<br/>
[ActionComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CActionComponent.h)<br/>

#### StateComponent
Character들의 상태를 관리하는 Component입니다.<br/>
EStateType(Enum 타입)으로 Character들의 상태를 정의합니다.<br/>
함수를 통해 상태를 변경할 수 있으며, 현재 상태를 검사할 수 도 있습니다.<br/>
상태를 변경할 시 Delegate를 사용하여 상태에 맞는 행동을 하게 하였습니다.<br/>
많은 타입이 있지만 가장 대표적인 Type은 Idle 입니다. 이 Idle은 어떠한 행동도 하지 않은 상태를 의미합니다.<br/>
다양한 Type들이 존재하며 상태에 맞는 행동을 하기 전에 상태를 변경하며 이 행동을 하는 동안에는 다른 행동이 불가합니다.<br/> Ex)공격중인 상태(Action)에서 무기를 장착 또는 해제(Equip, UnEquip)를 할 수 없습니다.<br/>
[StateComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CStateComponent.cpp)<br/>
[StateComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CStateComponent.h)<br/>

#### MontageComponent  
Character들이 공동으로 행해야하는 Montage를 관리하는 Component 입니다.<br/>
Montage가 재생되려면 위에 서술한 StateComponent를 통해 재생이 됩니다.<br/>
재생될 Montage들은 구조체로 저장하여 관리합니다.<br/>
구조체는 EStateType, UAnimMotage, PlayRate(float Type), StartSection(FName)을 가지고 있습니다.<br/>
저장한 구조체에서 EStateType에 맞는 Montage를 재생합니다.<br/>
[MontageComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CMontageComponent.cpp)<br/>
[MontageComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CMontageComponent.h)<br/>

#### AttributeComponent
Character들의 가지고 있는 기본 능력치를 조정하는 Component 입니다.<br/>
Character의 기본 최대체력, 걸음 속도(Sneak, walk, Run)을 엔진에서 정할 수 있게 했습니다.<br/>
[AttributeComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CAttributeComponent.cpp)<br/>
[AttributeComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CAttributeComponent.h)<br/>

#### BehaviorComponent
AI 전용 Component 입니다.<br/>
BehaviorTree를 상태에 맞게 사용하기 위한 Component 입니다.<br/>
BehaviorType이라는 Enum 변수를 만들어 상황에 맞게 사용합니다.<br/>
예를 들어 플레이어를 쫒아가야 하는 상황이라면 BehaviorType을 Approch로 변경하여 이 정보를 BehaviorTree로 보냅니다.<br/>
보내진 정보를 사용해 AI의 움직임을 조정 할 수 있습니다.<br/>
[BehaviorComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CBehaviorComponent.cpp)<br/>
[BehaviorComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CBehaviorComponent.h)<br/>

#### PatrolComponent
AI 전용 Component 입니다.<br/>
BehaviorType이 Patrol일 경우 사용되는 Component입니다.<br/>
플레이어를 발견하기 전까지 정해진 경로를 돌아다니게 하는 Component로 사용하였습니다.<br/>
경로는 후술할 PatrolPath를 사용하였습니다.<br/>
[PatrolComponent.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CPatrolComponent.cpp)<br/>
[PatrolComponent.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Component/CPatrolComponent.h)<br/>
[PatrolPath](#PatrolPath)<br/>

### Actions
#### ActionData
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
Character가 무기를 장착한 상태에서 행하는 행동을 담당을 하는 Actor이며 CPP로 자식을 만들어 사용하였습니다.<br/>
ActionData에 저장되어 있는 정보에 따라 행동합니다.<br/>
[DoAction.Cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CDoAction.cpp)<br/>
[DoAction.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/CDoAction.h)<br/>


#### DoAction_Katana
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
###### 조준
마우스 우클릭을 하면 조준을 하게끔 만들었습니다.<br/>
조준 할 때는 [Aim.h](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/Aim.h) , [Aim.cpp](https://github.com/hiki25/Portfolio/blob/main/Source/Potpolio/Action/Aim.cpp)를 사용하였습니다.<br/>
UI는 HUD를 사용하였습니다.<br/>
###### 공격
마우스 좌클릭을 하면 공격이 나가게끔 만들었습니다.<br/>
조준을 하고 있지 않으면 공격이 나가지 않습니다.<br/>
공격을 할 때 카메라의 위치를 시작 점 카메라의 위치에서 카메라 전방 1000M를 끝 지점으로 삼아 LineTrace를 하였으며 Line이 충돌되었다면<br/>
끝지점을 충돌된 위치로 변경하였습니다.<br/>
끝지점과 소환될 위치를 사용하여 소환될 총알의 방향을 잡아주었습니다.<br/>
소환된 총알의 Collision에 Delegate을 사용하여 충돌 시 대미지를 주게 하였습니다.<br/>
공격을 할 때 카메라를 흔들림, 파열음, 발사 했을 때 Paricle을 주어 몰입감을 주었습니다.<br/>
카메라 쉐이크,Paricle은 ActionData에 저장되어있으며 파열음과 같은 소리는 Attachment에 저장되어 있습니다.<br/>
###### 재장전
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











#### PatrolPath

