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
행하는 행동들은 ActionData(DataAsset)에 저장되어 있는 AnimMontage를 실행 합니다.<br/>
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
DataAsset을 부모로 사용하며 Actor 타입인 Attachment,DoAction, Equipment를 저장하고 이용하는 







#### PatrolPath

